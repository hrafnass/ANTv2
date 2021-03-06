//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// SurfaceD3D.cpp: D3D implementation of an EGL surface

#include "libANGLE/renderer/d3d/SurfaceD3D.h"

#include "libANGLE/Context.h"
#include "libANGLE/Display.h"
#include "libANGLE/Surface.h"
#include "libANGLE/renderer/d3d/RenderTargetD3D.h"
#include "libANGLE/renderer/d3d/RendererD3D.h"
#include "libANGLE/renderer/d3d/SwapChainD3D.h"

#include <tchar.h>
#include <EGL/eglext.h>
#include <algorithm>

namespace rx
{

SurfaceD3D::SurfaceD3D(const egl::SurfaceState &state,
                       RendererD3D *renderer,
                       egl::Display *display,
                       EGLNativeWindowType window,
                       EGLenum buftype,
                       EGLClientBuffer clientBuffer,
                       const egl::AttributeMap &attribs)
    : SurfaceImpl(state),
      mRenderer(renderer),
      mDisplay(display),
      mFixedSize(window == nullptr || attribs.get(EGL_FIXED_SIZE_ANGLE, EGL_FALSE) == EGL_TRUE),
      mOrientation(static_cast<EGLint>(attribs.get(EGL_SURFACE_ORIENTATION_ANGLE, 0))),
      mRenderTargetFormat(state.config->renderTargetFormat),
      mDepthStencilFormat(state.config->depthStencilFormat),
      mSwapChain(nullptr),
      mSwapIntervalDirty(true),
      mWindowSubclassed(false),
      mNativeWindow(renderer->createNativeWindow(window, state.config, attribs)),
      mWidth(static_cast<EGLint>(attribs.get(EGL_WIDTH, 0))),
      mHeight(static_cast<EGLint>(attribs.get(EGL_HEIGHT, 0))),
      mSwapInterval(1),
      mShareHandle(0),
      mD3DTexture(nullptr)
{
    subclassWindow();
    if (window != nullptr && !mFixedSize)
    {
        mWidth  = -1;
        mHeight = -1;
    }

    switch (buftype)
    {
        case EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE:
            mShareHandle = static_cast<HANDLE>(clientBuffer);
            break;

        case EGL_D3D_TEXTURE_ANGLE:
            mD3DTexture = static_cast<IUnknown *>(clientBuffer);
            ASSERT(mD3DTexture != nullptr);
            mD3DTexture->AddRef();
            ANGLE_SWALLOW_ERR(mRenderer->getD3DTextureInfo(state.config, mD3DTexture, &mWidth,
                                                           &mHeight, &mRenderTargetFormat));
            break;

        default:
            break;
    }
}

SurfaceD3D::~SurfaceD3D()
{
    unsubclassWindow();
    releaseSwapChain();
    SafeDelete(mNativeWindow);
    SafeRelease(mD3DTexture);
}

void SurfaceD3D::releaseSwapChain()
{
    SafeDelete(mSwapChain);
}

egl::Error SurfaceD3D::initialize(const egl::Display *display)
{
    if (mNativeWindow->getNativeWindow())
    {
        if (!mNativeWindow->initialize())
        {
            return egl::EglBadSurface();
        }
    }

    ANGLE_TRY(resetSwapChain(display));
    return egl::NoError();
}

FramebufferImpl *SurfaceD3D::createDefaultFramebuffer(const gl::FramebufferState &data)
{
    return mRenderer->createDefaultFramebuffer(data);
}

egl::Error SurfaceD3D::bindTexImage(gl::Texture *, EGLint)
{
    return egl::NoError();
}

egl::Error SurfaceD3D::releaseTexImage(EGLint)
{
    return egl::NoError();
}

egl::Error SurfaceD3D::getSyncValues(EGLuint64KHR *ust, EGLuint64KHR *msc, EGLuint64KHR *sbc)
{
    return mSwapChain->getSyncValues(ust, msc, sbc);
}

egl::Error SurfaceD3D::resetSwapChain(const egl::Display *display)
{
    ASSERT(!mSwapChain);

    int width;
    int height;

    if (!mFixedSize)
    {
        RECT windowRect;
        if (!mNativeWindow->getClientRect(&windowRect))
        {
            ASSERT(false);

            return egl::EglBadSurface() << "Could not retrieve the window dimensions";
        }

        width = windowRect.right - windowRect.left;
        height = windowRect.bottom - windowRect.top;
    }
    else
    {
        // non-window surface - size is determined at creation
        width = mWidth;
        height = mHeight;
    }

    mSwapChain =
        mRenderer->createSwapChain(mNativeWindow, mShareHandle, mD3DTexture, mRenderTargetFormat,
                                   mDepthStencilFormat, mOrientation, mState.config->samples);
    if (!mSwapChain)
    {
        return egl::EglBadAlloc();
    }

    // This is a bit risky to pass the proxy context here, but it can happen at almost any time.
    egl::Error error = resetSwapChain(display->getProxyContext(), width, height);
    if (error.isError())
    {
        SafeDelete(mSwapChain);
        return error;
    }

    return egl::NoError();
}

egl::Error SurfaceD3D::resizeSwapChain(const gl::Context *context,
                                       int backbufferWidth,
                                       int backbufferHeight)
{
    ASSERT(backbufferWidth >= 0 && backbufferHeight >= 0);
    ASSERT(mSwapChain);

    EGLint status =
        mSwapChain->resize(context, std::max(1, backbufferWidth), std::max(1, backbufferHeight));

    if (status == EGL_CONTEXT_LOST)
    {
        mDisplay->notifyDeviceLost();
        return egl::Error(status);
    }
    else if (status != EGL_SUCCESS)
    {
        return egl::Error(status);
    }

    mWidth = backbufferWidth;
    mHeight = backbufferHeight;

    return egl::NoError();
}

egl::Error SurfaceD3D::resetSwapChain(const gl::Context *context,
                                      int backbufferWidth,
                                      int backbufferHeight)
{
    ASSERT(backbufferWidth >= 0 && backbufferHeight >= 0);
    ASSERT(mSwapChain);

    EGLint status = mSwapChain->reset(context, std::max(1, backbufferWidth),
                                      std::max(1, backbufferHeight), mSwapInterval);

    if (status == EGL_CONTEXT_LOST)
    {
        mRenderer->notifyDeviceLost();
        return egl::Error(status);
    }
    else if (status != EGL_SUCCESS)
    {
        return egl::Error(status);
    }

    mWidth = backbufferWidth;
    mHeight = backbufferHeight;
    mSwapIntervalDirty = false;

    return egl::NoError();
}

egl::Error SurfaceD3D::swapRect(const gl::Context *context,
                                EGLint x,
                                EGLint y,
                                EGLint width,
                                EGLint height)
{
    if (!mSwapChain)
    {
        return egl::NoError();
    }

    if (x + width > mWidth)
    {
        width = mWidth - x;
    }

    if (y + height > mHeight)
    {
        height = mHeight - y;
    }

    if (width != 0 && height != 0)
    {
        EGLint status = mSwapChain->swapRect(context, x, y, width, height);

        if (status == EGL_CONTEXT_LOST)
        {
            mRenderer->notifyDeviceLost();
            return egl::Error(status);
        }
        else if (status != EGL_SUCCESS)
        {
            return egl::Error(status);
        }
    }

    ANGLE_TRY(checkForOutOfDateSwapChain(context));

    return egl::NoError();
}

#if !defined(ANGLE_ENABLE_WINDOWS_STORE)
#define kSurfaceProperty _TEXT("Egl::SurfaceOwner")
#define kParentWndProc _TEXT("Egl::SurfaceParentWndProc")
#define kDisplayProperty _TEXT("Egl::Display")

static LRESULT CALLBACK SurfaceWindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_SIZE)
    {
        SurfaceD3D* surf = reinterpret_cast<SurfaceD3D*>(GetProp(hwnd, kSurfaceProperty));
        if(surf)
        {
            egl::Display *display = reinterpret_cast<egl::Display *>(GetProp(hwnd, kDisplayProperty));
            surf->checkForOutOfDateSwapChain(display->getProxyContext());
        }
    }
    WNDPROC prevWndFunc = reinterpret_cast<WNDPROC >(GetProp(hwnd, kParentWndProc));
    return CallWindowProc(prevWndFunc, hwnd, message, wparam, lparam);
}
#endif

void SurfaceD3D::subclassWindow()
{
#if !defined(ANGLE_ENABLE_WINDOWS_STORE)
    HWND window = mNativeWindow->getNativeWindow();
    if (!window)
    {
        return;
    }

    DWORD processId;
    DWORD threadId = GetWindowThreadProcessId(window, &processId);
    if (processId != GetCurrentProcessId() || threadId != GetCurrentThreadId())
    {
        return;
    }

    SetLastError(0);
    LONG_PTR oldWndProc = SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(SurfaceWindowProc));
    if(oldWndProc == 0 && GetLastError() != ERROR_SUCCESS)
    {
        mWindowSubclassed = false;
        return;
    }

    SetProp(window, kSurfaceProperty, reinterpret_cast<HANDLE>(this));
    SetProp(window, kParentWndProc, reinterpret_cast<HANDLE>(oldWndProc));
    SetProp(window, kDisplayProperty, reinterpret_cast<HANDLE>(mDisplay));
    mWindowSubclassed = true;
#endif
}

void SurfaceD3D::unsubclassWindow()
{
    if (!mWindowSubclassed)
    {
        return;
    }

#if !defined(ANGLE_ENABLE_WINDOWS_STORE)
    HWND window = mNativeWindow->getNativeWindow();
    if (!window)
    {
        return;
    }

    // un-subclass
    LONG_PTR parentWndFunc = reinterpret_cast<LONG_PTR>(GetProp(window, kParentWndProc));

    // Check the windowproc is still SurfaceWindowProc.
    // If this assert fails, then it is likely the application has subclassed the
    // hwnd as well and did not unsubclass before destroying its EGL context. The
    // application should be modified to either subclass before initializing the
    // EGL context, or to unsubclass before destroying the EGL context.
    if(parentWndFunc)
    {
        LONG_PTR prevWndFunc = SetWindowLongPtr(window, GWLP_WNDPROC, parentWndFunc);
        ASSERT(prevWndFunc == reinterpret_cast<LONG_PTR>(SurfaceWindowProc));
    }

    RemoveProp(window, kSurfaceProperty);
    RemoveProp(window, kParentWndProc);
    RemoveProp(window, kDisplayProperty);
#endif
    mWindowSubclassed = false;
}


egl::Error SurfaceD3D::checkForOutOfDateSwapChain(const gl::Context *context)
{
    RECT client;
    int clientWidth = getWidth();
    int clientHeight = getHeight();
    bool sizeDirty = false;
    if (!mFixedSize && !mNativeWindow->isIconic())
    {
        // The window is automatically resized to 150x22 when it's minimized, but the swapchain shouldn't be resized
        // because that's not a useful size to render to.
        if (!mNativeWindow->getClientRect(&client))
        {
            UNREACHABLE();
            return egl::NoError();
        }

        // Grow the buffer now, if the window has grown. We need to grow now to avoid losing information.
        clientWidth = client.right - client.left;
        clientHeight = client.bottom - client.top;
        sizeDirty = clientWidth != getWidth() || clientHeight != getHeight();
    }

    if (mSwapIntervalDirty)
    {
        ANGLE_TRY(resetSwapChain(context, clientWidth, clientHeight));
    }
    else if (sizeDirty)
    {
        ANGLE_TRY(resizeSwapChain(context, clientWidth, clientHeight));
    }

    return egl::NoError();
}

egl::Error SurfaceD3D::swap(const gl::Context *context)
{
    return swapRect(context, 0, 0, mWidth, mHeight);
}

egl::Error SurfaceD3D::postSubBuffer(const gl::Context *context,
                                     EGLint x,
                                     EGLint y,
                                     EGLint width,
                                     EGLint height)
{
    return swapRect(context, x, y, width, height);
}

rx::SwapChainD3D *SurfaceD3D::getSwapChain() const
{
    return mSwapChain;
}

void SurfaceD3D::setSwapInterval(EGLint interval)
{
    if (mSwapInterval == interval)
    {
        return;
    }

    mSwapInterval = interval;
    mSwapIntervalDirty = true;
}

EGLint SurfaceD3D::getWidth() const
{
    return mWidth;
}

EGLint SurfaceD3D::getHeight() const
{
    return mHeight;
}

EGLint SurfaceD3D::isPostSubBufferSupported() const
{
    // post sub buffer is always possible on D3D surfaces
    return EGL_TRUE;
}

EGLint SurfaceD3D::getSwapBehavior() const
{
    return EGL_BUFFER_PRESERVED;
}

egl::Error SurfaceD3D::querySurfacePointerANGLE(EGLint attribute, void **value)
{
    if (attribute == EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE)
    {
        *value = mSwapChain->getShareHandle();
    }
    else if (attribute == EGL_DXGI_KEYED_MUTEX_ANGLE)
    {
        *value = mSwapChain->getKeyedMutex();
    }
    else if (attribute == EGL_DEVICE_EXT)
    {
        *value = mSwapChain->getDevice();
    }
    else UNREACHABLE();

    return egl::NoError();
}

gl::Error SurfaceD3D::getAttachmentRenderTarget(const gl::Context *context,
                                                GLenum binding,
                                                const gl::ImageIndex &imageIndex,
                                                FramebufferAttachmentRenderTarget **rtOut)
{
    if (binding == GL_BACK)
    {
        *rtOut = mSwapChain->getColorRenderTarget();
    }
    else
    {
        *rtOut = mSwapChain->getDepthStencilRenderTarget();
    }
    return gl::NoError();
}

WindowSurfaceD3D::WindowSurfaceD3D(const egl::SurfaceState &state,
                                   RendererD3D *renderer,
                                   egl::Display *display,
                                   EGLNativeWindowType window,
                                   const egl::AttributeMap &attribs)
    : SurfaceD3D(state,
                 renderer,
                 display,
                 window,
                 0,
                 static_cast<EGLClientBuffer>(0),
                 attribs)
{
}

WindowSurfaceD3D::~WindowSurfaceD3D()
{
}

PbufferSurfaceD3D::PbufferSurfaceD3D(const egl::SurfaceState &state,
                                     RendererD3D *renderer,
                                     egl::Display *display,
                                     EGLenum buftype,
                                     EGLClientBuffer clientBuffer,
                                     const egl::AttributeMap &attribs)
    : SurfaceD3D(state,
                 renderer,
                 display,
                 static_cast<EGLNativeWindowType>(0),
                 buftype,
                 clientBuffer,
                 attribs)
{
}

PbufferSurfaceD3D::~PbufferSurfaceD3D()
{
}

}  // namespace rc

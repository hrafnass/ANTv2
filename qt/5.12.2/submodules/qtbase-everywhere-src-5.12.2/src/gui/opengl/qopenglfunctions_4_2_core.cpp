/****************************************************************************
**
** Copyright (C) 2013 Klaralvdalens Datakonsult AB (KDAB)
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
**
** This file was generated by glgen version 0.1
** Command line was: glgen
**
** glgen is Copyright (C) 2013 Klaralvdalens Datakonsult AB (KDAB)
**
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
**
****************************************************************************/

#include "qopenglfunctions_4_2_core.h"
#include "qopenglcontext.h"

QT_BEGIN_NAMESPACE

/*!
    \class QOpenGLFunctions_4_2_Core
    \inmodule QtGui
    \since 5.1
    \wrapper
    \brief The QOpenGLFunctions_4_2_Core class provides all functions for OpenGL 4.2 core profile.

    This class is a wrapper for functions from OpenGL 4.2 core profile.
    See reference pages on \l {http://www.opengl.org/sdk/docs/}{opengl.org}
    for function documentation.

    \sa QAbstractOpenGLFunctions
*/

QOpenGLFunctions_4_2_Core::QOpenGLFunctions_4_2_Core()
 : QAbstractOpenGLFunctions()
 , d_1_0_Core(0)
 , d_1_1_Core(0)
 , d_1_2_Core(0)
 , d_1_3_Core(0)
 , d_1_4_Core(0)
 , d_1_5_Core(0)
 , d_2_0_Core(0)
 , d_2_1_Core(0)
 , d_3_0_Core(0)
 , d_3_1_Core(0)
 , d_3_2_Core(0)
 , d_3_3_Core(0)
 , d_4_0_Core(0)
 , d_4_1_Core(0)
 , d_4_2_Core(0)
{
}

QOpenGLFunctions_4_2_Core::~QOpenGLFunctions_4_2_Core()
{
    if (d_1_0_Core) {
        d_1_0_Core->refs.deref();
        Q_ASSERT(d_1_0_Core->refs.load());
    }
    if (d_1_1_Core) {
        d_1_1_Core->refs.deref();
        Q_ASSERT(d_1_1_Core->refs.load());
    }
    if (d_1_2_Core) {
        d_1_2_Core->refs.deref();
        Q_ASSERT(d_1_2_Core->refs.load());
    }
    if (d_1_3_Core) {
        d_1_3_Core->refs.deref();
        Q_ASSERT(d_1_3_Core->refs.load());
    }
    if (d_1_4_Core) {
        d_1_4_Core->refs.deref();
        Q_ASSERT(d_1_4_Core->refs.load());
    }
    if (d_1_5_Core) {
        d_1_5_Core->refs.deref();
        Q_ASSERT(d_1_5_Core->refs.load());
    }
    if (d_2_0_Core) {
        d_2_0_Core->refs.deref();
        Q_ASSERT(d_2_0_Core->refs.load());
    }
    if (d_2_1_Core) {
        d_2_1_Core->refs.deref();
        Q_ASSERT(d_2_1_Core->refs.load());
    }
    if (d_3_0_Core) {
        d_3_0_Core->refs.deref();
        Q_ASSERT(d_3_0_Core->refs.load());
    }
    if (d_3_1_Core) {
        d_3_1_Core->refs.deref();
        Q_ASSERT(d_3_1_Core->refs.load());
    }
    if (d_3_2_Core) {
        d_3_2_Core->refs.deref();
        Q_ASSERT(d_3_2_Core->refs.load());
    }
    if (d_3_3_Core) {
        d_3_3_Core->refs.deref();
        Q_ASSERT(d_3_3_Core->refs.load());
    }
    if (d_4_0_Core) {
        d_4_0_Core->refs.deref();
        Q_ASSERT(d_4_0_Core->refs.load());
    }
    if (d_4_1_Core) {
        d_4_1_Core->refs.deref();
        Q_ASSERT(d_4_1_Core->refs.load());
    }
    if (d_4_2_Core) {
        d_4_2_Core->refs.deref();
        Q_ASSERT(d_4_2_Core->refs.load());
    }
}

bool QOpenGLFunctions_4_2_Core::initializeOpenGLFunctions()
{
    if ( isInitialized() )
        return true;

    QOpenGLContext* context = QOpenGLContext::currentContext();

    // If owned by a context object make sure it is current.
    // Also check that current context is capable of resolving all needed functions
    if (((owningContext() && owningContext() == context) || !owningContext())
        && QOpenGLFunctions_4_2_Core::isContextCompatible(context))
    {
        // Associate with private implementation, creating if necessary
        // Function pointers in the backends are resolved at creation time
        QOpenGLVersionFunctionsBackend* d = 0;
        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_1_0_CoreBackend::versionStatus());
        d_1_0_Core = static_cast<QOpenGLFunctions_1_0_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_1_1_CoreBackend::versionStatus());
        d_1_1_Core = static_cast<QOpenGLFunctions_1_1_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_1_2_CoreBackend::versionStatus());
        d_1_2_Core = static_cast<QOpenGLFunctions_1_2_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_1_3_CoreBackend::versionStatus());
        d_1_3_Core = static_cast<QOpenGLFunctions_1_3_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_1_4_CoreBackend::versionStatus());
        d_1_4_Core = static_cast<QOpenGLFunctions_1_4_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_1_5_CoreBackend::versionStatus());
        d_1_5_Core = static_cast<QOpenGLFunctions_1_5_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_2_0_CoreBackend::versionStatus());
        d_2_0_Core = static_cast<QOpenGLFunctions_2_0_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_2_1_CoreBackend::versionStatus());
        d_2_1_Core = static_cast<QOpenGLFunctions_2_1_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_3_0_CoreBackend::versionStatus());
        d_3_0_Core = static_cast<QOpenGLFunctions_3_0_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_3_1_CoreBackend::versionStatus());
        d_3_1_Core = static_cast<QOpenGLFunctions_3_1_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_3_2_CoreBackend::versionStatus());
        d_3_2_Core = static_cast<QOpenGLFunctions_3_2_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_3_3_CoreBackend::versionStatus());
        d_3_3_Core = static_cast<QOpenGLFunctions_3_3_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_4_0_CoreBackend::versionStatus());
        d_4_0_Core = static_cast<QOpenGLFunctions_4_0_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_4_1_CoreBackend::versionStatus());
        d_4_1_Core = static_cast<QOpenGLFunctions_4_1_CoreBackend*>(d);
        d->refs.ref();

        d = QAbstractOpenGLFunctionsPrivate::functionsBackend(context, QOpenGLFunctions_4_2_CoreBackend::versionStatus());
        d_4_2_Core = static_cast<QOpenGLFunctions_4_2_CoreBackend*>(d);
        d->refs.ref();

        QAbstractOpenGLFunctions::initializeOpenGLFunctions();
    }
    return isInitialized();
}

bool QOpenGLFunctions_4_2_Core::isContextCompatible(QOpenGLContext *context)
{
    Q_ASSERT(context);
    QSurfaceFormat f = context->format();
    const QPair<int, int> v = qMakePair(f.majorVersion(), f.minorVersion());
    if (v < qMakePair(4, 2))
        return false;

    return true;
}

QOpenGLVersionProfile QOpenGLFunctions_4_2_Core::versionProfile()
{
    QOpenGLVersionProfile v;
    v.setVersion(4, 2);
    v.setProfile(QSurfaceFormat::CoreProfile);
    return v;
}

QT_END_NAMESPACE

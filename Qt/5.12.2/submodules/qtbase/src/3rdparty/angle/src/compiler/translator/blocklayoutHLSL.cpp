//
// Copyright (c) 2013-2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// blocklayout.cpp:
//   Implementation for block layout classes and methods.
//

#include "compiler/translator/blocklayoutHLSL.h"

#include "common/mathutil.h"
#include "common/utilities.h"

namespace sh
{

HLSLBlockEncoder::HLSLBlockEncoder(HLSLBlockEncoderStrategy strategy, bool transposeMatrices)
    : mEncoderStrategy(strategy), mTransposeMatrices(transposeMatrices)
{
}

void HLSLBlockEncoder::enterAggregateType()
{
    nextRegister();
}

void HLSLBlockEncoder::exitAggregateType()
{
}

void HLSLBlockEncoder::getBlockLayoutInfo(GLenum typeIn,
                                          const std::vector<unsigned int> &arraySizes,
                                          bool isRowMajorMatrix,
                                          int *arrayStrideOut,
                                          int *matrixStrideOut)
{
    GLenum type = (mTransposeMatrices ? gl::TransposeMatrixType(typeIn) : typeIn);

    // We assume we are only dealing with 4 byte components (no doubles or half-words currently)
    ASSERT(gl::VariableComponentSize(gl::VariableComponentType(type)) == BytesPerComponent);

    int matrixStride = 0;
    int arrayStride  = 0;

    // if variables are not to be packed, or we're about to
    // pack a matrix or array, skip to the start of the next
    // register
    if (!isPacked() || gl::IsMatrixType(type) || !arraySizes.empty())
    {
        nextRegister();
    }

    if (gl::IsMatrixType(type))
    {
        matrixStride = ComponentsPerRegister;

        if (!arraySizes.empty())
        {
            const int numRegisters = gl::MatrixRegisterCount(type, isRowMajorMatrix);
            arrayStride            = ComponentsPerRegister * numRegisters;
        }
    }
    else if (!arraySizes.empty())
    {
        arrayStride = ComponentsPerRegister;
    }
    else if (isPacked())
    {
        int numComponents = gl::VariableComponentCount(type);
        if ((numComponents + (mCurrentOffset % ComponentsPerRegister)) > ComponentsPerRegister)
        {
            nextRegister();
        }
    }

    *matrixStrideOut = matrixStride;
    *arrayStrideOut  = arrayStride;
}

void HLSLBlockEncoder::advanceOffset(GLenum typeIn,
                                     const std::vector<unsigned int> &arraySizes,
                                     bool isRowMajorMatrix,
                                     int arrayStride,
                                     int matrixStride)
{
    GLenum type = (mTransposeMatrices ? gl::TransposeMatrixType(typeIn) : typeIn);

    if (!arraySizes.empty())
    {
        mCurrentOffset += arrayStride * (gl::ArraySizeProduct(arraySizes) - 1);
    }

    if (gl::IsMatrixType(type))
    {
        ASSERT(matrixStride == ComponentsPerRegister);
        const int numRegisters  = gl::MatrixRegisterCount(type, isRowMajorMatrix);
        const int numComponents = gl::MatrixComponentCount(type, isRowMajorMatrix);
        mCurrentOffset += ComponentsPerRegister * (numRegisters - 1);
        mCurrentOffset += numComponents;
    }
    else if (isPacked())
    {
        mCurrentOffset += gl::VariableComponentCount(type);
    }
    else
    {
        mCurrentOffset += ComponentsPerRegister;
    }
}

void HLSLBlockEncoder::skipRegisters(unsigned int numRegisters)
{
    mCurrentOffset += (numRegisters * ComponentsPerRegister);
}

HLSLBlockEncoder::HLSLBlockEncoderStrategy HLSLBlockEncoder::GetStrategyFor(
    ShShaderOutput outputType)
{
    switch (outputType)
    {
        case SH_HLSL_3_0_OUTPUT:
            return ENCODE_LOOSE;
        case SH_HLSL_4_1_OUTPUT:
        case SH_HLSL_4_0_FL9_3_OUTPUT:
            return ENCODE_PACKED;
        default:
            UNREACHABLE();
            return ENCODE_PACKED;
    }
}

template <class ShaderVarType>
void HLSLVariableRegisterCount(const ShaderVarType &variable, HLSLBlockEncoder *encoder)
{
    if (variable.isStruct())
    {
        for (size_t arrayElement = 0; arrayElement < variable.getArraySizeProduct(); arrayElement++)
        {
            encoder->enterAggregateType();

            for (size_t fieldIndex = 0; fieldIndex < variable.fields.size(); fieldIndex++)
            {
                HLSLVariableRegisterCount(variable.fields[fieldIndex], encoder);
            }

            encoder->exitAggregateType();
        }
    }
    else
    {
        // We operate only on varyings and uniforms, which do not have matrix layout qualifiers
        encoder->encodeType(variable.type, variable.arraySizes, false);
    }
}

unsigned int HLSLVariableRegisterCount(const Uniform &variable, ShShaderOutput outputType)
{
    HLSLBlockEncoder encoder(HLSLBlockEncoder::GetStrategyFor(outputType), true);
    HLSLVariableRegisterCount(variable, &encoder);

    const size_t registerBytes = (encoder.BytesPerComponent * encoder.ComponentsPerRegister);
    return static_cast<unsigned int>(rx::roundUp<size_t>(encoder.getBlockSize(), registerBytes) /
                                     registerBytes);
}
}  // namespace sh

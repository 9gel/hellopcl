#ifndef VESGLTYPES_H
#define VESGLTYPES_H

#include "vesGL.h"

struct vesPrimitiveRenderType
{
  enum Type
  {
    Points        = GL_POINTS,
    LineStrip     = GL_LINE_STRIP,
    LineLoop      = GL_LINE_LOOP,
    Lines         = GL_LINES,
    TriangleStrip = GL_TRIANGLE_STRIP,
    TriangleFan   = GL_TRIANGLE_FAN,
    Triangles     = GL_TRIANGLES
  };
};

struct vesPrimitiveIndicesValueType
{
  enum Type
  {
    UnsignedShort = GL_UNSIGNED_SHORT,
    UnsignedInt = GL_UNSIGNED_INT
  };
};

struct vesColorDataType
{
  enum PixelFormat
  {
    PixelFormatNone = 0,
    Alpha           = GL_ALPHA,
    Luminance       = GL_LUMINANCE,
    LuminanceAlpha  = GL_LUMINANCE_ALPHA,
    RGB             = GL_RGB,
    RGBA            = GL_RGBA
  };

  enum PixelDataType
  {
    PixelDataTypeNone = 0,
    UnsignedByte      = GL_UNSIGNED_BYTE,
    UnsignedShort565  = GL_UNSIGNED_SHORT_5_6_5,
    UnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
    UnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1
  };
};

struct vesDataType
{
  enum Type
  {
    Float       = GL_FLOAT,
    FloatVec2   = GL_FLOAT_VEC2,
    FloatVec3   = GL_FLOAT_VEC3,
    FloatVec4   = GL_FLOAT_VEC4,
    Int         = GL_INT,
    IntVec2     = GL_INT_VEC2,
    IntVec3     = GL_INT_VEC3,
    IntVec4     = GL_INT_VEC4,
    Bool        = GL_BOOL,
    BoolVec2    = GL_BOOL_VEC2,
    BoolVec3    = GL_BOOL_VEC3,
    BoolVec4    = GL_BOOL_VEC4,
    FloatMat2   = GL_FLOAT_MAT2,
    FloatMat3   = GL_FLOAT_MAT3,
    FloatMat4   = GL_FLOAT_MAT4,
    Sampler1D   = GL_SAMPLER_1D,
    Sampler2D   = GL_SAMPLER_2D,
    Sampler3D   = GL_SAMPLER_3D,
    SamplerCube = GL_SAMPLER_CUBE,

    Sampler1DShadow = GL_SAMPLER_1D_SHADOW,
    Sampler2DShadow = GL_SAMPLER_2D_SHADOW,

    Undefined = 0x0
  };
};

#endif // VESGLTYPES_H

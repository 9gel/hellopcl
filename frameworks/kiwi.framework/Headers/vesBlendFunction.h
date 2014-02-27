/*========================================================================
  VES --- VTK OpenGL ES Rendering Toolkit

      http://www.kitware.com/ves

  Copyright 2011 Kitware, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 ========================================================================*/
/// \class vesBlendFunction
/// \ingroup ves
/// \see vesMaterial vesMaterialAttribute vesBlend

#ifndef VESBLENDFUNCTION_H
#define VESBLENDFUNCTION_H

// VES includes
#include "vesGL.h"
#include "vesSetGet.h"

// Forward declarations
class vesRenderState;

class vesBlendFunction
{
public:
  vesTypeMacro(vesBlendFunction);

  enum Parameter {
    DstAlpha                = GL_DST_ALPHA,
    DstColor                = GL_DST_COLOR,
    One                     = GL_ONE,
    OneMinusDstAlpha        = GL_ONE_MINUS_DST_ALPHA,
    OneMinusDstColor        = GL_ONE_MINUS_DST_COLOR,
    OneMinusSrcAlpha        = GL_ONE_MINUS_SRC_ALPHA,
    OneMinusSrcColor        = GL_ONE_MINUS_SRC_COLOR,
    SrcAlpha                = GL_SRC_ALPHA,
    SrcAlphaSaturate        = GL_SRC_ALPHA_SATURATE,
    SrcColor                = GL_SRC_COLOR,
    ConstantColor           = GL_CONSTANT_COLOR,
    OneMinusConstantColor   = GL_ONE_MINUS_CONSTANT_COLOR,
    ConstantAlpha           = GL_CONSTANT_ALPHA,
    OneMinusConstantAlpha   = GL_ONE_MINUS_CONSTANT_ALPHA,
    Zero                    = GL_ZERO
  };

   vesBlendFunction(Parameter source, Parameter destination);
  ~vesBlendFunction();

   void apply(const vesRenderState &renderState);

protected:

  Parameter m_source;
  Parameter m_destination;
};

#endif // VESBLENDFUNCTION_H

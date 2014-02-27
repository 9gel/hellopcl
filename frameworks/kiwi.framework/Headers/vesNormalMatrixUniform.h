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

#ifndef VESNORMALMATRIXUNIFORM_H
#define VESNORMALMATRIXUNIFORM_H

#include "vesUniform.h"

// VES includes
#include "vesMath.h"
#include "vesRenderStage.h"
#include "vesSetGet.h"

class vesNormalMatrixUniform : public vesUniform
{
public:
  vesTypeMacro(vesNormalMatrixUniform);

  vesNormalMatrixUniform(const std::string &name="normalMatrix") :
    vesUniform(name, vesMatrix3x3f())
  {
  }

  virtual void update(const vesRenderState &renderState,
                      const vesShaderProgram &program)
  {
    vesNotUsed(program);
    vesMatrix3x3f normalMatrix =
      makeNormalMatrix3x3f(makeTransposeMatrix4x4(makeInverseMatrix4x4
      (*(renderState.m_modelViewMatrix))));

    this->set(normalMatrix);
  }
};



#endif // VESNORMALMATRIXUNIFORM_H

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

#ifndef VESBOOLEANUNIFORM_H
#define VESBOOLEANUNIFORM_H

#include "vesUniform.h"

// VES includes
#include "vesGeometryData.h"
#include "vesMapper.h"
#include "vesRenderState.h"
#include "vesSetGet.h"

// C++ includes
#include <string>

class vesBooleanUniform : public vesUniform
{
public:
  vesTypeMacro(vesBooleanUniform);

  vesBooleanUniform(const std::string &name="booleanUniform") :
    vesUniform(name, false)
  {
  }


  virtual void update(const vesRenderState &renderState,
                      const vesShaderProgram &program)
  {
    vesNotUsed(renderState);
    vesNotUsed(program);
    // \note: Do nothing.
  }
};


class vesHasVertexColorsUniform : public vesBooleanUniform
{
public:
  vesTypeMacro(vesHasVertexColorsUniform);

  vesHasVertexColorsUniform(const std::string &name="hasVertexColors") :
    vesBooleanUniform(name)
  {
  }


  virtual void update(const vesRenderState &renderState,
                      const vesShaderProgram &program)
  {

    vesNotUsed(program);
    if (renderState.m_mapper->geometryData()->sourceData(
      vesVertexAttributeKeys::Color)) {
      this->set(true);
    } else {
      this->set(false);
    }
  }

  virtual vesUniform* asUniform()
  {
    return (static_cast<vesUniform*>(this));
  }
};

#endif // VESBOOLEANUNIFORM_H

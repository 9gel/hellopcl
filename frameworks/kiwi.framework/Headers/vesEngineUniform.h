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

#ifndef VESENGINEUNIFORM_H
#define VESENGINEUNIFORM_H

// VES includes
#include "vesBooleanUniform.h"
#include "vesIntegerUniform.h"
#include "vesRenderData.h"
#include "vesSetGet.h"

class vesEngineUniform
{
public:
  vesTypeMacro(vesEngineUniform);

  vesEngineUniform()
  {
  }

  virtual ~vesEngineUniform()
  {
  }

  virtual void bindRenderData(const vesRenderState &renderState,
                              const vesRenderData  &renderData)
    { vesNotUsed(renderState); vesNotUsed(renderData); }

  vesSharedPtr<vesUniform> uniform() { return this->m_uniform; }
  const vesSharedPtr<vesUniform> uniform() const { return this->m_uniform; }

protected:
  vesSharedPtr<vesUniform> m_uniform;
};


class vesHasVertexColors : public vesEngineUniform
{
public:
  vesHasVertexColors() : vesEngineUniform()
  {
    this->m_uniform = vesUniform::Ptr(new vesHasVertexColorsUniform());
  }
};


class vesVertexOpacityUniform : public vesUniform
{
public:
  vesTypeMacro(vesVertexOpacityUniform);

  vesVertexOpacityUniform(const std::string &name="vertexOpacity") :
    vesUniform(name, static_cast<float>(1.0))
  {
  }

  virtual void update(const vesRenderState &renderState,
                      const vesShaderProgram &program)
  {
    vesNotUsed(program);
    this->set(renderState.m_mapper->color()[3]);
  }
};


class vesPrimitiveType : public vesEngineUniform
{
public:
  vesPrimitiveType() : vesEngineUniform()
  {
    this->m_uniform = vesUniform::Ptr(new vesIntegerUniform("primitiveType"));
  }

  virtual void bindRenderData(const vesRenderState &renderState,
                              const vesRenderData  &renderData)
  {
    this->m_uniform->set(renderData.m_pritimiveType);
    this->m_uniform->callGL(renderState.m_material->shaderProgram()->
                            uniformLocation(this->m_uniform->name()));
  }
};

class vesPointSizeEngineUniform : public vesEngineUniform
{
public:
  vesPointSizeEngineUniform() : vesEngineUniform()
  {
    this->m_uniform = vesUniform::Ptr(new vesIntegerUniform("pointSize"));
  }

  virtual void bindRenderData(const vesRenderState &renderState,
                              const vesRenderData  &renderData)
  {
    this->m_uniform->set(renderData.m_pointSize);
    this->m_uniform->callGL(renderState.m_material->shaderProgram()->
                            uniformLocation(this->m_uniform->name()));
  }
};

class vesLineWidthEngineUniform : public vesEngineUniform
{
public:
  vesLineWidthEngineUniform() : vesEngineUniform()
  {
    this->m_uniform = vesUniform::Ptr(new vesUniform("lineWidth", static_cast<float>(1.0)));
  }

  virtual void bindRenderData(const vesRenderState &renderState,
                              const vesRenderData  &renderData)
  {
    this->m_uniform->set(static_cast<float>(renderData.m_lineWidth));
    this->m_uniform->callGL(renderState.m_material->shaderProgram()->
                            uniformLocation(this->m_uniform->name()));
    glLineWidth(static_cast<int>(renderData.m_lineWidth));
  }
};

class vesWindowSizeEngineUniform : public vesEngineUniform
{
public:
  vesWindowSizeEngineUniform() : vesEngineUniform()
  {
    this->m_uniform = vesUniform::Ptr(new vesUniform("windowSize", vesVector2f(1.0, 1.0)));
  }

  virtual void bindRenderData(const vesRenderState &renderState,
                              const vesRenderData  &renderData)
  {
    vesVector2f windowSize = renderState.m_viewSize / 2.0;
    this->m_uniform->set(windowSize);
    this->m_uniform->callGL(renderState.m_material->shaderProgram()->
                            uniformLocation(this->m_uniform->name()));
  }
};

#endif // VESENGINEUNIFORM_H

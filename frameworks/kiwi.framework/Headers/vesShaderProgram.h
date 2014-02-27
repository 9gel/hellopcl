/*========================================================================
  VES --- VTK OpenGL ES Rendering Toolkit

      http://www.kitware.com/ves

  Copyright 2011 Kitware, Inc.
  Copyright 2012 Willow Garage, Inc.

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
/// \class vesShaderProgram
/// \ingroup ves
/// \see vesMaterialAttribute vesMaterial

#ifndef VESSHADER_PROGRAM_H
#define VESSHADER_PROGRAM_H

// VES includes
#include "vesMaterial.h"
#include "vesMath.h"
#include "vesSetGet.h"

// C++ includes
#include <string>

// Forward declarations
class vesShader;
class vesRenderState;
class vesUniform;
class vesVertexAttribute;

class vesShaderProgram : public vesMaterialAttribute
{
public:
  vesTypeMacro(vesShaderProgram);

  vesShaderProgram();
  virtual ~vesShaderProgram();

  bool addShader(vesSharedPtr<vesShader> shader);
  bool addUniform(vesSharedPtr<vesUniform> uniform);

  bool addVertexAttribute(vesSharedPtr<vesVertexAttribute> attribute, int key);
  vesSharedPtr<vesVertexAttribute> attribute(int key);
  bool enableVertexAttribute(int key, bool value);
  bool isEnabledVertexAttribute(int key) const;

  bool addBindAttributeLocation(const std::string &name, int location);

  int uniformLocation(const std::string &name) const;
  int attributeLocation(const std::string &name) const;

  vesSharedPtr<vesUniform> uniform(const std::string &name);

  bool uniformExist(const std::string &name);

  virtual void updateUniforms();

  bool link();

  bool validate();
  void use();

  void cleanUp();
  void deleteProgram();
  void deleteVertexAndFragment();

  unsigned int programHandle();
  const unsigned int& programHandle() const;

  virtual void bind(const vesRenderState &renderState);
  virtual void unbind(const vesRenderState &renderState);
  virtual void setup(const vesRenderState &renderState);

  virtual void bindVertexData(const vesRenderState &renderState, int key);
  virtual void unbindVertexData(const vesRenderState &renderState, int key);
  virtual void setupVertexData(const vesRenderState &renderState, int key);

  virtual void bindRenderData(const vesRenderState &renderState,
                              const vesRenderData &renderData);

protected:
  int  queryUniformLocation(const std::string &value);
  int  queryAttributeLocation(const std::string &value);

  void bindAttributes();
  void bindUniforms();

private:
  class vesInternal;
  vesInternal *m_internal;

  vesShaderProgram(const vesShaderProgram&);
  void operator=  (const vesShaderProgram&);
};


#endif

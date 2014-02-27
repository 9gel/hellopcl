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
/// \class vesMaterial
/// \ingroup ves
/// \brief Class that defines the apperance of a geometry
///
/// vesMaterial defines how the geometry is going to look once rendered.
/// Material primarily constitute of various attributes such as color, texture,
/// etc. vesMaterial is a collection of these material attributes.
/// \see vesMaterialAttribute

#ifndef VESMATERIAL_H
#define VESMATERIAL_H

#include "vesObject.h"

// VES includes
#include "vesMaterialAttribute.h"
#include "vesSetGet.h"

// Forward declarations
class vesRenderData;
class vesRenderState;
class vesShaderProgram;

class vesMaterial : public vesObject
{
public:
  vesTypeMacro(vesMaterial);

  enum RenderHint
  {
    DefaultBin      = 0,
    OpaqueBin       = 1,
    TransparentBin  = 2
  };


  enum RenderBin
  {
    Default     = 0,
    Opaque      = 1,
    Transparent = 10,
    Overlay     = 20
  };

  vesMaterial();
  virtual ~vesMaterial();

  /// Set bin number of the material
  ///
  /// Bin number decides the render order within the same render hint group.
  /// Material with a higher bin number will render later compare to a
  /// material with a lower bin number.
  void setBinNumber(int number) { this->m_binNumber = number; }

  /// Return bin number of the material
  int binNumber() { return this->m_binNumber; }
  const int& binNumber() const { return this->m_binNumber; }

  /// Add new material attribute. Return true on success.
  bool addAttribute(vesSharedPtr<vesMaterialAttribute> attribute);

  /// Get material attribute
  vesSharedPtr<vesMaterialAttribute> attribute(
    vesMaterialAttribute::AttributeType type);
  const vesSharedPtr<vesMaterialAttribute> attribute(
    vesMaterialAttribute::AttributeType type) const;

  /// Provide quick acces to shader program
  bool setShaderProgram(vesSharedPtr<vesShaderProgram> shaderProgram);
  vesSharedPtr<vesShaderProgram> shaderProgram()
    { return this->m_shaderProgram; }
  const vesSharedPtr<vesShaderProgram> shaderProgram() const
    { return this->m_shaderProgram; }

  /// Set whether or not use vertex colors
  bool enableVertexColor(bool value);
  /// Get current state of vertex color flag
  bool isEnabledVertexColor() const;

  /// Render the material
  virtual void render(const vesRenderState &renderState);

  /// Remove (unbind) the material
  virtual void remove(const vesRenderState &renderState);

  /// Per render bind and setup calls
  virtual void bind(const vesRenderState &renderState);
  virtual void unbind(const vesRenderState &renderState);
  virtual void setup(const vesRenderState &renderState);

  virtual void bindVertexData(const vesRenderState &renderState, int key);
  virtual void unbindVertexData(const vesRenderState &renderState, int key);
  virtual void setupVertexData(const vesRenderState &renderState, int key);

  virtual void bindRenderData(const vesRenderState &renderState,
                              const vesRenderData  &renderData);

protected:

  int m_binNumber;

  vesSharedPtr<vesShaderProgram> m_shaderProgram;

  class vesInternal;
  vesInternal *m_internal;
};


#endif // VESMATERIAL_H

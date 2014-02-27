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
/// \class vesMaterialAttribute
/// \ingroup ves
/// \brief Base class that defines attributes of a material such as color,
/// texture etc
///
/// vesMaterialAttribute is base class for all attributes defined for a material.
/// Basically material in VES consists of attributes such as color, texture, shader etc.
/// vesMaterialAttribute provides common interface to set various key aspects of
/// material attribute such as type of attribute, binding type.
/// \see vesMaterial

#ifndef VESMATERIALATTRIBUTE_H
#define VESMATERIALATTRIBUTE_H

#include "vesObject.h"

// Forward declarations
class vesRenderData;
class vesRenderState;

class vesMaterialAttribute : public vesObject
{
public:
  vesTypeMacro(vesMaterialAttribute);

  enum AttributeType
  {
    Undefined = 0x0,
    Shader = 0x1,
    Texture = 0x2,
    Blend = 0x3,
    Depth = 0x4
  };


  enum AttributeBinding
  {
    BindAll = 0,
    BindMinimal = 1,
    BindVertexData = 2,
    BindRenderData = 3
  };


  vesMaterialAttribute() : vesObject(),
    m_enable(true),
    m_type(Undefined),
    m_binding(BindMinimal)
  {
  }


  virtual ~vesMaterialAttribute()
  {
  }

  inline void enable() { this->m_enable = true; }
  inline void disable() { this->m_enable = false; }
  inline bool isEnabled() const { return this->m_enable; }

  inline bool setType(AttributeType type) { this->m_type = type; return true; }
  inline AttributeType type() { return this->m_type; }
  inline AttributeType type() const { return this->m_type; }

  /// Define what sort of bind calls required by the attribute
  /// \note Should be set at the time of creation of the attribute.
  inline bool setBinding(AttributeBinding binding)
    { this->m_binding = binding; return true; }

  /// Return what kind of binding call is set on the attribute
  inline AttributeBinding binding() { return this->m_binding; }
  inline AttributeBinding binding() const { return this->m_binding; }

  /// Per render bind and setup calls
  virtual void bind(const vesRenderState &renderState)
    { vesNotUsed(renderState); }
  virtual void unbind(const vesRenderState &renderState)
    { vesNotUsed(renderState); }
  virtual void setup(const vesRenderState &renderState)
    { vesNotUsed(renderState); }
  virtual void bindVertexData(const vesRenderState &renderState, int key)
    { vesNotUsed(renderState); vesNotUsed(key); }
  virtual void unbindVertexData(const vesRenderState &renderState, int key)
    { vesNotUsed(renderState); vesNotUsed(key); }
  virtual void setupVertexData(const vesRenderState &renderState, int key)
    { vesNotUsed(renderState); vesNotUsed(key); }

  virtual void bindRenderData(const vesRenderState &renderState,
                              const vesRenderData  &renderData)
    { vesNotUsed(renderState); vesNotUsed(renderData); }

protected:
  bool m_enable;
  AttributeType m_type;
  AttributeBinding m_binding;
};

#endif // VESMATERIALATTRIBUTE_H

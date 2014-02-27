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

#ifndef VESRENDERSTATE_H
#define VESRENDERSTATE_H

// VES includes
#include "vesMaterial.h"
#include "vesMath.h"
#include "vesSetGet.h"

// Forward declarations
class vesMapper;

/*! Data structure to hold objects and states related to rendering. */
class vesRenderState
{
public:
  vesTypeMacro(vesRenderState);

  vesRenderState()
  {
    this->m_identity = new vesMatrix4x4f;
    m_identity->setIdentity();

    this->m_modelViewMatrix   = this->m_identity;
    this->m_projectionMatrix  = this->m_identity;
    this->m_viewSize = vesVector2f(0.0, 0.0);
  }


  ~vesRenderState()
  {
    delete this->m_identity; this->m_identity = 0x0;
  }


  void applyMaterial(const vesSharedPtr<vesMaterial> &material)
  {
    if (material && material != this->m_material) {
      this->m_material = material;
    }
  }


  void removeMaterial(const vesSharedPtr<vesMaterial> &material)
  {
    if (material && material == this->m_material) {
      this->m_material->remove(*this);
    }
  }


  void applyMapper(const vesSharedPtr<vesMapper> &mapper)
  {
    if (mapper && mapper != this->m_mapper) {
      this->m_mapper = mapper;
    }
  }


  void applyModelViewMatrix(vesMatrix4x4f *modelViewMatrix)
  {
    if (modelViewMatrix && modelViewMatrix != this->m_modelViewMatrix) {
      this->m_modelViewMatrix = modelViewMatrix;
    }
  }


  void applyProjectionMatrix(vesMatrix4x4f *projectionMatrix)
  {
    if (projectionMatrix  && projectionMatrix != m_projectionMatrix) {
      this->m_projectionMatrix = projectionMatrix;
    }
  }

  vesSharedPtr<vesMaterial> m_material;
  vesSharedPtr<vesMapper> m_mapper;

  vesVector2f m_viewSize;
  vesMatrix4x4f *m_identity;
  vesMatrix4x4f *m_projectionMatrix;
  vesMatrix4x4f *m_modelViewMatrix;
};

#endif // VESRENDERSTATE_H

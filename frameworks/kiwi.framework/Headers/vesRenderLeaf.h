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

#ifndef VESRENDERLEAF_H
#define VESRENDERLEAF_H

// VES includes
#include "vesRenderState.h"
#include "vesMath.h"
#include "vesSetGet.h"

// Forward declarations
class vesMapper;
class vesMaterial;

class vesRenderLeaf
{
public:
  vesTypeMacro(vesRenderLeaf);

  vesRenderLeaf(
    int depth, const vesMatrix4x4f &modelViewMatrix,
    const vesMatrix4x4f &projectionMatrix,
    const vesSharedPtr<vesMaterial> &material,
    const vesSharedPtr<vesMapper> &mapper)
  {
    this->m_depth = depth;
    this->m_modelViewMatrix = modelViewMatrix;
    this->m_projectionMatrix = projectionMatrix;

    this->m_material = material;

    if (material) {
      this->m_bin = material->binNumber();
    }
    else {
      this->m_bin = vesMaterial::DefaultBin;
    }

    this->m_mapper = mapper;
  }

  ~vesRenderLeaf()
  {
  }

  void render(vesRenderState &renderState, vesRenderLeaf *previous)
  {
    if (previous && this->m_material != previous->m_material) {
      renderState.removeMaterial(previous->m_material);
    }

    renderState.applyProjectionMatrix (&this->m_projectionMatrix);
    renderState.applyModelViewMatrix  (&this->m_modelViewMatrix);

    if (this->m_material) {
      renderState.applyMaterial(this->m_material);
    }

    if (this->m_mapper) {
      renderState.applyMapper(this->m_mapper);

      this->m_material->render(renderState);
      this->m_mapper->render  (renderState);
    }
  }

  void finalize(vesRenderState &renderState)
  {
    if (this->m_material) {
      renderState.removeMaterial(this->m_material);
    }
  }

  int m_depth;
  int m_bin;

  vesMatrix4x4f m_projectionMatrix;
  vesMatrix4x4f m_modelViewMatrix;

  vesSharedPtr<vesMaterial> m_material;
  vesSharedPtr<vesMapper> m_mapper;
};

#endif // VESRENDERLEAF_H

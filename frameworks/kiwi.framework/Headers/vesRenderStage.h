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
/// \class vesRenderStage
/// \ingroup ves
/// \see vesRenderLeaf vesRenderState vesRenderer

#ifndef VESRENDERSTAGE_H
#define VESRENDERSTAGE_H

// VES includes.
#include "vesGL.h"
#include "vesMapper.h"
#include "vesMaterial.h"
#include "vesMath.h"
#include "vesRenderLeaf.h"
#include "vesSetGet.h"
#include "vesStateAttributeBits.h"
#include "vesViewport.h"

// C++ includes
#include <list>
#include <map>
#include <vector>

class vesRenderStage
{
public:
  vesTypeMacro(vesRenderStage);

  typedef std::vector< vesRenderLeaf> RenderLeaves;
  typedef std::map<int, RenderLeaves> BinRenderLeavesMap;

  enum SortMode
  {
    BackToFront = 0x0,
    FrontToBack,
    SortByState
  };

  vesRenderStage()
  {
    this->m_clearMask = vesStateAttributeBits::ColorBufferBit
      | vesStateAttributeBits::DepthBufferBit;
    this->m_clearColor = vesVector4f(1.0f, 1.0f, 1.0f, 1.0f);
    this->m_clearDepth = 1.0;
  }

 ~vesRenderStage()
  {
    this->m_binRenderLeavesMap.clear();
  }

  void addRenderLeaf(const vesRenderLeaf &renderLeaf)
  {
    this->m_binRenderLeavesMap[renderLeaf.m_bin].push_back(renderLeaf);
  }

  void setViewport(vesSharedPtr<vesViewport> viewport) { this->m_viewport = viewport; }
  const vesSharedPtr<vesViewport> viewport() const { return this->m_viewport; }
  vesSharedPtr<vesViewport> viewport() { return this->m_viewport; }

  void sort(SortMode mode)
  {
    // \todo: Implement this.
    vesNotUsed(mode);
  }

  void render(vesRenderState &renderState, vesRenderLeaf *previous)
  {
    this->renderPreRenderStages(renderState, previous);

    if (this->m_viewport) {
      this->m_viewport->render(renderState);

      if (this->m_clearMask & GL_COLOR_BUFFER_BIT) {
        glClearColor(this->m_clearColor[0], this->m_clearColor[1],
          this->m_clearColor[2], this->m_clearColor[2]);
      }

      if (this->m_clearMask & GL_DEPTH_BUFFER_BIT) {
        glClearDepthf(this->m_clearDepth);
        glDepthMask( GL_TRUE );
      }

      glClear(this->m_clearMask);
    }

    BinRenderLeavesMap::iterator itr = this->m_binRenderLeavesMap.begin();
    RenderLeaves::iterator rlsItr;

    for (; itr != this->m_binRenderLeavesMap.end(); ++itr) {
      for (rlsItr = itr->second.begin(); rlsItr != itr->second.end(); ++rlsItr) {
        (*rlsItr).render(renderState, previous);

        previous = &(*rlsItr);
      }

      // Make sure to restore the state.
      if (!itr->second.empty()) {
        (*(--rlsItr)).finalize(renderState);
      }
    }

    this->renderPostRenderStages(renderState, previous);
  }

  void clearAll()
  {
    this->m_binRenderLeavesMap.clear();
    this->m_preRenderList.clear();
    this->m_postRenderList.clear();
  }

  void addPreRenderStage(vesSharedPtr<vesRenderStage> renderStage, int priority);
  void addPostRenderStage(vesSharedPtr<vesRenderStage>, int priority);

  void renderPreRenderStages(vesRenderState &renderState, vesRenderLeaf *previous);
  void renderPostRenderStages(vesRenderState &renderState, vesRenderLeaf *previous);

  void setClearMask(unsigned int mask);
  unsigned int clearMask() const;

  void setClearColor(const vesVector4f &clearColor);
  vesVector4f clearColor();
  const vesVector4f& clearColor() const;

  void setClearDepth(double depth);
  double clearDepth() const;

private:
  vesSharedPtr<vesViewport> m_viewport;

  typedef std::pair< int, vesSharedPtr<vesRenderStage> > RenderStageOrderPair;
  typedef std::list< RenderStageOrderPair > RenderStageList;

  BinRenderLeavesMap  m_binRenderLeavesMap;

  RenderStageList m_preRenderList;
  RenderStageList m_postRenderList;

  unsigned int m_clearMask;
  vesVector4f m_clearColor;
  double m_clearDepth;

  /// Not implemented.
  vesRenderStage(const vesRenderStage&);
  void operator=(const vesRenderStage&);
};

#endif // VESRENDERSTAGE_H

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
/// \class vesCullVisitor
/// \ingroup ves
/// \see vesVisitor

#ifndef VESCULLVISITOR_H
#define VESCULLVISITOR_H

#include "vesVisitor.h"

// VES includes
#include "vesSetGet.h"

// C/C++ includes.
#include <vector>

// Forward declarations
class vesCamera;
class vesRenderStage;

class vesCullVisitor : public vesVisitor
{
public:
  vesTypeMacro(vesCullVisitor);

  vesCullVisitor(TraversalMode mode=TraverseAllChildren) :
    vesVisitor    (CullVisitor, mode)
  {
  }

  ~vesCullVisitor()
  {
  }

  bool setRenderStage(vesSharedPtr<vesRenderStage> renderStage)
  {
    bool success = true;

    if (renderStage && this->m_renderStage != renderStage) {
      this->m_renderStage = renderStage;
      this->m_renderStageStack.push_back(this->m_renderStage);

      return success;
    }

    return !success;
  }

  vesSharedPtr<vesRenderStage> renderStage() const
  {
    return this->m_renderStageStack.back();
  }

  void pushRenderStage(vesSharedPtr<vesRenderStage> renderStage)
  {
    // No check is applied here.
    this->m_renderStageStack.push_back(renderStage);
  }

  void popRenderStage()
  {
    this->m_renderStageStack.pop_back();
  }

  virtual void visit(vesNode &node);
  virtual void visit(vesGroupNode &groupNode);
  virtual void visit(vesTransformNode &transformNode);
  virtual void visit(vesActor &actor);
  virtual void visit(vesCamera &camera);

protected:
  void addGeometryAndStates(const vesSharedPtr<vesMapper> &mapper,
                            const vesSharedPtr<vesMaterial> &material,
                            const vesMatrix4x4f &modelViewMatrix,
                            const vesMatrix4x4f &projectionMatrix,
                            float depth);

  inline void invokeCallbacksAndTraverse(vesNode &node)
  {
    this->traverse(node);
  }

  typedef std::vector< vesSharedPtr<vesRenderStage> > RenderStageStack;

  RenderStageStack m_renderStageStack;
  vesSharedPtr<vesRenderStage> m_renderStage;
};

#endif // VESCULLVISITOR_H

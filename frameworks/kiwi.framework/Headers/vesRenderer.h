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
/// \class vesRenderer
/// \ingroup ves
/// \brief Class responsible for rendering drawable entities in the scene
///
/// vesRenderer is the backbone of the rendering in VES.  It performs
/// the rendering by visiting registered actors with the renderer. Rendering
/// in VES is a three pass algorithm. Scene gets updated first, culled afterwards
/// and then gets rendered.
///
/// \see vesActor vesMapper vesVisitor

#ifndef VESRENDERER_H
#define VESRENDERER_H

// VES includes
#include "vesGL.h"
#include "vesMath.h"
#include "vesSetGet.h"

// C++ includes
#include <string>
#include <vector>

// Forward declarations
class vesActor;
class vesBackground;
class vesCamera;
class vesGroupNode;
class vesRenderStage;
class vesTexture;

class vesRenderer
{
public:
  vesTypeMacro(vesRenderer);

  vesRenderer();
  virtual ~vesRenderer();

  /// Render the scene
  virtual void render();

  /// Reset camera, calculate its position and other parameters
  /// again based on the current scene.
  virtual void resetCamera();

  /// Recalculate camera's clipping range
  virtual void resetCameraClippingRange();

  /// Resize viewport based on the new width and height of the window
  virtual void resize(int width,int height, float scale);

  /// Set background color of the renderer
  virtual void setBackgroundColor(float r, float g, float b);

  /// Get background object of the renderer
  vesSharedPtr<vesBackground> background();
  const vesSharedPtr<vesBackground> background() const;

  /// Add new actor to the collection. This is required if the actor
  /// needs to be rendered by the renderer.
  virtual void addActor   (vesSharedPtr<vesActor> actor);

  /// Remove the actor from the collection.This method will
  /// not trigger reset camera.
  virtual void removeActor(vesSharedPtr<vesActor> actor);

  /// Returns a vector containing all actors in the scene.  The vector is created
  /// by performing a depth first traversal starting at the scene root and adding
  /// actor nodes to the vector as they are visited.
  std::vector<vesSharedPtr<vesActor> > sceneActors() const;

  /// Get scene root. Do not change scene root or its data unless
  /// required in some special circumstances.
  const  vesSharedPtr<vesGroupNode> sceneRoot() const { return this->m_sceneRoot; }

  /// Get camera of the renderer
  inline vesSharedPtr<vesCamera> camera(){ return this->m_camera; }

  /// Get width of the window last set
  inline int width()   { return this->m_width;  }

  /// Get height of the window last set
  inline int height()  { return this->m_height; }

  /// Transform a vector in world space to display space
  vesVector3f computeWorldToDisplay(vesVector3f world);

  /// Transform a vector in display space to world space
  vesVector3f computeDisplayToWorld(vesVector3f display);

protected:

  virtual void updateTraverseScene();
  virtual void cullTraverseScene();
  virtual void setupBackground();
  virtual void updateBackgroundViewport();

  void resetCameraClippingRange(float bounds[6]);

private:
  double m_aspect[2];
  int m_width;
  int m_height;

  vesSharedPtr<vesCamera> m_camera;
  vesSharedPtr<vesGroupNode> m_sceneRoot;

  vesSharedPtr<vesRenderStage> m_renderStage;
  vesSharedPtr<vesBackground> m_background;
};

#endif

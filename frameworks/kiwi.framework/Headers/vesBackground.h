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
/// \class vesBackground
/// \ingroup ves
/// \see vesCamera

#ifndef VESBACKGROUND_H
#define VESBACKGROUND_H

#include "vesCamera.h"

// VES includes
#include "vesSetGet.h"

// Forward declarations.
class vesActor;
class vesDepth;
class vesImage;
class vesMapper;

class vesBackground : public vesCamera
{
public:
  vesTypeMacro(vesBackground);

  vesBackground();
  virtual ~vesBackground();

  /// Set single color for the background.
  virtual void setColor(const vesVector3f &color);

  /// Set two colors for the gradient background.
  virtual void setGradientColor(const vesVector3f &topColor,
                                const vesVector3f &bottomColor);

  /// Set image for the background
  virtual void setImage(const vesSharedPtr<vesImage> image);

  /// Get image for the background
  vesSharedPtr<vesImage> image() const;

  /// \copydoc vesCamera::modelViewMatrix()
  virtual vesMatrix4x4f modelViewMatrix();

  /// \copydoc vesCamera::projectionMatrix()
  virtual vesMatrix4x4f projectionMatrix();

protected:
  void createBackground();

  vesVector3f m_topColor;
  vesVector3f m_bottomColor;

  class vesInternal;
  vesInternal *m_internal;
};

#endif // VESBACKGROUND_H

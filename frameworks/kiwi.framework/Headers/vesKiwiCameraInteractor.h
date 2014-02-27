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
/// \class vesKiwiCameraInteractor
/// \ingroup KiwiPlatform
/// \brief A class for mapping 2D screen motions to 3D camera motions.
#ifndef __vesKiwiCameraInteractor_h
#define __vesKiwiCameraInteractor_h

#include "vesMath.h"
#include "vesSharedPtr.h"
#include "vesSetGet.h"

class vesRenderer;

class vesKiwiCameraInteractor
{
public:

  vesTypeMacro(vesKiwiCameraInteractor);

  vesKiwiCameraInteractor();
  virtual ~vesKiwiCameraInteractor();

  /// Set/Get the vesRenderer instance operated on by this interactor.
  /// The renderer is used to access the view dimensions and the camera.
  void setRenderer(vesSharedPtr<vesRenderer> renderer);
  vesSharedPtr<vesRenderer> renderer() const;

  /// Move the camera along the view direction by the given factor.
  /// \see vesCamera::dolly().
  void dolly(double scale);

  /// Roll the camera about the view direction.
  /// \see vesCamera::roll().
  void roll(double rotation);

  /// Convert a 2D translation in screen coordinates into a 3D camera rotation
  /// about the camera focal point and apply it to the camera.
  void rotate(vesVector2d screenTranslation);

  /// Convert a 2D translation in screen coordinates into a 3D camera pan,
  /// moving the camera position and camera focal point by the same amount.
  /// p0 and p1 define the end points of a movement on the screen.
  void pan(vesVector2d p0, vesVector2d p1);

private:

  vesKiwiCameraInteractor(const vesKiwiCameraInteractor&); // Not implemented
  void operator=(const vesKiwiCameraInteractor&); // Not implemented

  vesSharedPtr<vesRenderer> mRenderer;
};

#endif

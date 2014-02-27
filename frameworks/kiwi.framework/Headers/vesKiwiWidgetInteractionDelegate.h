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
/// \class vesKiwiWidgetInteractionDelegate
/// \ingroup KiwiPlatform
/// \brief A class for delegating interaction gestures to widgets.
#ifndef __vesKiwiWidgetInteractionDelegate_h
#define __vesKiwiWidgetInteractionDelegate_h

#include "vesSharedPtr.h"
#include "vesSetGet.h"

#include <vector>

class vesKiwiDataRepresentation;

class vesKiwiWidgetInteractionDelegate
{
public:

  vesTypeMacro(vesKiwiWidgetInteractionDelegate);

  vesKiwiWidgetInteractionDelegate();
  virtual ~vesKiwiWidgetInteractionDelegate();

  static bool handleSingleTouchPanGesture(double deltaX, double deltaY, std::vector<vesSharedPtr<vesKiwiDataRepresentation> > reps);

  static bool handleSingleTouchUp(std::vector<vesSharedPtr<vesKiwiDataRepresentation> > reps);

  static bool handleSingleTouchTap(int displayX, int displayY, std::vector<vesSharedPtr<vesKiwiDataRepresentation> > reps);

  static bool handleSingleTouchDown(int displayX, int displayY, std::vector<vesSharedPtr<vesKiwiDataRepresentation> > reps);


  static bool handleDoubleTap(int displayX, int displayY, std::vector<vesSharedPtr<vesKiwiDataRepresentation> > reps);

  static bool handleLongPress(int displayX, int displayY, std::vector<vesSharedPtr<vesKiwiDataRepresentation> > reps);

  static bool interactionIsActive(std::vector<vesSharedPtr<vesKiwiDataRepresentation> > reps);


private:

  vesKiwiWidgetInteractionDelegate(const vesKiwiWidgetInteractionDelegate&); // Not implemented
  void operator=(const vesKiwiWidgetInteractionDelegate&); // Not implemented

};

#endif

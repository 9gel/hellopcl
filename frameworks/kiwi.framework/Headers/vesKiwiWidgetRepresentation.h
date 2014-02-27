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
/// \class vesKiwiWidgetRepresentation
/// \ingroup KiwiPlatform
#ifndef __vesKiwiWidgetRepresentation_h
#define __vesKiwiWidgetRepresentation_h

#include "vesKiwiDataRepresentation.h"

#include <vector>
#include <string>

class vesKiwiWidgetRepresentation : public vesKiwiDataRepresentation
{
public:

  vesTypeMacro(vesKiwiWidgetRepresentation);

  vesKiwiWidgetRepresentation();
  ~vesKiwiWidgetRepresentation();

  virtual bool handleSingleTouchDown(int displayX, int displayY);
  virtual bool handleSingleTouchTap(int displayX, int displayY);
  virtual bool handleSingleTouchPanGesture(double deltaX, double deltaY);
  virtual bool handleSingleTouchUp();
  virtual bool handleDoubleTap(int displayX, int displayY);
  virtual bool handleLongPress(int displayX, int displayY);

  bool interactionIsActive() const;

  virtual std::vector<std::string> actions() const;
  virtual bool handleAction(const std::string& action);

  // HACK
  // A renderer should be passed into all the methods that require a renderer.
  // This class should be made to work with multiple renderers.
  inline vesSharedPtr<vesRenderer> renderer() { return this->m_renderer; }
  virtual void addSelfToRenderer(vesSharedPtr<vesRenderer> renderer);
  virtual void removeSelfFromRenderer(vesSharedPtr<vesRenderer> renderer);

protected:

  void interactionOn();
  void interactionOff();

private:

  bool m_interactionIsActive;
  vesSharedPtr<vesRenderer> m_renderer;

  vesKiwiWidgetRepresentation(const vesKiwiWidgetRepresentation&); // Not implemented
  void operator=(const vesKiwiWidgetRepresentation&); // Not implemented
};

#endif

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
/// \class vesKiwiImageWidgetRepresentation
/// \ingroup KiwiPlatform
#ifndef __vesKiwiImageWidgetRepresentation_h
#define __vesKiwiImageWidgetRepresentation_h

#include "vesKiwiWidgetRepresentation.h"

class vesShaderProgram;
class vesKiwiPolyDataRepresentation;
class vesKiwiImagePlaneDataRepresentation;

class vtkImageData;
class vtkPolyData;

class vesKiwiImageWidgetRepresentation : public vesKiwiWidgetRepresentation
{
public:

  vesTypeMacro(vesKiwiImageWidgetRepresentation);

  typedef vesKiwiWidgetRepresentation Superclass;
  vesKiwiImageWidgetRepresentation();
  ~vesKiwiImageWidgetRepresentation();

  enum {
    PLANE_YZ, // x axis
    PLANE_XZ, // y axis
    PLANE_XY, // z axis
  };

  void setImageData(vtkImageData* imageData);
  vtkImageData* imageData() const;

  double* imageBounds();


  int numberOfSlices(int planeIndex) const;

  void scheduleSetSliceIndex(int planeIndex, int sliceIndex);

  // note- performs clamping on sliceIndex
  void setSliceIndex(int planeIndex, int sliceIndex);

  int sliceIndex(int planeIndex) const;

  double window() const;
  double level() const;

  void resetWindowLevel();
  void setWindowLevel(double window, double level);
  void invertTable();

  void initializeWithShader(vesSharedPtr<vesShaderProgram> geometryShader,
                            vesSharedPtr<vesShaderProgram> textureShader);

  virtual void addSelfToRenderer(vesSharedPtr<vesRenderer> renderer);
  virtual void removeSelfFromRenderer(vesSharedPtr<vesRenderer> renderer);

  bool handleSingleTouchDown(int displayX, int displayY);
  bool handleSingleTouchPanGesture(double deltaX, double deltaY);
  bool handleSingleTouchUp();
  bool handleDoubleTap(int displayX, int displayY);

  virtual void willRender(vesSharedPtr<vesRenderer> renderer);

  void setInteractionIsEnabled(bool enabled);
  bool interactionIsEnabled() const;

  void setWindowLevelInteractionEnabled(bool enabled);
  bool windowLevelInteractionEnabled() const;

  virtual bool interactionIsActive() const { return this->scrollSliceModeActive(); }

  bool scrollSliceModeActive() const;

  void setPlaneVisibility(int planeIndex, bool visible);
  bool planeVisibility(int planeIndex) const;

  void scrollImageSlice(double deltaX, double deltaY);
  void setScrollSlice(int planeIndex);
  void refreshTextures();

  void setOutlineVisible(bool visible);

protected:

  vesKiwiImagePlaneDataRepresentation* newSliceRepresentation(vtkImageData* sliceImage);
  vesKiwiPolyDataRepresentation* newGeometryRepresentation(vtkPolyData* polyData);


  double OriginalWindow;
  double OriginalLevel;
  double CurrentWindow;
  double CurrentLevel;

private:

  vesKiwiImageWidgetRepresentation(const vesKiwiImageWidgetRepresentation&); // Not implemented
  void operator=(const vesKiwiImageWidgetRepresentation&); // Not implemented

  class vesInternal;
  vesInternal* Internal;
};

#endif

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
/// \class vesKiwiImagePlaneDataRepresentation
/// \ingroup KiwiPlatform
#ifndef __vesKiwiImagePlaneDataRepresentation_h
#define __vesKiwiImagePlaneDataRepresentation_h

#include "vesKiwiPolyDataRepresentation.h"

#include "vesSharedPtr.h"

#include <vtk/vtkSmartPointer.h>

class vtkImageData;
class vtkScalarsToColors;

class vesKiwiImagePlaneDataRepresentation : public vesKiwiPolyDataRepresentation
{
public:

  vesTypeMacro(vesKiwiImagePlaneDataRepresentation);

  vesKiwiImagePlaneDataRepresentation();
  ~vesKiwiImagePlaneDataRepresentation();

  void setImageData(vtkImageData* imageData);
  vtkImageData* imageData() const;

  vtkPolyData* imagePlanePolyData();

  static vtkSmartPointer<vtkPolyData> polyDataForImagePlane(vtkImageData* image);
  static int imageFlatDimension(vtkImageData* image);

  vesVector2f textureSize() const;

protected:

  void setTextureFromImage(vesSharedPtr<vesTexture> texture, vtkImageData* image);

private:

  vesKiwiImagePlaneDataRepresentation(const vesKiwiImagePlaneDataRepresentation&); // Not implemented
  void operator=(const vesKiwiImagePlaneDataRepresentation&); // Not implemented


  class vesInternal;
  vesInternal* Internal;
};


#endif

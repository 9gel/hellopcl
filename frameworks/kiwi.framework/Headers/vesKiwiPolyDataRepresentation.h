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
/// \class vesKiwiPolyDataRepresentation
/// \ingroup KiwiPlatform
#ifndef __vesKiwiPolyDataRepresentation_h
#define __vesKiwiPolyDataRepresentation_h

#include "vesKiwiDataRepresentation.h"


#include <vtk/vtkSmartPointer.h>
#include <vector>

class vesGeometryData;
class vesActor;
class vesMapper;
class vesRenderer;
class vesShaderProgram;
class vesTexture;

class vtkPolyData;
class vtkScalarsToColors;
class vtkDataArray;


class vesKiwiPolyDataRepresentation : public vesKiwiDataRepresentation
{
public:

  vesTypeMacro(vesKiwiPolyDataRepresentation);

  vesKiwiPolyDataRepresentation();
  ~vesKiwiPolyDataRepresentation();

  void initializeWithShader(vesSharedPtr<vesShaderProgram> shaderProgram);

  void setPolyData(vtkPolyData* polyData);

  void addTextureCoordinates(vtkDataArray* textureCoordinates);

  vesSharedPtr<vesGeometryData> geometryData() const;

  virtual void addSelfToRenderer(vesSharedPtr<vesRenderer> renderer);
  virtual void removeSelfFromRenderer(vesSharedPtr<vesRenderer>);

  void setColor(double r, double g, double b, double a);
  vesVector4f color();

  double opacity() const;
  void setOpacity(double opacity);

  int pointSize() const;
  void setPointSize(int size);

  int lineWidth() const;
  void setLineWidth(int width);

  void setTexture(vesSharedPtr<vesTexture> texture);
  vesSharedPtr<vesTexture> texture() const;

  void setBinNumber(int binNumber);

  virtual void setTranslation(const vesVector3f& translation);

  virtual void setShaderProgram(vesSharedPtr<vesShaderProgram> shaderProgram);
  virtual vesSharedPtr<vesShaderProgram> shaderProgram() const;

  // todo:
  // move these back to protected.  This class should provide public api so that
  // the vesActor and vesMapper can remain implementation details that callers do
  // not have to access.
  vesSharedPtr<vesMapper> mapper() const;
  vesSharedPtr<vesActor> actor() const;

  void colorByDefault();
  void colorByTexture();
  void colorByRGBArray();
  void colorBySolidColor();
  void colorByScalars();
  void colorByScalars(const std::string& arrayName);
  //void colorByScalars(vtkDataArray* scalars, vtkScalarsToColors* scalarsToColors);
  //void colorByTexture(vtkDataArray* tcoords);
  void convertVertexArrays(vtkPolyData* polyData);

  void pointsOn();
  void surfaceOn();
  void wireframeOn();
  void surfaceWithEdgesOn();
  void setSurfaceShader(vesSharedPtr<vesShaderProgram> shader);
  void setWireframeShader(vesSharedPtr<vesShaderProgram> shader);
  void setSurfaceWithEdgesShader(vesSharedPtr<vesShaderProgram> shader);
  void setTextureSurfaceShader(vesSharedPtr<vesShaderProgram> shader);
  int geometryMode() const;

  std::vector<std::string> colorModes();
  void setColorMode(const std::string& colorMode);
  std::string colorMode() const;

  enum
  {
    SURFACE_MODE = 0,
    SURFACE_WITH_EDGES_MODE,
    WIREFRAME_MODE,
    POINTS_MODE
  };

  const std::string& name() const;
  void setName(const std::string& name);

  void assignColorsInternal();

protected:


private:

  vesKiwiPolyDataRepresentation(const vesKiwiPolyDataRepresentation&); // Not implemented
  void operator=(const vesKiwiPolyDataRepresentation&); // Not implemented

  class vesInternal;
  vesInternal* Internal;
};


#endif

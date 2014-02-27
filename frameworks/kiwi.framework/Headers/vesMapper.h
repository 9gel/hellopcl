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
/// \class vesMapper
/// \ingroup ves
/// \brief Mapper contains a geometry data and has the responsibility of rendering
/// the geometry appropriately.
///
/// Actor and mapper works in pair where mapper takes the responsibility of
/// rendering a geometry using OpenGL ES 2.0 API. vesMapper defines
/// a light weight polydata rendering entity that works in conjunction with a
/// vesActor.
///
/// \see vesBoundingObject vesActor vesGeometryData

#ifndef VESMAPPER_H
#define VESMAPPER_H

#include "vesBoundingObject.h"

// VES includes
#include "vesSetGet.h"

// C/C++ includes
#include <vector>

// Forward declarations
class vesGeometryData;
class vesPrimitive;
class vesVisitor;
class vesRenderState;

class vesMapper : public vesBoundingObject
{
public:
  vesTypeMacro(vesMapper);

  vesMapper();
  virtual ~vesMapper();

  /// Compute bounds of the mapper
  virtual void computeBounds();

  /// Set geometry data for the mapper
  bool setGeometryData(vesSharedPtr<vesGeometryData> geometryData);

  /// Get geometry data of the mapper
  vesSharedPtr<vesGeometryData> geometryData();
  const vesSharedPtr<vesGeometryData> geometryData() const;

  /// Set single geometry color. Default is (1.0, 1.0, 1.0, 1.0).
  void setColor(float r, float g, float b, float a);

  /// Get single geometry color. Default is (1.0, 1.0, 1.0, 1.0).
  float* color();
  const float* color() const;

  int pointSize() const;
  void setPointSize(int size);

  int lineWidth() const;
  void setLineWidth(int width);

  /// Enable / Disable wireframe rendering
  void enableWireframe(bool value);
  /// Check whether or not wireframe rendering is enabled
  bool isEnabledWireframe() const;

  /// Render the geometry
  virtual void render(const vesRenderState &renderState);

private:
  virtual void setupDrawObjects(const vesRenderState &renderState);

  virtual void createVertexBufferObjects();
  virtual void deleteVertexBufferObjects();

protected:
  void drawPrimitive(const vesRenderState &renderState,
                     vesSharedPtr<vesPrimitive> primitive);
  void drawTriangles(const vesRenderState &renderState,
                     vesSharedPtr<vesPrimitive> triangles);
  void drawPoints(const vesRenderState &renderState,
                  vesSharedPtr<vesPrimitive> points);

  bool m_initialized;
  bool m_enableWireframe;

  int m_pointSize;
  int m_lineWidth;

  const int m_maximumTriangleIndicesPerDraw;

  vesSharedPtr<vesGeometryData> m_geometryData;

  class vesInternal;
  vesInternal *m_internal;
};

#endif

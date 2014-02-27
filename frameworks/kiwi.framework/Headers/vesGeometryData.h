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
/// \class vesGeometryData
/// \ingroup ves
/// \brief Class defines a data structure that constitutes a geometry
///
/// vesGeometryData is modeled after collada (collada.org) and XDMF (xdmf.org).
/// Primarily vesGeometryData constitutes of sources and primitives. Sources define
/// the data in some coordinate space and primitives made references to the source data
/// in order to constitute a meaningful geometry primitive.
///
/// \see vesMapper vesActor vesSourceData vesPrimitive

#ifndef VESGEOMETRYDATA_H
#define VESGEOMETRYDATA_H

// VES includes
#include "vesGL.h"
#include "vesMath.h"
#include "vesPrimitive.h"
#include "vesSetGet.h"
#include "vesSharedPtr.h"
#include "vesSourceData.h"
#include "vesVertexAttributeKeys.h"

// C/C++ includes
#include <algorithm>
#include <map>
#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
///
/// Geometry data
///
class vesGeometryData
{
public:
  typedef std::vector<vesSourceData::Ptr> Sources;

  vesTypeMacro(vesGeometryData);

  vesGeometryData() :
    m_computeBounds(true),
    m_computeNormals(true)
  {
  }

  /// Get name / ID of the geometry data
  inline const std::string& name() const
  {
    return this->m_name;
  }

  /// Set name / ID of the geometry data
  inline bool setName(const std::string &name)
  {
    bool success = true;

    this->m_name = name;

    return success;
  }

  /// Add a new source to the geometry. Return true on success.
  inline bool addSource(vesSharedPtr<vesSourceData> source)
  {
    bool success = true;

    if (std::find(this->m_sources.begin(), this->m_sources.end(), source)
      == this->m_sources.end())
    {
      this->m_sources.push_back(source);
      return success;
    }

    return !success;
  }

  /// Remove a source if it exists in the list of sources.
  inline void removeSource(vesSharedPtr<vesSourceData> source)
  {
    this->m_sources.erase(std::remove(this->m_sources.begin(), this->m_sources.end(), source), this->m_sources.end());
  }

  /// Add a new primitive to the geometry. Return true on success.
  inline bool addPrimitive(vesSharedPtr<vesPrimitive> primitive)
  {
    bool success = true;

    if (std::find(this->m_primitives.begin(), this->m_primitives.end(),
      primitive) == this->m_primitives.end())
    {
      this->m_primitives.push_back(primitive);
      return success;
    }

    return !success;
  }

  /// Return a primitive given a index. Return NULL on failure.
  inline vesSharedPtr<vesPrimitive> primitive(unsigned int index)
  {
    return this->m_primitives[index];
  }

  /// Return a primitive given a index. Return NULL on failure.
  inline const vesSharedPtr<vesPrimitive> primitive(unsigned int index) const
  {
    return this->m_primitives[index];
  }

  /// Remove a primitive if it exists in the list of primitives.
  inline void removePrimitive(vesSharedPtr<vesPrimitive> primitive)
  {
    this->m_primitives.erase(std::remove(this->m_primitives.begin(), this->m_primitives.end(), primitive), this->m_primitives.end());
  }

  /// Return a source given a index. Return NULL on failure.
  inline vesSharedPtr<vesSourceData> source(unsigned int index)
  {
    return this->m_sources[index];
  }

  /// Return a source given a index. Return NULL on failure.
  inline const vesSharedPtr<vesSourceData> source(unsigned int index) const
  {
    return this->m_sources[index];
  }

  /// Return number of primitive types contained at the moment in the geometry
  inline unsigned int numberOfPrimitiveTypes() const
  {
    return static_cast<unsigned int>(this->m_primitives.size());
  }

  /// Return number of sources contained at the moment in the geometry
  inline unsigned int numberOfSources() const
  {
    return static_cast<unsigned int>(this->m_sources.size());
  }

  /// Compute and return geometry min bounds
  inline vesVector3f boundsMin()
  {
    if (this->m_computeBounds) {
      this->computeBounds();
    }

    return this->m_boundsMin;
  }

  /// Compute and return geometry max bounds
  inline vesVector3f boundsMax()
  {
    if (this->m_computeBounds) {
      this->computeBounds();
    }

    return this->m_boundsMax;
  }

  /// Compute geometry bounds
  void computeBounds();

  /// Compute normals (per vertex) if possible
  template<typename T>
  void computeNormals();

  /// Return primitive of type triangles. Return NULL on failure.
  inline vesSharedPtr<vesPrimitive> triangles();

  /// Return primitive of type triangle strips. Return NULL on failure.
  inline vesSharedPtr<vesPrimitive> triangleStrips();

  /// Return primitive of type lines. Return NULL on failure.
  inline vesSharedPtr<vesPrimitive> lines();

  inline vesSharedPtr<vesPrimitive> points();

  /// Return source data given a key. Return NULL on failure.
  inline vesSharedPtr<vesSourceData> sourceData(int key);

private:
  void addAndUpdateNormal(unsigned int index, float n1, float n2, float n3,
                          void *data, unsigned int stride, unsigned int offset,
                          unsigned int sizeOfDataType);

  /// The ID of the geometry element
  std::string m_name;

  std::vector<vesPrimitive::Ptr> m_primitives;

  Sources m_sources;

  bool m_computeBounds;
  bool m_computeNormals;

  vesVector3f m_boundsMin;
  vesVector3f m_boundsMax;
};

vesSharedPtr<vesPrimitive> vesGeometryData::triangles()
{
  for (size_t i=0; i < this->m_primitives.size(); ++i) {
    if (this->m_primitives[i]->primitiveType() == GL_TRIANGLES) {
      return this->m_primitives[i];
    }
  }

  return vesPrimitive::Ptr();
}

vesSharedPtr<vesPrimitive> vesGeometryData::triangleStrips()
{
  for (size_t i=0; i < this->m_primitives.size(); ++i) {
    if (this->m_primitives[i]->primitiveType() == GL_TRIANGLE_STRIP) {
      return this->m_primitives[i];
    }
  }

  return vesPrimitive::Ptr();
}

vesSharedPtr<vesPrimitive> vesGeometryData::lines()
{
  for (size_t i=0; i < this->m_primitives.size(); ++i) {
    if (this->m_primitives[i]->primitiveType() == GL_LINES) {
      return this->m_primitives[i];
    }
  }

  return vesPrimitive::Ptr();
}

vesSharedPtr<vesPrimitive> vesGeometryData::points()
{
  for (size_t i=0; i < this->m_primitives.size(); ++i) {
    if (this->m_primitives[i]->primitiveType() == GL_POINTS) {
      return this->m_primitives[i];
    }
  }

  return vesPrimitive::Ptr();
}

vesSharedPtr<vesSourceData>  vesGeometryData::sourceData(int key)
{
  for (size_t i = 0; i < this->m_sources.size(); ++i) {
    if (this->m_sources[i]->hasKey(key)) {
      return this->m_sources[i];
    }
  }

  return vesSharedPtr<vesSourceData>();
}

template<typename T>
void vesGeometryData::computeNormals()
{
  if (!this->m_computeNormals) {
    return;
  }

  vesPrimitive::Ptr triangles = this->triangles();
  if (!triangles) {
    // \todo Put a log message here
    return;
  }

  vesSourceData::Ptr sourceData
    = this->sourceData(vesVertexAttributeKeys::Normal);
  if (!sourceData) {
    return;
  }

  void* data = sourceData->data();

  unsigned int count = sourceData->sizeOfArray();
  unsigned int sizeOfDataType
    = sourceData->sizeOfAttributeDataType(vesVertexAttributeKeys::Normal);
  unsigned int numberOfComponents
    = sourceData->numberOfComponents(vesVertexAttributeKeys::Normal);
  unsigned int stride
    = sourceData->attributeStride(vesVertexAttributeKeys::Normal);
  unsigned int offset
    = sourceData->attributeOffset(vesVertexAttributeKeys::Normal);

  assert(numberOfComponents <= 3);

  for (unsigned int i = 0; i < count; ++i) {
    void* v = static_cast<char*>(data) + i * stride + offset;

    for (unsigned int j = 0; j < numberOfComponents; ++j) {
      float &value = *(static_cast<float*>(v));
      value = 0.0f;
      v = static_cast<char*>(v) + sizeOfDataType;
    }
  }

  unsigned int numberOfIndices = triangles->numberOfIndices();
  vesSharedPtr< vesIndices< T > > triangleIndices
      = ::std::tr1::static_pointer_cast< vesIndices< T > >
        (triangles->getVesIndices());

  assert(triangles->indexCount() == 3);

  for (unsigned int i = 0; i < numberOfIndices; i=i+3) {

    void* p1 = static_cast<char*>(data) + triangleIndices->at(i+0) * stride;
    void* p2 = static_cast<char*>(data) + triangleIndices->at(i+1) * stride;
    void* p3 = static_cast<char*>(data) + triangleIndices->at(i+2) * stride;

    vesVector3f p1Vec3f;
    vesVector3f p2Vec3f;
    vesVector3f p3Vec3f;

    for (unsigned int j = 0; j < numberOfComponents; ++j) {
      float &valueP1 = *(static_cast<float*>(p1));
      float &valueP2 = *(static_cast<float*>(p2));
      float &valueP3 = *(static_cast<float*>(p3));

      p1Vec3f[j] = valueP1;
      p2Vec3f[j] = valueP2;
      p3Vec3f[j] = valueP3;

      p1 = static_cast<char*>(p1) + sizeOfDataType;
      p2 = static_cast<char*>(p2) + sizeOfDataType;
      p3 = static_cast<char*>(p3) + sizeOfDataType;
    }

    vesVector3f u = p2Vec3f - p1Vec3f;
    vesVector3f v = p3Vec3f - p1Vec3f;
    vesVector3f n;
    n[0] = u[1]*v[2] - u[2]*v[1];
    n[1] = u[2]*v[0] - u[0]*v[2];
    n[2] = u[0]*v[1] - u[1]*v[0];

    this->addAndUpdateNormal(triangleIndices->at(i+0), n[0], n[1], n[2],
                            data, stride, offset, sizeOfDataType);
    this->addAndUpdateNormal(triangleIndices->at(i+1), n[0], n[1], n[2],
                            data, stride, offset, sizeOfDataType);
    this->addAndUpdateNormal(triangleIndices->at(i+2), n[0], n[1], n[2],
                            data, stride, offset, sizeOfDataType);
  }

  for (unsigned int i = 0; i < count; ++i) {
    void* v1 = static_cast<char*>(data) + i * stride + offset;
    void* v2 = static_cast<char*>(v1) + sizeOfDataType;
    void* v3 = static_cast<char*>(v2) + sizeOfDataType;

    float &value1 = *(static_cast<float*>(v1));
    float &value2 = *(static_cast<float*>(v2));
    float &value3 = *(static_cast<float*>(v3));

    float length = value1 * value1 + value2 * value2 + value3 * value3;
    if (length > 0)
    {
      value1 /= sqrt(length);
      value2 /= sqrt(length);
      value3 /= sqrt(length);
    }
    else
    {
      value1 = 0;
      value2 = 0;
      value3 = 1;
    }
  }

  this->m_computeNormals = false;
}

#endif // VESGEOMETRYDATA_H

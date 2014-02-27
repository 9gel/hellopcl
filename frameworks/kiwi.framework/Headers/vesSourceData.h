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
/// \class vesSourceData
/// \ingroup ves
/// \see vesGeometryData vesMapper

#ifndef VESSOURCEDATA_H
#define VESSOURCEDATA_H

// VES includes
#include "vesGLTypes.h"
#include "vesMath.h"
#include "vesSetGet.h"
#include "vesVertexAttributeKeys.h"

// C++ includes
#include <map>
#include <vector>

/// Predefined vertex data structures
struct vesVertexDataP3f
{
  vesVector3f m_position;
};

struct vesVertexDataN3f
{
  vesVector3f m_normal;
};

struct vesVertexDataC3f
{
  vesVector3f m_color;
};

struct vesVertexDataC4f
{
  vesVector4f m_color;
};

struct vesVertexDataT2f
{
  vesVector2f m_textureCoordinate;
};

struct vesVertexDataT3f
{
  vesVector3f m_textureCoordinate;
};

struct vesVertexDataP3N3f
{
  vesVector3f m_position;
  vesVector3f m_normal;
};

struct vesVertexDataP3N3T3f
{
  vesVector3f m_position;
  vesVector3f m_normal;
  vesVector3f m_texureCoordinates;
};

struct vesVertexDataP3N3C3f
{
  vesVector3f m_position;
  vesVector3f m_normal;
  vesVector3f m_color;
};

struct vesVertexDataP3N3T3C3f
{
  vesVector3f m_position;
  vesVector3f m_normal;
  vesVector3f m_texureCoordinates;
  vesVector3f m_color;
};

struct vesVertexDataP3N3T3C3S3f
{
  vesVector3f m_position;
  vesVector3f m_normal;
  vesVector3f m_texureCoordinates;
  vesVector3f m_color;
  vesVector3f m_scalar;
};

struct vesVertexDataP3T3C3f
{
  vesVector3f m_position;
  vesVector3f m_texureCoordinates;
  vesVector3f m_color;
};

struct vesVertexDataf
{
  float m_scalar;
};

/// Base class for source data
class vesSourceData
{
public:

  vesTypeMacro(vesSourceData);

  struct AttributeData
  {
    /// Number of components per group
    unsigned int m_numberOfComponents;

    /// Type of data type (GL_FLOAT etc)
    unsigned int m_dataType;

    /// Size of data type
    unsigned int m_dataTypeSize;

    /// Specifies whether fixed-point data values should be normalized
    /// (true) or converted directly as fixed-point values (false)
    /// when they are accessed.
    bool m_normalized;

    /// Strides for each attribute.
    unsigned m_stride;

    /// Offset
    unsigned int m_offset;
  };

  typedef int Key;
  typedef std::map<Key, AttributeData> AttributeMap;
  typedef AttributeMap::iterator AttributeIterator;
  typedef AttributeMap::const_iterator AttributeConstIterator;

  virtual void* data() = 0;
  virtual unsigned int sizeOfArray() const = 0;
  virtual unsigned int sizeInBytes() const = 0;

  virtual bool hasKey(int key) const = 0;
  virtual std::vector<int> keys() const = 0;

  virtual unsigned int numberOfAttributes() const = 0;

  virtual unsigned int numberOfComponents(int key) const = 0;
  virtual bool setNumberOfComponents(int key, unsigned int count) = 0;

  virtual bool isAttributeNormalized(int key) const = 0;
  virtual bool setIsAttributeNormalized(int key, bool flag) = 0;

  virtual unsigned int sizeOfAttributeDataType(int key) const = 0;
  virtual bool setSizeOfAttributeDataType(int key, unsigned int size) = 0;

  virtual unsigned int attributeDataType(int key) const = 0;
  virtual bool setAttributeDataType(int key, unsigned int type) = 0;

  virtual int attributeOffset(int key) const = 0;
  virtual bool setAttributeOffset(int key, int offset) = 0;

  virtual int attributeStride(int key) const = 0;
  virtual bool setAttributeStride(int key, int stride) = 0;

  virtual void duplicateElements(const std::vector<unsigned int>& indices) = 0;
};

/// Generic implementation for the source data
template <typename T>
class vesGenericSourceData : public vesSourceData
{
public:
  vesTypeMacro(vesGenericSourceData);

  virtual ~vesGenericSourceData()
  {
  }

  virtual void duplicateElements(const std::vector<unsigned int>& indices)
  {
    size_t nIndices = indices.size();
    for (size_t i = 0; i < nIndices; ++i) {
      this->m_data.push_back(this->m_data[indices[i]]);
    }
  }


  /// Use this method with caution
  inline std::vector<T>& arrayReference()
  {
    return this->m_data;
  }

  inline const std::vector<T>& arrayReference() const
  {
    return this->m_data;
  }

  virtual void* data()
  {
    return &this->m_data.front();
  }

  virtual unsigned int sizeOfArray() const
  {
    return this->m_data.size();
  }

  virtual unsigned int sizeInBytes() const
  {
    unsigned int sizeInByes = 0;

    std::vector<int> keys = this->keys();
    std::vector<int>::const_iterator constItr = keys.begin();

    for (; constItr != keys.end(); ++constItr) {
      sizeInByes
        += this->numberOfComponents(*constItr) * this->sizeOfAttributeDataType(*constItr);
    }

    sizeInByes *= this->sizeOfArray();

    return sizeInByes;
  }

  virtual bool hasKey(int key) const
  {
    bool success = true;

    AttributeConstIterator constItr = this->m_attributeMap.find(key);

    if (constItr != this->m_attributeMap.end()) {
      return success;
    }

    return !success;
  }

  virtual std::vector<int> keys() const
  {
    std::vector<int> keys;

    AttributeConstIterator constItr = this->m_attributeMap.begin();

    for (; constItr != this->m_attributeMap.end(); ++constItr) {

      keys.push_back(constItr->first);
    }

    return keys;
  }

  virtual unsigned int numberOfAttributes() const
  {
    return static_cast<unsigned int>(this->m_attributeMap.size());
  }

  virtual unsigned int numberOfComponents(int key) const
  {
    AttributeConstIterator constItr = this->m_attributeMap.find(key);

    if (constItr != this->m_attributeMap.end()) {

      return constItr->second.m_numberOfComponents;
    }

    return 0;
  }

  virtual bool setNumberOfComponents(int key, unsigned int count)
  {
    bool success = true;

    this->m_attributeMap[key].m_numberOfComponents = count;

    return success;
  }

  virtual bool isAttributeNormalized(int key) const
  {
    AttributeConstIterator constItr
      = this->m_attributeMap.find(key);

    if (constItr != this->m_attributeMap.end()) {
      return constItr->second.m_normalized;
    }

    return 0;
  }

  virtual bool setIsAttributeNormalized(int key, bool flag)
  {
    bool success = true;

    this->m_attributeMap[key].m_normalized = flag;

    return success;
  }

  virtual unsigned int sizeOfAttributeDataType(int key) const
  {
    AttributeConstIterator constItr
      = this->m_attributeMap.find(key);

    if (constItr != this->m_attributeMap.end()) {
      return constItr->second.m_dataTypeSize;
    }

    return 0;
  }

  virtual bool setSizeOfAttributeDataType(int key, unsigned int size)
  {
    bool success = true;

    this->m_attributeMap[key].m_dataTypeSize = size;

    return success;
  }

  unsigned int attributeDataType(int key) const
  {
    AttributeConstIterator constItr
      = this->m_attributeMap.find(key);

    if (constItr != this->m_attributeMap.end()) {
      return constItr->second.m_dataType;
    }

    return 0;
  }

  virtual bool setAttributeDataType(int key, unsigned int type)
  {
    this->m_attributeMap[key].m_dataType = type;

    return true;
  }

  virtual int attributeOffset(int key) const
  {
    AttributeConstIterator constItr
      = this->m_attributeMap.find(key);

    if (constItr != this->m_attributeMap.end()) {
      return constItr->second.m_offset;
    }

    return -1;
  }

  virtual bool setAttributeOffset(int key, int offset)
  {
    this->m_attributeMap[key].m_offset = offset;

    return true;
  }

  virtual int attributeStride(int key) const
  {
    AttributeConstIterator constItr
      = this->m_attributeMap.find(key);

    if (constItr != this->m_attributeMap.end()) {
      return constItr->second.m_stride;
    }

    return -1;
  }

  virtual bool setAttributeStride(int key, int stride)
  {
    this->m_attributeMap[key].m_stride = stride;

    return true;
  }

  inline void pushBack(const T &value)
  {
    this->m_data.push_back(value);
  }

protected:
  /// Mesh data
  std::vector<T> m_data;

  AttributeMap m_attributeMap;
};

class vesSourceDataP3f : public vesGenericSourceData<vesVertexDataP3f>
{
public:
  vesTypeMacro(vesSourceDataP3f);

  vesSourceDataP3f() : vesGenericSourceData<vesVertexDataP3f>()
  {
    const int totalNumberOfFloats = 3;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::Position, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::Position, 0);
    this->setAttributeStride(vesVertexAttributeKeys::Position, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::Position, 3);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Position, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Position, false);
  }
};

class vesGenericSourceData3f : public vesGenericSourceData<vesVector3f>
{
public:
  vesTypeMacro(vesGenericSourceData3f);

  vesGenericSourceData3f(int key) : vesGenericSourceData<vesVector3f>()
  {
    const int totalNumberOfFloats = 3;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(key, vesDataType::Float);
    this->setAttributeOffset(key, 0);
    this->setAttributeStride(key, stride);
    this->setNumberOfComponents(key, 3);
    this->setSizeOfAttributeDataType(key, sizeof(float));
    this->setIsAttributeNormalized(key, false);
  }
};

class vesGenericSourceData1f : public vesGenericSourceData<float>
{
public:
  vesTypeMacro(vesGenericSourceData1f);

  vesGenericSourceData1f(int key) : vesGenericSourceData<float>()
  {
    this->setAttributeDataType(key, vesDataType::Float);
    this->setAttributeOffset(key, 0);
    this->setAttributeStride(key, sizeof(float));
    this->setNumberOfComponents(key, 1);
    this->setSizeOfAttributeDataType(key, sizeof(float));
    this->setIsAttributeNormalized(key, false);
  }
};

class vesSourceDataf : public vesGenericSourceData<vesVertexDataf>
{
public:
  vesTypeMacro(vesSourceDataf);

  vesSourceDataf() : vesGenericSourceData<vesVertexDataf>()
  {
    const int totalNumberOfFloats = 1;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::Scalar, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::Scalar, 0);
    this->setAttributeStride(vesVertexAttributeKeys::Scalar, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::Scalar, 1);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Scalar, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Scalar, false);
  }
};

class vesSourceDataN3f : public vesGenericSourceData<vesVertexDataN3f>
{
public:
  vesTypeMacro(vesSourceDataN3f);

  vesSourceDataN3f() : vesGenericSourceData<vesVertexDataN3f>()
  {
    const int totalNumberOfFloats = 3;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::Normal, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::Normal, 0);
    this->setAttributeStride(vesVertexAttributeKeys::Normal, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::Normal, 3);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Normal, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Normal, false);
  }
};

class vesSourceDataC3f : public vesGenericSourceData<vesVertexDataC3f>
{
public:
  vesTypeMacro(vesSourceDataC3f);

  vesSourceDataC3f() : vesGenericSourceData<vesVertexDataC3f>()
  {
    const int totalNumberOfFloats = 3;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::Color, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::Color, 0);
    this->setAttributeStride(vesVertexAttributeKeys::Color, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::Color, 3);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Color, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Color, false);
  }
};

class vesSourceDataC4f : public vesGenericSourceData<vesVertexDataC4f>
{
public:
  vesTypeMacro(vesSourceDataC4f);

  vesSourceDataC4f() : vesGenericSourceData<vesVertexDataC4f>()
  {
    const int totalNumberOfFloats = 4;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::Color, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::Color, 0);
    this->setAttributeStride(vesVertexAttributeKeys::Color, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::Color, 4);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Color, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Color, false);
  }
};

class vesSourceDataT2f : public vesGenericSourceData<vesVertexDataT2f>
{
public:
  vesTypeMacro(vesSourceDataT2f);

  vesSourceDataT2f() : vesGenericSourceData<vesVertexDataT2f>()
  {
    const int totalNumberOfFloats = 2;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::TextureCoordinate, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::TextureCoordinate, 0);
    this->setAttributeStride(vesVertexAttributeKeys::TextureCoordinate, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::TextureCoordinate, 2);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::TextureCoordinate, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::TextureCoordinate, false);
  }
};

class vesSourceDataT3f : public vesGenericSourceData<vesVertexDataT3f>
{
public:
  vesTypeMacro(vesSourceDataT3f);

  vesSourceDataT3f() : vesGenericSourceData<vesVertexDataT3f>()
  {
    const int totalNumberOfFloats = 3;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::TextureCoordinate, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::TextureCoordinate, 0);
    this->setAttributeStride(vesVertexAttributeKeys::TextureCoordinate, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::TextureCoordinate, 3);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::TextureCoordinate, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::TextureCoordinate, false);
  }
};

class vesSourceDataP3N3f : public vesGenericSourceData<vesVertexDataP3N3f>
{
public:
  vesTypeMacro(vesSourceDataP3N3f);

  vesSourceDataP3N3f() : vesGenericSourceData<vesVertexDataP3N3f>()
  {
    const int totalNumberOfFloats = 6;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::Position, vesDataType::Float);
    this->setAttributeDataType(vesVertexAttributeKeys::Normal, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::Position, 0);
    this->setAttributeOffset(vesVertexAttributeKeys::Normal, 12);
    this->setAttributeStride(vesVertexAttributeKeys::Position, stride);
    this->setAttributeStride(vesVertexAttributeKeys::Normal, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::Position, 3);
    this->setNumberOfComponents(vesVertexAttributeKeys::Normal, 3);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Position, sizeof(float));
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Normal, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Position, false);
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Normal, false);
  }
};

class vesSourceDataP3N3C3f : public vesGenericSourceData<vesVertexDataP3N3C3f>
{
public:
  vesTypeMacro(vesSourceDataP3N3C3f);

  vesSourceDataP3N3C3f() : vesGenericSourceData<vesVertexDataP3N3C3f>()
  {
    const int totalNumberOfFloats = 9;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::Position, vesDataType::Float);
    this->setAttributeDataType(vesVertexAttributeKeys::Normal, vesDataType::Float);
    this->setAttributeDataType(vesVertexAttributeKeys::Color, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::Position, 0);
    this->setAttributeOffset(vesVertexAttributeKeys::Normal, 12);
    this->setAttributeOffset(vesVertexAttributeKeys::Color, 24);
    this->setAttributeStride(vesVertexAttributeKeys::Position, stride);
    this->setAttributeStride(vesVertexAttributeKeys::Normal, stride);
    this->setAttributeStride(vesVertexAttributeKeys::Color, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::Position, 3);
    this->setNumberOfComponents(vesVertexAttributeKeys::Normal, 3);
    this->setNumberOfComponents(vesVertexAttributeKeys::Color, 3);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Position, sizeof(float));
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Normal, sizeof(float));
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Color, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Position, false);
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Normal, false);
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Color, false);
  }
};

class vesSourceDataP3T3C3f : public vesGenericSourceData<vesVertexDataP3T3C3f>
{
public:
  vesTypeMacro(vesSourceDataP3T3C3f);

  vesSourceDataP3T3C3f() : vesGenericSourceData<vesVertexDataP3T3C3f>()
  {
    const int totalNumberOfFloats = 9;
    const int stride = sizeof(float) * totalNumberOfFloats;

    this->setAttributeDataType(vesVertexAttributeKeys::Position, vesDataType::Float);
    this->setAttributeDataType(vesVertexAttributeKeys::TextureCoordinate, vesDataType::Float);
    this->setAttributeDataType(vesVertexAttributeKeys::Color, vesDataType::Float);
    this->setAttributeOffset(vesVertexAttributeKeys::Position, 0);
    this->setAttributeOffset(vesVertexAttributeKeys::TextureCoordinate, 12);
    this->setAttributeOffset(vesVertexAttributeKeys::Color, 24);
    this->setAttributeStride(vesVertexAttributeKeys::Position, stride);
    this->setAttributeStride(vesVertexAttributeKeys::TextureCoordinate, stride);
    this->setAttributeStride(vesVertexAttributeKeys::Color, stride);
    this->setNumberOfComponents(vesVertexAttributeKeys::Position, 3);
    this->setNumberOfComponents(vesVertexAttributeKeys::TextureCoordinate, 3);
    this->setNumberOfComponents(vesVertexAttributeKeys::Color, 3);
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Position, sizeof(float));
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::TextureCoordinate, sizeof(float));
    this->setSizeOfAttributeDataType(vesVertexAttributeKeys::Color, sizeof(float));
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Position, false);
    this->setIsAttributeNormalized(vesVertexAttributeKeys::TextureCoordinate, false);
    this->setIsAttributeNormalized(vesVertexAttributeKeys::Color, false);
  }
};

#endif // VESSOURCEDATA_H

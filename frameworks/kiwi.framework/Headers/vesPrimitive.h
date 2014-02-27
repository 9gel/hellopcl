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

#ifndef VESPRIMITIVE_H
#define VESPRIMITIVE_H

// VES includes
#include "vesSetGet.h"

// C++ includes
#include <vector>

class vesBaseIndices
{
public:
  vesTypeMacro(vesBaseIndices);

  virtual void* dataPointer() const = 0;
  virtual unsigned int sizeOfDataType() const = 0;
  virtual unsigned int size() const = 0;
};

template<typename T>
class vesIndices : public vesBaseIndices
{
public:
  typedef std::vector<T> Indices;

  vesTypeMacro(vesIndices);

  vesIndices() :
    m_dataTypeSize(sizeof(T))
  {
  }

  virtual void* dataPointer() const
  {
    return (void*)&this->m_indices.front();
  }

  virtual unsigned int sizeOfDataType() const
  {
    return this->m_dataTypeSize;
  }

  virtual unsigned int size() const
  {
    return static_cast<unsigned int>(this->m_indices.size());
  }

  /// Helper functions
  inline void pushBackIndices(T i1)
  {
    this->m_indices.push_back(i1);
  }

  inline void pushBackIndices(T i1, T i2)
  {
    this->m_indices.push_back(i1);
    this->m_indices.push_back(i2);
  }

  inline void pushBackIndices(T i1, T i2, T i3)
  {
    this->m_indices.push_back(i1);
    this->m_indices.push_back(i2);
    this->m_indices.push_back(i3);
  }

  /// Use this method with caution
  inline T* data()
  {
    return &this->m_indices.front();
  }

  inline const T* data() const
  {
    return &this->m_indices.front();
  }

  inline T at(unsigned int index)
  {
    return this->m_indices[index];
  }

  inline const T& at(unsigned int index) const
  {
    return this->m_indices[index];
  }

  /// Use this method with caution
  inline std::vector<T>* indices()
  {
    return &this->m_indices;
  }

  inline const std::vector<T>* indices() const
  {
    return &this->m_indices;
  }

private:
  /// Size of indices data type
  unsigned int m_dataTypeSize;

  Indices m_indices;
};


class vesPrimitive
{
public:
  vesTypeMacro(vesPrimitive);

  vesPrimitive() :
    m_indexCount(0),
    m_primitiveType(0),
    m_indicesValueType(0)
  {
  }

  inline void setVesIndices(vesSharedPtr<vesBaseIndices> primIndices)
  {
    this->m_vesIndices = primIndices;
  }

  inline vesSharedPtr<vesBaseIndices> getVesIndices()
  {
    return this->m_vesIndices;
  }

  inline unsigned int size() const
  {
    return this->numberOfIndices();
  }

  inline unsigned int sizeInBytes() const
  {
    return (this->m_vesIndices
      ? (this->m_vesIndices->sizeOfDataType()
         * this->m_vesIndices->size())
      : 0);
  }

  inline unsigned int numberOfIndices() const
  {
    return (this->m_vesIndices
      ? static_cast<unsigned int>(this->m_vesIndices->size())
      : 0);
  }

  inline unsigned int primitiveType() const
  {
    return this->m_primitiveType;
  }

  inline bool setPrimitiveType(unsigned int type)
  {
    this->m_primitiveType = type;
    return true;
  }

  inline unsigned int indicesValueType() const
  {
    return this->m_indicesValueType;
  }

  inline bool setIndicesValueType(unsigned int type)
  {
    this->m_indicesValueType = type;
    return true;
  }

  inline unsigned int indexCount() const
  {
    return this->m_indexCount;
  }

  inline bool setIndexCount(unsigned int count)
  {
    bool success = true;
    this->m_indexCount = count;
    return success;
  }

  /// \NOTE Use this method with caution
  inline void* data()
  {
    return (this->m_vesIndices
      ? (void*)(this->m_vesIndices->dataPointer())
      : 0);
  }

  /// Use this method with caution
  inline const void* data() const
  {
    return (this->m_vesIndices
      ? (void*)(this->m_vesIndices->dataPointer())
      : 0);
  }

  /// Use this method with caution
  inline unsigned int sizeOfDataType() const
  {
    return (this->m_vesIndices
      ? this->m_vesIndices->sizeOfDataType()
      : 0);
  }


private:
  /// Number of indices used to draw elements
  int m_indexCount;

  /// Primitive type
  unsigned int m_primitiveType;

  /// Primitive indices value type
  unsigned int m_indicesValueType;

  /// Primitive indices
  vesSharedPtr<vesBaseIndices> m_vesIndices;
};

#endif // VESPRIMITIVE_H

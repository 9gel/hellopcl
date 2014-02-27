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

#ifndef VESIMAGE_H
#define VESIMAGE_H

// VES includes
#include "vesGLTypes.h"
#include "vesSetGet.h"

// C/C++ includes
#include <cstdlib>
#include <cstring>

class vesImage
{
public:
  vesTypeMacro(vesImage);

  vesImage() :
    m_width(0),
    m_height(0),
    m_depth(0),
    m_pixelFormat(vesColorDataType::PixelFormatNone),
    m_pixelDataType(vesColorDataType::PixelDataTypeNone),
    m_data(0x0)
  {
  }

  ~vesImage()
    {
    if (this->m_data) {
      this->releaseData();
      }
    }

  /// Set image width
  inline void setWidth(int width) { this->m_width = width; }

  /// Get image width
  inline int width() const { return this->m_width; }

  /// Set image height
  inline void setHeight(int height) { this->m_height = height; }

  /// Get image height
  inline int height() const { return this->m_height; }

  /// Set image depth
  inline void setDepth(int depth) { this->m_depth = depth; }

  /// Get image depth
  inline int depth() const { return this->m_depth; }

  /// Set pixel format. It is important that this is done at the time of
  /// initialization.
  inline void setPixelFormat(vesColorDataType::PixelFormat format)
    {
    this->m_pixelFormat = format;
    }

  /// Get pixel format
  inline vesColorDataType::PixelFormat pixelFormat() const
    {
    return this->m_pixelFormat;
    }

  /// Set pixel data type. It is important that this is done at the time of
  /// initialization.
  inline void setPixelDataType(vesColorDataType::PixelDataType type)
    {
    this->m_pixelDataType = type;
    }

  /// Get pixel data type
  inline vesColorDataType::PixelDataType pixelDataType() const
    {
    return this->m_pixelDataType;
    }

  /// Set pixel data
  inline bool setData(const void *data, unsigned int size)
    {
    bool retval = false;

    if(!data)
      {
      return retval;
      }

    if (!this->allocate(size)) {
      return retval;
      }

    // All is good
    retval = true;

    memcpy(this->m_data, data, size);

    return retval;
    }

  /// Get pixel data
  void* data() const
    {
    return this->m_data;
    }

protected:
  int m_width;
  int m_height;
  int m_depth;

  vesColorDataType::PixelFormat m_pixelFormat;
  vesColorDataType::PixelDataType m_pixelDataType;

  void *m_data;

  inline bool allocate(unsigned int size)
    {
    this->releaseData();

    // If the function failed to allocate the requested block of memory,
    // a null pointer is returned
    this->m_data = malloc(size);

    if (this->m_data) {
      return true;
      }

    return false;
    }

  inline void releaseData()
    {
    if (this->m_data) {
      free(this->m_data);
      }
    }
};

#endif // VESIMAGE_H

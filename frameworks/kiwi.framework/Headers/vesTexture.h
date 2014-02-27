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
/// \class vesTexture
/// \ingroup ves
/// \see vesMaterialAttribute vesMaterial

#ifndef __vesTexture_h
#define __vesTexture_h

#include "vesMaterial.h"

// VES includes.
#include "vesGLTypes.h"
#include "vesImage.h"
#include "vesSetGet.h"

class vesTexture : public vesMaterialAttribute
{
public:
  vesTypeMacro(vesTexture);

  enum InternalFormat
  {
    Alpha           = GL_ALPHA,
    Luminance       = GL_LUMINANCE,
    LuminanceAlpha  = GL_LUMINANCE_ALPHA,
    RGB             = GL_RGB,
    RGBA            = GL_RGBA
  };

  vesTexture();
  virtual ~vesTexture();

  virtual void bind(const vesRenderState &renderState);
  virtual void unbind(const vesRenderState &renderState);
  virtual void setup(const vesRenderState &renderState);

  void setImage(vesSharedPtr<vesImage> image);
  vesSharedPtr<vesImage> image() const;

  void setTextureUnit(unsigned int unit);
  unsigned int textureUnit() const { return this->m_textureUnit; }

  /// Set width of the texture, used as fallback when no image is attached.
  bool setWidth(int width);
  int width() const;

  /// Set height of the texture, used as fallback when no image is attached.
  bool setHeight(int height);
  int height() const;

  /// Set depth of the texture, used as fallback when no image is attached.
  bool setDepth(int depth);
  int depth() const;

  unsigned int textureHandle() const  { return this->m_textureHandle; }

  /// Set pixel format type, used as fallback when no image is attached.
  bool setPixelFormat(vesColorDataType::PixelFormat pixelFormat);
  vesColorDataType::PixelFormat pixelFormat() const;

  /// Set internal format type. In general this is computed from the image attached.
  bool setInternalFormat(int internalFormat);
  int internalFormat() const;

  /// Set pixel data type, In general this is computed from the image attached.
  bool setPixelDataType(vesColorDataType::PixelDataType pixelDataType);
  vesColorDataType::PixelDataType pixelDataType() const;

protected:
  void computeInternalFormatUsingImage();
  void updateDimensions();

  vesSharedPtr<vesImage> m_image;

  bool m_hasImage;

  int m_width;
  int m_height;
  int m_depth;

  unsigned int m_textureHandle;
  unsigned int m_textureUnit;

  vesColorDataType::PixelFormat m_pixelFormat;
  vesColorDataType::PixelDataType m_pixelDataType;

  int m_internalFormat;
};
#endif // __vesTexture_h

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
/// \class vesFBO
/// \ingroup ves
/// \see vesObject

#ifndef VESFBO_H
#define VESFBO_H

#include "vesObject.h"

// VES includes
#include "vesGL.h"
#include "vesSetGet.h"

// Forward declarations
class vesRenderState;
class vesTexture;

class vesFBO : public vesObject
{
public:
  vesTypeMacro(vesFBO);

  enum AttachmentType
  {
    ColorAttachment0  = GL_COLOR_ATTACHMENT0,
    DepthAttachment   = GL_DEPTH_ATTACHMENT
  };

  vesFBO();
  virtual ~vesFBO();

  bool setTexture(AttachmentType type, vesTexture *texture);
  vesTexture* texture(AttachmentType type);
  const vesTexture* texture(AttachmentType type) const;

  void setWidth (int width);
  int width() const;

  void setHeight (int height);
  int height() const;

  unsigned int frameBufferHandle();

  virtual void setup(vesRenderState &renderState);
  virtual void render(vesRenderState &renderState);
  virtual void remove(vesRenderState &renderState);

protected:
   virtual void createFBO(vesRenderState &renderState);
   virtual void deleteFBO(vesRenderState &renderState);

  class vesInternal;
  vesInternal *m_internal;
};


#endif // VESFBO_H

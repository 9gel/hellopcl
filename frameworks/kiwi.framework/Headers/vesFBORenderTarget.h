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
/// \class vesFBORenderTarget
/// \ingroup ves
/// \see vesRenderTarget

#ifndef VESFBORENDERTARGET_H
#define VESFBORENDERTARGET_H

#include "vesRenderTarget.h"

// VES includes
#include "vesFBO.h"
#include "vesSetGet.h"

// Forward declarations
class vesTexture;

class vesFBORenderTarget : public vesRenderTarget
{
public:
  vesTypeMacro(vesFBORenderTarget);

  vesFBORenderTarget();
  virtual ~vesFBORenderTarget();

  virtual bool attach(vesFBO::AttachmentType type, vesTexture *texture);

protected:
  vesFBO *m_fbo;
};

#endif // VESFBORENDERTARGET_H

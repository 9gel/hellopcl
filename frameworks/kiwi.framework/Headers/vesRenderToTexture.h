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
/// \class vesRenderToTexture
/// \ingroup ves
/// \see vesFBORenderTarget vesFBO

#ifndef VESRENDERTOTEXTURE_H
#define VESRENDERTOTEXTURE_H

// VES includes
#include "vesFBORenderTarget.h"
#include "vesSetGet.h"

class vesRenderToTexture : public vesFBORenderTarget
{
public:
  vesTypeMacro(vesRenderToTexture);
  vesRenderToTexture();
  virtual ~vesRenderToTexture();

  bool setColorTexture(vesTexture *texture);
  vesTexture* colorTexture();
  const vesTexture* colorTexture() const;

  bool setDepthTexture(vesTexture *texture);
  vesTexture* depthTexture();
  const vesTexture* depthTexture() const;

protected:
  void setup (vesRenderState &renderState);
  void render(vesRenderState &renderState);
  void remove(vesRenderState &renderState);
};


#endif // VESRENDERTOTEXTURE_H

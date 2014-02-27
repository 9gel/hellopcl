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
/// \class vesBlend
/// \ingroup ves
/// \see vesMaterial vesMaterialAttribute vesBlendFunction

#ifndef VESBLEND_H
#define VESBLEND_H

#include "vesMaterial.h"

// VES includes.
#include "vesBlendFunction.h"
#include "vesSetGet.h"

class vesBlend : public vesMaterialAttribute
{
public:
  vesTypeMacro(vesBlend);

  vesBlend();
  virtual ~vesBlend();

  void setBlendFunction(const vesBlendFunction& blendFunction);
  vesBlendFunction blendFunction();
  const vesBlendFunction& blendFunction() const;

  virtual void bind (const vesRenderState &renderState);
  virtual void unbind (const vesRenderState &renderState);

protected:
  bool m_wasEnabled;
  vesBlendFunction m_blendFunction;
};


#endif // VESBLEND_H

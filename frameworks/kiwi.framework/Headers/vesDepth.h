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
/// \class vesDepth
/// \ingroup ves
/// \see vesMaterialAttribute vesMaterial

#ifndef VESDEPTH_H
#define VESDEPTH_H

#include "vesMaterial.h"

// VES includes
#include "vesSetGet.h"

class vesDepth : public vesMaterialAttribute
{
public:
  vesTypeMacro(vesDepth);

  vesDepth();
  virtual ~vesDepth();

  inline void setWriteMask(bool mask) { this->m_depthWriteMask = mask; }
  inline bool writeMask() const { return this->m_depthWriteMask; }

  virtual void bind (const vesRenderState &renderState);
  virtual void unbind (const vesRenderState &renderState);

protected:
  bool m_wasEnabled;
  bool m_previousDepthWriteMask;
  bool m_depthWriteMask;
};

#endif // VESDEPTH_H

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

#ifndef VESOBJECT_H
#define VESOBJECT_H

// VES includes
#include "vesSetGet.h"

class vesObject
{
public:
  vesTypeMacro(vesObject);

  vesObject() :
    m_dirtyState(true)
  {
  }

  virtual ~vesObject() {}

  void setDirty(const bool &value) { this->m_dirtyState = value; }
  void setDirtyStateOn() { this->setDirty(true); }
  void setDirtyStateOff() { this->setDirty(false); }
  bool dirtyState() { return this->m_dirtyState; }
  const bool& dirtyState() const { return this->m_dirtyState; }

protected:
  bool m_dirtyState;
};


#endif // VESOBJECT_H

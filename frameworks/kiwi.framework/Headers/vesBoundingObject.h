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
/// \class vesBoundingObject
/// \ingroup ves
/// \see vesNode

#ifndef __vesBoundingObject_h
#define __vesBoundingObject_h

#include "vesObject.h"

// VES includes
#include "vesMath.h"
#include "vesSetGet.h"

class vesBoundingObject : public vesObject
{
public:
  vesTypeMacro(vesBoundingObject);

  vesBoundingObject();
  virtual ~vesBoundingObject();

  virtual void computeBounds() = 0;

  const vesVector3f& boundsMinimum() const {return this->m_boundsMinimum;}
  const vesVector3f& boundsMaximum() const {return this->m_boundsMaximum;}

  const vesVector3f& boundsCenter() const {return this->m_boundsCenter;}
  const vesVector3f& boundsSize() const {return this->m_boundsSize;}

  void setBoundsCenter(const vesVector3f &center);
  void setBoundsSize(const vesVector3f &size);

  void  setBounds(vesVector3f min, vesVector3f max);

  float boundsRadius();

  void setBoundsDirty(bool value);
  bool boundsDirty() { return this->m_boundsDirty; }
  bool boundsDirty() const { return this->m_boundsDirty; }

  void resetBounds();

protected:
  bool m_boundsDirty;

  vesVector3f m_boundsCenter;
  vesVector3f m_boundsSize;

  vesVector3f m_boundsMinimum;
  vesVector3f m_boundsMaximum;
};

#endif // __vesBoundingObject_h

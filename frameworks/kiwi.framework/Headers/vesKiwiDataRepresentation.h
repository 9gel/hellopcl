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
/// \class vesKiwiDataRepresentation
/// \ingroup KiwiPlatform
#ifndef __vesKiwiDataRepresentation_h
#define __vesKiwiDataRepresentation_h

// VES includes
#include "vesMath.h"
#include "vesSharedPtr.h"
#include "vesSetGet.h"

class vesKiwiColorMapCollection;
class vesRenderer;
class vesActor;
class vtkTransform;

class vesKiwiDataRepresentation
{
public:

  vesTypeMacro(vesKiwiDataRepresentation);

  vesKiwiDataRepresentation();
  virtual ~vesKiwiDataRepresentation() {}

  virtual void addSelfToRenderer(vesSharedPtr<vesRenderer> renderer) = 0;
  virtual void removeSelfFromRenderer(vesSharedPtr<vesRenderer> renderer) = 0;
  virtual void willRender(vesSharedPtr<vesRenderer> renderer);

  void setColorMapCollection(vesSharedPtr<vesKiwiColorMapCollection> collection);
  vesSharedPtr<vesKiwiColorMapCollection> colorMapCollection() const;

  static void setTransformOnActor(vesSharedPtr<vesActor> actor, vtkTransform* transform);

private:

  vesSharedPtr<vesKiwiColorMapCollection> mColorMapCollection;
  vesKiwiDataRepresentation(const vesKiwiDataRepresentation&); // Not implemented
  void operator=(const vesKiwiDataRepresentation&); // Not implemented
};

#endif

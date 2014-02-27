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
/// \class vesKiwiText2DRepresentation
/// \ingroup KiwiPlatform
#ifndef __vesKiwiText2DRepresentation_h
#define __vesKiwiText2DRepresentation_h

#include "vesKiwiImagePlaneDataRepresentation.h"


class vtkImageData;

class vesKiwiText2DRepresentation : public vesKiwiImagePlaneDataRepresentation
{
public:

  vesTypeMacro(vesKiwiText2DRepresentation);

  vesKiwiText2DRepresentation();
  ~vesKiwiText2DRepresentation();

  void setText(const std::string& text);

  virtual void willRender(vesSharedPtr<vesRenderer> renderer);

  void setWorldAnchorPointEnabled(bool enabled);
  bool worldAnchorPointEnabled() const;

  void setWorldAnchorPoint(vesVector3f worldPoint);
  vesVector3f worldAnchorPoint() const;

  void setAnchorOffset(double offset);
  double anchorOffset() const;

  void setDisplayPosition(vesVector2f displayPosition);
  vesVector2f displayPosition() const;

  /// Return the width of the texture used by this text annotation.
  int textWidth();

private:

  vesKiwiText2DRepresentation(const vesKiwiText2DRepresentation&); // Not implemented
  void operator=(const vesKiwiText2DRepresentation&); // Not implemented


  class vesInternal;
  vesInternal* Internal;
};


#endif

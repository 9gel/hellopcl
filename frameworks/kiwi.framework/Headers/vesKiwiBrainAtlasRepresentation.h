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
/// \class vesKiwiBrainAtlasRepresentation
/// \ingroup KiwiPlatform
#ifndef __vesKiwiBrainAtlasRepresentation_h
#define __vesKiwiBrainAtlasRepresentation_h

#include "vesKiwiWidgetRepresentation.h"

class vesShaderProgram;
class vtkPlane;

class vesKiwiBrainAtlasRepresentation : public vesKiwiWidgetRepresentation
{
public:

  vesTypeMacro(vesKiwiBrainAtlasRepresentation);

  typedef vesKiwiWidgetRepresentation Superclass;
  vesKiwiBrainAtlasRepresentation();
  ~vesKiwiBrainAtlasRepresentation();

  void initializeWithShader(vesSharedPtr<vesShaderProgram> geometryShader,
                            vesSharedPtr<vesShaderProgram> textureShader,
                            vesSharedPtr<vesShaderProgram> clipShader);

  void loadData(const std::string& filename);

  void setClipPlane(vtkPlane* plane);

  virtual void addSelfToRenderer(vesSharedPtr<vesRenderer> renderer);
  virtual void removeSelfFromRenderer(vesSharedPtr<vesRenderer> renderer);
  virtual void willRender(vesSharedPtr<vesRenderer> renderer);

  virtual void showTextLabel(int modelIndex);
  virtual void hideTextLabel();
  virtual int findTappedModel(int displayX, int displayY);
  virtual bool hideModel(int displayX, int displayY);
  virtual bool selectModel(int displayX, int displayY);
  virtual void deselectModel();
  virtual bool toggleSkinOpacity(int displayX, int displayY);

  virtual bool handleSingleTouchTap(int displayX, int displayY);
  virtual bool handleDoubleTap(int displayX, int displayY);
  virtual bool handleLongPress(int displayX, int displayY);

  virtual std::vector<std::string> actions() const;
  virtual bool handleAction(const std::string& action);

  // show all models again
  virtual void showHiddenModels();

protected:


private:

  vesKiwiBrainAtlasRepresentation(const vesKiwiBrainAtlasRepresentation&); // Not implemented
  void operator=(const vesKiwiBrainAtlasRepresentation&); // Not implemented

  class vesInternal;
  vesInternal* Internal;
};

#endif

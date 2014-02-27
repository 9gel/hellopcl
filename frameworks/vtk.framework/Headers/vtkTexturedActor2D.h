/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkTexturedActor2D.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkTexturedActor2D - actor that draws 2D data with texture support
// .SECTION Description
// vtkTexturedActor2D is an Actor2D which has additional support for
// textures, just like vtkActor. To use textures, the geometry must have
// texture coordinates, and the texture must be set with SetTexture().

// .SECTION See Also
// vtkActor2D vtkProp vtkMapper2D vtkProperty2D

#ifndef __vtkTexturedActor2D_h
#define __vtkTexturedActor2D_h

#include "vtkRenderingCoreModule.h" // For export macro
#include "vtkActor2D.h"

class vtkProp;
class vtkTexture;
class vtkViewport;
class vtkWindow;

class VTKRENDERINGCORE_EXPORT vtkTexturedActor2D : public vtkActor2D
{
public:
  static vtkTexturedActor2D* New();
  void PrintSelf(ostream& os, vtkIndent indent);
  vtkTypeMacro(vtkTexturedActor2D, vtkActor2D);

  // Description:
  // Set/Get the texture object to control rendering texture maps.  This will
  // be a vtkTexture object. An actor does not need to have an associated
  // texture map and multiple actors can share one texture.
  virtual void SetTexture(vtkTexture* texture);
  vtkGetObjectMacro(Texture, vtkTexture);

  // Description:
  // Release any graphics resources that are being consumed by this actor.
  // The parameter window could be used to determine which graphic
  // resources to release.
  virtual void ReleaseGraphicsResources(vtkWindow* win);

  // Description:
  // Support the standard render methods.
  virtual int RenderOverlay(vtkViewport* viewport);
  virtual int RenderOpaqueGeometry(vtkViewport* viewport);
  virtual int RenderTranslucentPolygonalGeometry(vtkViewport* viewport);

  // Description:
  // Return this object's modified time.
  virtual unsigned long int GetMTime();

  // Description:
  // Shallow copy of this vtkTexturedActor2D. Overrides vtkActor2D method.
  virtual void ShallowCopy(vtkProp* prop);

protected:
  vtkTexturedActor2D();
  ~vtkTexturedActor2D();

  vtkTexture* Texture;

private:
  vtkTexturedActor2D(const vtkTexturedActor2D&); // Not implemented.
  void operator=(const vtkTexturedActor2D&); // Not implemented.
};

#endif


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
/// \class vesKiwiBaseApp
/// \ingroup KiwiPlatform
/// \brief A base class for implementing an application with a single renderer.
//
/// vesKiwiBaseApp can be subclassed to create an application that has
/// a single renderer and camera.  vesKiwiBaseApp manages the renderer,
/// camera, and translates touch events into camera movements.
#ifndef __vesKiwiBaseApp_h
#define __vesKiwiBaseApp_h

#include "vesMath.h"
#include "vesSharedPtr.h"
#include "vesSetGet.h"

#include <string>

class vesCamera;
class vesOpenGLSupport;
class vesRenderer;
class vesShader;
class vesShaderProgram;
class vesUniform;
class vesVertexAttribute;
class vesKiwiCameraInteractor;

class vesKiwiBaseApp
{
public:

  vesTypeMacro(vesKiwiBaseApp);

  vesKiwiBaseApp();
  virtual ~vesKiwiBaseApp();

  /// This method makes OpenGL calls to perform initializations that must
  /// occur while there is a valid GL context.  This method initilizes the
  /// instance of vesOpenGLSupport returned glSupport().  Preferably, this
  /// method should be called right after performing the platform specific
  /// initialization of the GL context.
  virtual void initGL();

  /// Call vesRenderer::render() on the vesRenderer owned by this app object.
  /// willRender() is called at the start of this method, and didRender() is called
  /// at the end.  Subclasses can override those methods to implement custom
  /// behavior, rather than overriding this method.
  void render();

  /// Reset the camera to a default viewing direction and position.
  /// The camera view direction is reset to the world +Z axis and the view up
  /// direction is set to +Y.  The camera focal point is set to the center of
  /// the bounds of all visible objects in the renderer and the camera is
  /// dollied away from the focal point so that all objects are visible in the view.
  /// \see vesCamera::resetCamera()
  virtual void resetView();

  /// Reset the camera to a default position using the given view direction
  /// and view up vector. The camera focal point is set to the center of
  /// the bounds of all visible objects in the renderer and the camera is
  /// dollied away from the focal point so that all objects are visible in the view.
  /// \see vesCamera::resetCamera()
  virtual void resetView(const vesVector3f& viewDirection, const vesVector3f& viewUp);

  /// Resizes the renderer to the given width and height.
  virtual void resizeView(int width, int height);

  /// Handle a two touch pan gesture.  The implementation translates the movement
  /// in 2D to a 3D translation to be applied to the camera position and focal point.
  virtual void handleTwoTouchPanGesture(double x0, double y0, double x1, double y1);

  /// Handle a single touch pan gesture.  The implementation translates the movement
  /// in 2D into a 3D camera rotation.
  /// \see  vesCamera::azimuth()
  /// \see  vesCamera::elevation()
  virtual void handleSingleTouchPanGesture(double deltaX, double deltaY);

  /// Handle a two touch pinch gesture.  The implementation calls vesCamera::dolly()
  /// with the given scale factor.  The scale factor represents a percentage of
  /// the current view diagonal using a value between -1.0 and 1.0.
  virtual void handleTwoTouchPinchGesture(double scale);

  /// Handle a two touch rotation gesture.  The implementation rotates the
  /// camera about the view direction.  Rotation is given in radians.
  /// \see vesCamera::roll()
  virtual void handleTwoTouchRotationGesture(double rotation);

  /// Handle a single touch down event.  The location of the touch down event
  /// is given in 2D screen coordinates.  The default implementation is a no-op.
  virtual void handleSingleTouchDown(int displayX, int displayY);

  /// Handle a single touch up event.  The default implementation is a no-op.
  virtual void handleSingleTouchUp();

  /// Handle a single touch tap event.  The default implementation is a no-op.
  virtual void handleSingleTouchTap(int displayX, int displayY);

  /// Handle a double tap event.  The default implementation is a no-op.
  virtual void handleDoubleTap(int displayX, int displayY);

  /// Handle a long press event.  The default implementation is a no-op.
  virtual void handleLongPress(int displayX, int displayY);

  /// Set the background color of the renderer.
  void setBackgroundColor(double r, double g, double b);

  /// Get the width of the renderer.
  /// \see resizeView()
  int viewWidth() const;

  /// Get the height of the renderer.
  /// \see resizeView()
  int viewHeight() const;

  /// Get the current camera position.
  vesVector3f cameraPosition() const;

  /// Get the current camera focal point.
  vesVector3f cameraFocalPoint() const;

  /// Get the current camera view up direction.
  vesVector3f cameraViewUp() const;

  /// Set the camera position.
  void setCameraPosition(const vesVector3f& position);

  /// Set the camera focal point.
  void setCameraFocalPoint(const vesVector3f& focalPoint);

  /// Set the camera view up direction.
  void setCameraViewUp(const vesVector3f& viewUp);

  /// Return a vesOpenGLSupport instance.  This instance is initialized
  /// during the call to initGL() and it is an error to call this method
  /// before initGL().
  vesSharedPtr<vesOpenGLSupport> glSupport();

  /// Return the camera interactor used by the app instance for handling
  /// touch gestures.
  vesSharedPtr<vesKiwiCameraInteractor> cameraInteractor() const;

  /// This accessor is protected so that clients of this class do not use the
  /// API of the returned object. Instead, this class should provide public methods
  /// that wrap the API. The goal is to allow the VES API to be refactored
  /// without breaking clients of this class (only this class breaks)
  vesSharedPtr<vesCamera> camera() const;

  /// \copydoc camera()
  vesSharedPtr<vesRenderer> renderer() const;

protected:

  // Subclasses may override these methods to perform actions before and after
  // rendering.
  virtual void willRender() {}
  virtual void didRender() {}

  vesSharedPtr<vesShaderProgram> addShaderProgram(
    const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
  void deleteShaderProgram(vesSharedPtr<vesShaderProgram> shaderProgram);


  vesSharedPtr<vesUniform> addModelViewMatrixUniform(
    vesSharedPtr<vesShaderProgram> program, const std::string& name=std::string());
  vesSharedPtr<vesUniform> addProjectionMatrixUniform(
    vesSharedPtr<vesShaderProgram> program, const std::string& name=std::string());
  vesSharedPtr<vesUniform> addNormalMatrixUniform(
    vesSharedPtr<vesShaderProgram> program, const std::string& name=std::string());

  vesSharedPtr<vesVertexAttribute> addVertexPositionAttribute(
    vesSharedPtr<vesShaderProgram> program, const std::string& name=std::string());
  vesSharedPtr<vesVertexAttribute> addVertexNormalAttribute(
    vesSharedPtr<vesShaderProgram> program, const std::string& name=std::string());
  vesSharedPtr<vesVertexAttribute> addVertexColorAttribute(
    vesSharedPtr<vesShaderProgram> program, const std::string& name=std::string());
  vesSharedPtr<vesVertexAttribute> addVertexTextureCoordinateAttribute(
    vesSharedPtr<vesShaderProgram> program, const std::string& name=std::string());



private:

  vesKiwiBaseApp(const vesKiwiBaseApp&); // Not implemented
  void operator=(const vesKiwiBaseApp&); // Not implemented

  class vesInternal;
  vesInternal* Internal;
};


#endif

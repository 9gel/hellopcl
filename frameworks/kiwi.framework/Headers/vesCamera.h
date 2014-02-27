/*========================================================================
  VES --- VTK OpenGL ES Rendering Toolkit

      http://www.kitware.com/ves

  Copyright 2011 Kitware, Inc.
  Copyright 2012 Willow Garage, Inc.

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
/// \class vesCamera
/// \ingroup ves
/// \brief Transform node  that provides an interface for camera settings
///
/// vesCamera is a transform node that encapsulate various camera settings.
/// These settings affects how scene is going to get rendered by the underlying
/// rendering engine / API.
/// \see vesTransformNode

#ifndef __vesCamera_h
#define __vesCamera_h

#include "vesTransformNode.h"

// VES includes
#include "vesRenderTarget.h"
#include "vesSetGet.h"

// C/C++ includes
#include <vector>

// Forward declarations
class vesRenderStage;
class vesRenderState;
class vesViewport;
class vesVisitor;

class vesCamera: public vesTransformNode
{
public:
  vesTypeMacro(vesCamera);

  vesCamera();
  virtual  ~vesCamera();

  /// Define the render order of the camera.
  ///
  /// PreRender camera will get its turn of rendering before PostRender
  /// and NestedRender sibling camera's. PostRender camere will get its
  /// turn of rendering only after PreRender and NestedRender sibling
  /// camera's completed their rendering process.
  enum RenderOrder
  {
    PreRender = 0,
    PostRender,
    NestedRender
  };

  /// Set flag to indicate if view angle should be treated as horizontal
  /// view angle
  ///
  /// If set, the camera's view angle represents a horizontal view angle, rather
  /// than the default vertical view angle. This is useful if the application
  /// uses a display device which whose specs indicate a particular horizontal
  /// view angle, or if the application varies the window height but wants to
  /// keep the perspective transform unchanges.
  inline void setUseHorizontalViewAngle(bool value)
    { this->m_useHorizontalViewAngle = value; }

  /// Get flag that indicates if a view angle should be treated as horizontal
  /// view angle
  inline bool useHorizontalViewAngle() const
    { return this->m_useHorizontalViewAngle; }

  inline void setViewPlaneNormal(const vesVector3f &viewPlaneNormal)
    { this->m_viewPlaneNormal = viewPlaneNormal; }
  inline vesVector3f viewPlaneNormal() { return this->m_viewPlaneNormal; }
  inline const vesVector3f& viewPlaneNormal() const { return this->m_viewPlaneNormal; }

  /// Set the camera view angle, which is the angular height of the
  /// camera view measured in degrees.
  ///
  /// The default angle is 30 degrees.
  /// This method has no effect in parallel projection mode.
  /// The formula for setting the angle up for perfect perspective viewing
  /// is: angle = 2*atan((h/2)/d) where h is the height of the RenderWindow
  /// (measured by holding a ruler up to your screen) and d is the
  /// distance from your eyes to the screen.
  inline void setViewAngle(float viewAngle) { this->m_viewAngle = viewAngle; }

  /// Get the camera view angle, which is the angular height of the
  /// camera view measured in degrees.
  float viewAngle() const { return this->m_viewAngle; }

  /// Set the position of the camera in world coordinates.
  /// The default position is (0,0,1).
  inline void setPosition(const vesVector3f &m_position)
    { this->m_position = m_position; this->computeDistance(); }

  /// Get the position of the camera in world coordinates.
  /// The default position is (0,0,1).
  vesVector3f position() { return this->m_position; }
  const vesVector3f& position() const { return this->m_position; }

  /// Set the focal of the camera in world coordinates.
  /// The default focal point is the origin.
  inline void setFocalPoint(const vesVector3f &focalPoint)
    { this->m_focalPoint = focalPoint; }

  /// Get the focal of the camera in world coordinates.
  /// The default focal point is the origin.
  vesVector3f focalPoint() { return this->m_focalPoint; }
  const vesVector3f& focalPoint() const { return this->m_focalPoint; }

  /// Set the view up direction for the camera. The default
  /// is (0,1,0).
  inline void setViewUp(const vesVector3f &viewUp)
    { this->m_viewUp = viewUp; }

  /// Get the view up direction for the camera. The default
  /// is (0,1,0).
  vesVector3f viewUp() { return this->m_viewUp; }
  const vesVector3f& viewUp() const { return this->m_viewUp; }

  /// Set the scaling used for a parallel projection, i.e. the height
  /// of the viewport in world-coordinate distances. The default is 1.
  ///
  /// Note that the "scale" parameter works as an "inverse scale" ---
  /// larger numbers produce smaller images.
  /// This method has no effect in perspective projection mode.
  inline void setParallelScale(float parallelScale)
    { this->m_parallelScale = parallelScale; }

  /// Get the scaling used for a parallel projection, i.e. the height
  /// of the viewport in world-coordinate distances. The default is 1.
  float parallelScale() const { return this->m_parallelScale; }

  /// Set flag to determine if camera should do a perspective or
  /// parallel projection.
  inline void setParallelProjection(bool value)
    { this->m_parallelProjection = value; }

  /// Get flag that determines if camera should do a perspective or
  /// parallel projection.
  bool parallelProjection() const { return this->m_parallelProjection; }

  /// Rotate the camera about the view up vector centered at the focal point.
  /// Note that the view up vector is whatever was set via SetViewUp, and is
  /// not necessarily perpendicular to the direction of projection.  The
  /// result is a horizontal rotation of the camera.
  void azimuth(double angle);

  /// Rotate the camera about the cross product of the negative of the
  /// direction of projection and the view up vector, using the focal point
  /// as the center of rotation.  The result is a vertical rotation of the
  /// scene.
  void elevation(double angle);

  /// Divide the camera's distance from the focal point by the given
  /// dolly value.  Use a value greater than one to dolly-in toward
  /// the focal point, and use a value less than one to dolly-out away
  /// from the focal point.
  void dolly(double factor);

  /// Set the roll angle of the camera about the direction of projection
  void roll(double angle);

  /// Recompute the ViewUp vector to force it to be perpendicular to
  /// camera->focalpoint vector.  Unless you are going to use
  /// Yaw or Azimuth on the camera, there is no need to do this.
  void orthogonalizeViewUp();

  vesMatrix4x4f computeViewTransform();
  vesMatrix4x4f computeProjectionTransform(float aspect, float near, float far);

  /// Set the center of the window in viewport coordinates.
  ///
  /// The viewport coordinate range is ([-1,+1],[-1,+1]).  This method
  /// is for if you have one window which consists of several viewports,
  /// or if you have several screens which you want to act together as
  /// one large screen.
  void setWindowCenter(double x, double y);

  /// Set the location of the near and far clipping planes along the
  /// direction of projection.  Both of these values must be positive.
  /// How the clipping planes are set can have a large impact on how
  /// well z-buffering works.  In particular the front clipping
  /// plane can make a very big difference. Setting it to 0.01 when it
  /// really could be 1.0 can have a big impact on your z-buffer resolution
  /// farther away.  The default clipping range is (0.1,1000).
  /// Clipping distance is measured in world coordinate unless a scale factor
  /// exists in camera's ModelTransformMatrix.
  void setClippingRange(float near, float far);


  /// Set render target for the camera. Render taget defines
  /// the placeholder for the rendered pixels.
  bool setRenderTarget(vesRenderTarget *renderTarget);

  /// Get render target for the camera. Render taget defines
  /// the placeholder for the rendered pixels.
  vesRenderTarget* renderTarget();
  const vesRenderTarget* renderTarget() const;

  /// Clear render targets
  void clearRenderTargets(vesRenderState &renderState);

  /// Get viewport of the camera
  const vesSharedPtr<vesViewport> viewport() const;
  vesSharedPtr<vesViewport> viewport();

  /// Get render stage of the camera
  vesSharedPtr<vesRenderStage> renderStage();
  const vesSharedPtr<vesRenderStage> renderStage() const;
  vesSharedPtr<vesRenderStage> getOrCreateRenderStage();

  /// Set render order of the camera. Default is NestedRender.
  void setRenderOrder(RenderOrder renderOrder, int renderOrderPriority=0);

  /// Get render order of the camera. Default is NestedRender.
  RenderOrder renderOrder() const;
  int renderOrderPriority() const;

  /// Set clear mask. Possible values could be
  /// color buffer bit or depth buffer bit.
  /// \see vesStateAttributeBits::ClearMask
  void setClearMask(unsigned int clearMask);

  /// Get clear mask. Possible values could be
  /// color buffer bit or depth buffer bit.
  /// \see vesStateAttributeBits::ClearMask
  unsigned int clearMask() const;

  /// Set clear color value. This defines the default color
  /// value of the rendered pixel.Default is (1,1,1,1).
  void setClearColor(const vesVector4f &clearColor);

  /// Get clear color value.
  vesVector4f clearColor();
  const vesVector4f& clearColor() const;

  /// Set clear depth value. This defines the default depth
  /// value of the rendered pixel. Default is 1.
  void setClearDepth(double depth);

  /// Get clear depth value.
  double clearDepth() const;

  /// Return model view matrix for the camera
  virtual vesMatrix4x4f modelViewMatrix();

  /// Return projection matrix for the camera
  virtual vesMatrix4x4f projectionMatrix();

  /// \copydoc vesTransformNode::accept()
  virtual void accept(vesVisitor &visitor);

  /// \copydoc vesTransformNode::computeLocalToWorldMatrix()
  virtual bool computeLocalToWorldMatrix(vesMatrix4x4f &matrix,
                                         vesVisitor &visitor);

  /// \copydoc vesTransformNode::computeWorldToLocalMatrix()
  virtual bool computeWorldToLocalMatrix(vesMatrix4x4f& matrix,
                                         vesVisitor& visitor);

protected:
  void computeDistance();
  void computeViewPlaneNormal();

  typedef std::vector<vesRenderTarget*> RenderTargetStack;

  float         m_viewAngle;
  bool          m_useHorizontalViewAngle;
  vesVector3f   m_viewPlaneNormal;
  vesVector3f   m_position, m_focalPoint,m_viewUp;
  float         m_parallelScale;
  float         m_clippingRange[2];
  float         m_distance;
  vesVector3f   m_directionOfProjection;
  double        m_windowCenter[2];
  bool          m_parallelProjection;

  vesSharedPtr<vesViewport> m_viewport;
  vesSharedPtr<vesRenderStage> m_renderStage;

  RenderOrder m_renderOrder;
  int         m_renderOrderPriority;

  RenderTargetStack m_renderTargetStack;
  RenderTargetStack m_removedRenderTargetStack;

  unsigned int m_clearMask;
  vesVector4f m_clearColor;
  double m_clearDepth;
};
#endif //__vesCamera_h

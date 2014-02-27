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
/// \class vesActor
/// \ingroup ves
/// \brief Transform node that contains a drawable entity
///
/// vesActor is a placeholder transform node that contains a drawable entity.
/// One actor can contain only one drawable entity (mapper).
/// A mapper however can be set to multiple actors.
/// \see vesTransformNode vesMapper

#ifndef VESACTOR_H
#define VESACTOR_H

#include "vesNode.h"
#include "vesTransformInterface.h"

// VES includes
#include "vesSetGet.h"

// Forward declarations
class vesMapper;
class vesMaterial;
class vesTransformPrivate;
class vesVisitor;

class vesActor : public vesNode, public vesTransformInterface
{
public:
  vesTypeMacro(vesActor);

  vesActor();
  ~vesActor();

  /// Set center of transformations
  void setCenter(const vesVector3f &center);
  /// Get center of transformations
  const vesVector3f& center() const;

  /// Set rotation as described by angle (in radians) and axis
  /// ( axis(x, y, z), angle )
  void setRotation(const vesVector4f &rotation);

  /// Get rotation as described by angle (in radians) and axis
  /// ( axis(x, y, z), angle )
  const vesVector4f& rotation() const;

  /// Set scale in x, y and z directions
  void setScale(const vesVector3f &scale);

  /// Get scale in x, y and z directions
  const vesVector3f& scale() const;

  /// Set scale orientation (rotation) defined by angle and axis
  /// ( angle, axis(x, y, z) )
  void setScaleOrientation(const vesVector4f &scaleOrientation);

  /// Get scale orientation (rotation) defined by angle and axis
  /// ( angle, axis(x, y, z) )
  const vesVector4f& scaleOrientation() const;

  /// Set translation in x, y and z directions
  void setTranslation(const vesVector3f &translation);

  /// Get translation in x, y and z directions
  const vesVector3f& translation() const;

  /// Set reference frame for the transformations. Possible values
  /// are Absolute and Relative.
  bool setReferenceFrame(ReferenceFrame referenceFrame);

  /// Get reference frame for the transformations. Possible values
  /// are Absolute and Relative.
  ReferenceFrame referenceFrame() const;

  /// Evaluate the transform associated with the vtkActor.
  /// Return affine transformation for the actor.
  vesMatrix4x4f modelViewMatrix();

  /// \copydoc vesTransformInterace::matrix
  virtual vesMatrix4x4f matrix() { return this->modelViewMatrix(); }

  /// Set mapper for the actor
  /// \sa vesMapper
  void setMapper(vesSharedPtr<vesMapper> mapper);
  /// Get mapper of the actor
  /// \sa vesMapper
  vesSharedPtr<vesMapper> mapper() { return this->m_mapper; }
  const vesSharedPtr<vesMapper> mapper() const { return this->m_mapper; }

  /// \copydoc vesNode::accept()
  virtual void accept(vesVisitor &visitor);

  /// \copydoc vesNode::ascend()
  virtual void ascend(vesVisitor &visitor);

  /// \copydoc vesTransformInterace::computeLocalToWorldMatrix()
  virtual bool computeLocalToWorldMatrix(vesMatrix4x4f &matrix,
                                         vesVisitor &visitor);

  /// \copydoc vesTransformInterace::computeWorldToLocalMatrix()
  virtual bool computeWorldToLocalMatrix(vesMatrix4x4f& matrix,
                                         vesVisitor& visitor);

  virtual void computeBounds();

protected:
  void setInternals();

  vesVector3f m_center;
  vesVector4f m_rotation;
  vesVector3f m_scale;
  vesVector4f m_scaleOrientation;
  vesVector3f m_translation;

  ReferenceFrame m_referenceFrame;

  vesSharedPtr<vesMapper> m_mapper;

private:
  vesTransformPrivate *m_implementation;
};

#endif // VESACTOR_H

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
/// \class vesTransformNode
/// \ingroup ves
/// \brief Group node that defines coordinate space of child nodes
///
/// vesTransformNode is a group node that provides interface for affine
/// transformations.
/// \see vesNode vesGroupNode

#ifndef __VESTRANSFORMNODE_H
#define __VESTRANSFORMNODE_H

#include "vesGroupNode.h"
#include "vesTransformInterface.h"

// VES includes
#include "vesSetGet.h"

class vesTransformPrivate;

class vesTransformNode : public vesGroupNode, public vesTransformInterface
{
public:
  vesTypeMacro(vesTransformNode);

  vesTransformNode();
  virtual ~vesTransformNode();

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

  /// \copydoc vesTransformInterace::matrix
  virtual vesMatrix4x4f matrix();

  /// \copydoc vesNode::asTransformNode()
  virtual vesTransformNode* asTransformNode() { return this; }
  virtual const vesTransformNode* asTransformNode() const { return this; }

  /// \copydoc vesNode::accept(vesVisitor&)
  virtual void accept(vesVisitor &visitor);

  /// \copydoc vesTransformInterace::computeLocalToWorldMatrix
  virtual bool computeLocalToWorldMatrix(vesMatrix4x4f& matrix,
                                         vesVisitor& visitor);

  /// \copydoc vesTransformInterace::computeWorldToLocalMatrix
  virtual bool computeWorldToLocalMatrix(vesMatrix4x4f& matrix,
                                         vesVisitor& visitor);

protected:
  void updateBounds(vesNode &child);

  void setInternals();

  vesVector3f m_center;
  vesVector4f m_rotation;
  vesVector3f m_scale;
  vesVector4f m_scaleOrientation;
  vesVector3f m_translation;

  ReferenceFrame m_referenceFrame;

private:
  vesTransformPrivate *m_implementation;
};

#endif // __VESTRANSFORMNODE_H

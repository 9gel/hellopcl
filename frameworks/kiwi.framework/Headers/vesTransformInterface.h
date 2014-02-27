#ifndef VESTRANSFORMINTERFACE_H
#define VESTRANSFORMINTERFACE_H

class vesTransformInterface
{
public:
  enum ReferenceFrame
  {
    Relative = 0,
    Absolute = 1
  };

  /// Set center of transformations
  virtual void setCenter(const vesVector3f &center) = 0;
  /// Get center of transformations
  virtual const vesVector3f& center() const = 0;

  /// Set rotation as described by angle (in radians) and axis
  /// ( axis(x, y, z), angle )
  virtual void setRotation(const vesVector4f &rotation) = 0;

  /// Get rotation as described by angle (in radians) and axis
  /// ( axis(x, y, z), angle )
  virtual const vesVector4f& rotation() const = 0;

  /// Set scale in x, y and z directions
  virtual void setScale(const vesVector3f &scale) = 0;

  /// Get scale in x, y and z directions
  virtual const vesVector3f& scale() const = 0;

  /// Set scale orientation (rotation) defined by angle and axis
  /// ( angle, axis(x, y, z) )
  virtual void setScaleOrientation(const vesVector4f &scaleOrientation) = 0;

  /// Get scale orientation (rotation) defined by angle and axis
  /// ( angle, axis(x, y, z) )
  virtual const vesVector4f& scaleOrientation() const = 0;

  /// Set translation in x, y and z directions
  virtual void setTranslation(const vesVector3f &translation) = 0;

  /// Get translation in x, y and z directions
  virtual const vesVector3f& translation() const = 0;

  /// Set reference frame for the transformations. Possible values
  /// are Absolute and Relative.
  virtual bool setReferenceFrame(ReferenceFrame referenceFrame) = 0;

  /// Get reference frame for the transformations. Possible values
  /// are Absolute and Relative.
  virtual ReferenceFrame referenceFrame() const = 0;

  /// \copydoc vesTransformInterace::matrix
  virtual vesMatrix4x4f matrix() = 0;

  /// Compute local to world matrix transformation
  virtual bool computeLocalToWorldMatrix(vesMatrix4x4f& matrix,
                                         vesVisitor& visitor) = 0;

  /// Compute world to local matrix transformation
  virtual bool computeWorldToLocalMatrix(vesMatrix4x4f& matrix,
                                         vesVisitor& visitor) = 0;
};


#endif // VESTRANSFORMINTERFACE_H

#ifndef VESTRANSFORMPRIVATE_H
#define VESTRANSFORMPRIVATE_H

class vesTransformPrivate
{
public:
  vesMatrix4x4f eval()
  {
    return m_translation * m_center * m_rotation * m_scaleOrientation
      * m_scale * m_scaleOrientationInv * m_centerInv;
  }

  void setTranslation(vesVector3f trans)
  {
    m_translation = makeTranslationMatrix4x4(trans);
  }

  void setCenter(vesVector3f center)
  {
    m_center = makeTranslationMatrix4x4(center);
    m_centerInv = makeInverseMatrix4x4(m_center);
  }

  void setRotation(vesVector4f rot)
  {
    m_rotation = makeRotationMatrix4x4(rot[3], rot[0], rot[1], rot[2]);
  }

  void setScaleOrientation(vesVector4f sr)
  {
    m_scaleOrientation = makeRotationMatrix4x4(sr[3], sr[0], sr[1], sr[2]);
    m_scaleOrientationInv = makeInverseMatrix4x4(m_scaleOrientation);
  }

  void setScale(vesVector3f scale)
  {
    m_scale = makeScaleMatrix4x4(scale[0],scale[1],scale[2]);
  }

private:
  vesMatrix4x4f m_translation;
  vesMatrix4x4f m_center;
  vesMatrix4x4f m_centerInv;
  vesMatrix4x4f m_rotation;
  vesMatrix4x4f m_scale;
  vesMatrix4x4f m_scaleOrientation;
  vesMatrix4x4f m_scaleOrientationInv;
};

#endif // VESTRANSFORMPRIVATE_H

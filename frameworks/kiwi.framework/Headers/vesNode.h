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
/// \class vesNode
/// \ingroup ves
/// \brief Base class for all nodes in the scenegraph
///
/// vesNode provides most common interface for generic node
/// operations. vesNode can be subclassed to provide more specific
/// node operations.

#ifndef __VESNODE_H
#define __VESNODE_H

#include "vesBoundingObject.h"

// VES includes
#include "vesSetGet.h"

// Forward declarations.
class vesActor;
class vesCamera;
class vesGroupNode;
class vesMaterial;
class vesTransformNode;
class vesVisitor;

class vesNode : public vesBoundingObject
{
public:
  vesTypeMacro(vesNode);

  vesNode();
  virtual ~vesNode();

  /// Accept visitor for scene traversal
  virtual void accept(vesVisitor &visitor);

  /// Set material to be used for the node
  ///
  /// Material defines the apperance of the node. Only one material
  /// per node is allowed. Once defined a material for the node, all of
  /// node's children will inherit the same material unless they have their
  /// own material.
  /// \see vesMaterial
  void setMaterial(vesSharedPtr<vesMaterial> material);

  /// Get material of the node
  vesSharedPtr<vesMaterial> material() { return this->m_material; }
  const vesSharedPtr<vesMaterial> material() const { return this->m_material; }

  /// Set parent of the node
  bool setParent(vesGroupNode *parent);

  /// Get parent of the node
  vesGroupNode* parent(){ return this->m_parent; }

  /// Mark parent bounds dirty or not dirty
  void setParentBoundsDirty(bool value);
  /// Return if parent bounds are dirty or not
  bool parentBoundsDirty();

  /// Set if this node is an overlay node. Overlay nodes are drawn
  /// on top of scene nodes.
  inline void setIsOverlayNode(bool value) { this->m_isOverlayNode = value; }

  /// Return if node is an overlay node
  inline bool isOverlayNode() const { return this->m_isOverlayNode; }

  /// Set if this node should be visible
  bool setVisible(bool value);

  /// Return if node is visible
  bool isVisible() const { return this->m_visible; }

  /// Cast node as group node. Returns NULL on failure.
  virtual vesGroupNode* asGroupNode() { return 0x0; }
  virtual const vesGroupNode* asGroupNode() const { return 0x0; }

  /// Cast node as transform node. Returns NULL on failure.
  virtual vesTransformNode* asTransformNode() { return 0x0; }
  virtual const vesTransformNode* asTransformNode() const { return 0x0; }

  /// Cast node as camera node. Returns NULL on failure.
  virtual vesCamera* asCamera() { return 0x0; }
  virtual const vesCamera* asCamera() const { return 0x0; }

  /// Cast node as actor node. Returns NULL on failure.
  virtual vesActor* asActor() { return 0x0; }
  virtual const vesActor* asActor() const { return 0x0; }

  /// Traverse parent
  virtual void ascend(vesVisitor &visitor)
    { vesNotUsed(visitor); }

  /// Traverse children
  virtual void traverse(vesVisitor &visitor)
    { vesNotUsed(visitor); }

  /// Force computation of bounds
  virtual void computeBounds();

protected:
  virtual void updateBounds(vesNode &child)
    { vesNotUsed(child); }

  bool m_visible;
  bool m_isOverlayNode;

  vesGroupNode* m_parent;

  vesSharedPtr<vesMaterial> m_material;
};

#endif // __VESNODE_H

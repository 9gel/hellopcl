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
/// \class vesGroupNode
/// \ingroup ves
/// \brief Base class for all group nodes in the scenegraph
///
/// vesGroupNode provides most common interface for nodes that can contain
/// other nodes of the scenegraph. A node can be added as child node or can
/// be removed when required from this node. vesGroupNode is a collection of
/// nodes sharing a common parent. This node could be useful to share
/// common attribute to collection of nodes (such as material)
/// \see vesNode vesTransformNode

#ifndef __VESGROUPNODE_H
#define __VESGROUPNODE_H

#include "vesNode.h"

// VES includes
#include "vesSetGet.h"

// C/C++ includes
#include <list>

class vesGroupNode: public vesNode
{
public:
  vesTypeMacro(vesGroupNode);

  vesGroupNode();
  virtual ~vesGroupNode();

  typedef std::list< vesSharedPtr<vesNode> > Children;

  /// \copydoc vesNode::setVisible
  bool setVisible(bool value);

  /// Add a node as a child node
  bool addChild(vesSharedPtr<vesNode> child);

  /// Remove a child node. Return true on success.
  bool removeChild(vesSharedPtr<vesNode> child);
  bool removeChild(vesNode *child);

  /// Return list of child nodes
  Children&       children()       { return this->m_children; }
  const Children& children() const { return this->m_children; }

  /// \copydoc vesNode::accept(vesVisitor&)
  virtual void accept(vesVisitor &visitor);

  /// \copydoc vesNode::traverse(vesVisitor&)
  virtual void traverse(vesVisitor &visitor);

protected:
  void traverseChildrenAndUpdateBounds(vesVisitor &visitor);
  void traverseChildren(vesVisitor &visitor);

  virtual void updateBounds(vesNode &child);

  Children m_children;
};

#endif // __VESGROUPNODE_H

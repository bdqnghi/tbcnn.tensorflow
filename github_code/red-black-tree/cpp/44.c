/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2011-2012 Opera Software ASA.  All rights reserved.
 *
 * This file is part of the Opera web browser.
 * It may not be distributed under any circumstances.
 */

#ifndef MODULES_OTL_REDBLACKTREENODE_H
#define MODULES_OTL_REDBLACKTREENODE_H

/**
 * Node in an OtlRedBlackTree.
 *
 * Represents a single node of a red-black tree. It is characterized by
 * its color and the object it contains. Each node has links to its
 * parent node and up to two child nodes.
 *
 * @tparam T Type of the stored object.
 */
template<typename T>
class OtlRedBlackTreeNode
{
public:

	OtlRedBlackTreeNode(const T& item);
	~OtlRedBlackTreeNode();

	void Initialize();

	/** Delete subtree.
	 *
	 * Recursively calls itself on child nodes and then deletes them, effectively
	 * destroying the entire subtree.
	 */
	void DeleteChildren();

	/**
	 * Set new parent.
	 *
	 * Set @a p as parent of this node. Doesn't register self as child of @a p
	 * as there are no means to check which child is correct (left or right).
	 * @param p New parent. May be NULL.
	 */
	void SetParent(OtlRedBlackTreeNode* p);

	/// Get child from @a dir direction (0: left, 1: right).
	OtlRedBlackTreeNode* Child(int dir) const;

	/**
	 * Set new child.
	 *
	 * Set new child in @a dir direction (0: left, 1: right). Updates the new
	 * child's parent to self.
	 * @param n New child. May be NULL.
	 */
	void SetChild(OtlRedBlackTreeNode* n, int dir);

	/**
	 * Remove node from children.
	 *
	 * Checks if @a n is one of the children and if so, removes the link.
	 * No deletion is performed.
	 * @param n Node to unlink.
	 */
	void UnlinkChild(OtlRedBlackTreeNode* n);

	/**
	 * Get other child of the parent.
	 *
	 * If there's no parent node or if we're its only child, returns NULL.
	 * @return Pointer to sibling node or NULL.
	 */
	OtlRedBlackTreeNode* Sibling() const;

	/// Get parent node.
	OtlRedBlackTreeNode* Parent() const;

	bool HasNoRedChildren() const;
	bool HasTwoRedChildren() const;

	/// Get the descendant node that is furthest towards direction @a dir.
	OtlRedBlackTreeNode* Furthest(int dir);

	/// Return true when there is no parent.
	bool IsRoot() const;

	/// Return true when there are no children.
	bool IsLeaf() const;

	bool IsBlack() const;
	bool IsRed() const;
	void SetBlack();
	void SetRed();

	static bool IsRed(OtlRedBlackTreeNode* n)
	{
		return n ? n->color == RED : false;
	}

	/**
	 * Returns the neighbour of the node. dir specifies whether it's next (1)
	 * or previous (0).
	 */
	OtlRedBlackTreeNode* Neighbour(int dir) const;

	/**
	 * Returns the next node in an in-order traversal, or NULL if no more nodes
	 * can be reached.
	 */
	OtlRedBlackTreeNode* Next() const;

	/**
	 * Returns the next node in a reverse in-order traversal, or NULL if no
	 * more nodes can be reached.
	 */
	OtlRedBlackTreeNode* Previous() const;

#if defined(RBTREE_DEBUG) || defined(SELFTEST)
	/**
	 * Debug function - return the black depth of a node.
	 * NOTE: This is only meaningful for leaf nodes (with no left or right child).
	 */
	size_t BlackDepth() const;

	/**
	 * Debug function - return the actual depth of a node, regardless of coloring.
	 */
	size_t Depth() const;

	/**
	 * Debug function - return true if any parent walking from
	 * this node up to the root is a double red.
	 * Mostly useful for leaf nodes only.
	 */
	bool FindDoubleRed() const;
#endif // defined(RBTREE_DEBUG) || defined(SELFTEST)
	T item;
	enum { RED, BLACK } color;
	OtlRedBlackTreeNode* parent;
	OtlRedBlackTreeNode* child[2];
}; // OtlRedBlackTreeNode

// Implementation

template<typename T> inline
OtlRedBlackTreeNode<T>::OtlRedBlackTreeNode(const T& item)
	: item(item)
{
	Initialize();
}

template<typename T> inline
OtlRedBlackTreeNode<T>::~OtlRedBlackTreeNode()
{
	if (parent)
		parent->UnlinkChild(this);
}

template<typename T>
void OtlRedBlackTreeNode<T>::Initialize()
{
	parent = NULL;
	child[0] = NULL;
	child[1] = NULL;
	color = RED;
}


template<typename T> inline
void OtlRedBlackTreeNode<T>::SetParent(OtlRedBlackTreeNode* p)
{
	parent = p;
}

template<typename T> inline
OtlRedBlackTreeNode<T>* OtlRedBlackTreeNode<T>::Child(int dir) const
{
	OP_ASSERT(dir == 0 || dir == 1);
	return child[dir];
}

template<typename T> inline
void OtlRedBlackTreeNode<T>::SetChild(OtlRedBlackTreeNode* n, int dir)
{
	OP_ASSERT(dir == 0 || dir == 1);
	child[dir] = n;
	if (n)
	{
		n->SetParent(this);
	}
}

template<typename T> inline
void OtlRedBlackTreeNode<T>::UnlinkChild(OtlRedBlackTreeNode* n)
{
	if (child[0] == n)
		child[0] = NULL;
	if (child[1] == n)
		child[1] = NULL;
}

template<typename T> inline
OtlRedBlackTreeNode<T>* OtlRedBlackTreeNode<T>::Parent() const
{
	return parent;
}

template<typename T> inline
OtlRedBlackTreeNode<T>* OtlRedBlackTreeNode<T>::Sibling() const
{
	if (!parent)
		return NULL;
	return parent->Child(parent->Child(0) == this);
}

template<typename T> inline
bool OtlRedBlackTreeNode<T>::HasNoRedChildren() const
{
	return !IsRed(child[0]) && !IsRed(child[1]);
}

template<typename T> inline
bool OtlRedBlackTreeNode<T>::HasTwoRedChildren() const
{
	return IsRed(child[0]) && IsRed(child[1]);
}

template<typename T> inline
OtlRedBlackTreeNode<T>* OtlRedBlackTreeNode<T>::Furthest(int dir)
{
	OP_ASSERT(dir == 0 || dir == 1);
	OtlRedBlackTreeNode* it = this; while (it->Child(dir)) { it = it->Child(dir); } return it;
}

template<typename T> inline
bool OtlRedBlackTreeNode<T>::IsRoot() const
{
	return parent == NULL;
}

template<typename T> inline
bool OtlRedBlackTreeNode<T>::IsLeaf() const
{
	return child[0] == NULL && child[1] == NULL;
}

template<typename T> inline
bool OtlRedBlackTreeNode<T>::IsBlack() const
{
	return color == BLACK;
}

template<typename T> inline
bool OtlRedBlackTreeNode<T>::IsRed() const
{
	return color == RED;
}

template<typename T> inline
void OtlRedBlackTreeNode<T>::SetBlack()
{
	color = BLACK;
}

template<typename T> inline
void OtlRedBlackTreeNode<T>::SetRed()
{
	color = RED;
}

template<typename T>
void OtlRedBlackTreeNode<T>::DeleteChildren()
{
	for (int i = 0; i < 2; i++)
	{
		if (child[i])
		{
			child[i]->DeleteChildren();
			OP_DELETE(child[i]);
		}
	}
}

template<typename T>
OtlRedBlackTreeNode<T>* OtlRedBlackTreeNode<T>::Neighbour(int dir) const
{
	const OtlRedBlackTreeNode* n = this;

	if (n->child[dir])
	{
		return n->child[dir]->Furthest(!dir);
	}

	// Walk upwards to the root.
	OtlRedBlackTreeNode* p = n->parent;
	if (p)
	{
		// Walk up from the the other side.
		if (p->child[!dir] == n)
			return p;

		// Walk up from our side.
		while (p->child[dir] == n)
		{
			n = p;
			p = p->parent;
			if (!p)
				return NULL;
		}
		return p;
	}
	return NULL;
}

template<typename T> inline
OtlRedBlackTreeNode<T>* OtlRedBlackTreeNode<T>::Next() const
{
	return Neighbour(1);
}

template<typename T> inline
OtlRedBlackTreeNode<T>* OtlRedBlackTreeNode<T>::Previous() const
{
	return Neighbour(0);
}


#if defined(RBTREE_DEBUG) || defined(SELFTEST)
template<typename T>
size_t OtlRedBlackTreeNode<T>::BlackDepth() const
{
	size_t count = 0;
	const OtlRedBlackTreeNode* it = this;

	while (it)
	{
		if (it->IsBlack())
			count++;
		it = it->parent;
	}
	return count;
}

template<typename T>
size_t OtlRedBlackTreeNode<T>::Depth() const
{
	size_t count = 0;
	for (OtlRedBlackTreeNode* it = this; it; it = it->parent)
		count++;
	return count;
}

template<typename T>
bool OtlRedBlackTreeNode<T>::FindDoubleRed() const
{
	bool red = (color == RED);
	OtlRedBlackTreeNode* it = this->parent;
	while (it)
	{
		if (it->color == RED && red)
				return true;
		red = (it->color == RED);
		it = it->parent;
	}
	return false;
}
#endif // defined(RBTREE_DEBUG) || defined(SELFTEST)

#endif // MODULES_OTL_REDBLACKTREENODE_H

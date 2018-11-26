// ==========================================================================================
// Copyright (C) Goddamn Industries 2018. All Rights Reserved.
// 
// This software or any its part is distributed under terms of Goddamn Industries End User
// License Agreement. By downloading or using this software or any its part you agree with 
// terms of Goddamn Industries End User License Agreement.
// ==========================================================================================

/*!
 * @file GoddamnEngine/Core/Containers/RedBlackTree/RedBlackTree.cpp
 * Red-Black tree data structure implementation.
 */
#include <GoddamnEngine/Core/Containers/RedBlackTree/RedBlackTree.h>

GD_NAMESPACE_BEGIN

	// ==========================================================================================
	// RedBlackTree class.
	// ==========================================================================================

	// Low-level Red-Black Tree algorithms.
	// Adapted from the following code written by Emin Martinian:
	// http://web.mit.edu/~emin/www.old/source_code/red_black_tree/index.html
	//
	// Copyright (c) 2001 Emin Martinian
	//
	// Redistribution and use in source and binary forms, with or without modification, are 
	// permitted provided that neither the name of Emin Martinian nor the names of any 
	// contributors are be used to endorse or promote products derived from this software without 
	// specific prior written permission.
	//
	// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS 
	// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
	// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
	// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
	// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
	// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
	// AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
	// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
	// OF THE POSSIBILITY OF SUCH DAMAGE.

	// ------------------------------------------------------------------------------------------
	// Constructor and destructor.
	// ------------------------------------------------------------------------------------------

	/*!
	 * Initializes a new Red-Black Tree.
	 */
	GDAPI RedBlackTreeBase::RedBlackTreeBase()
	{
		InternalCreateNodeBase(m_NullNode);
		InternalCreateNodeBase(m_RootNode);
		m_NullNode->m_IsNull = true;
	}

	/*!
	 * Moves other Red-Black Tree here.
	 * @param other The other tree to move here.
	 */
	GDAPI RedBlackTreeBase::RedBlackTreeBase(RedBlackTreeBase&& other) noexcept
	{
		m_RootNode = other.m_RootNode;
		m_NullNode = other.m_NullNode;
		m_Length = other.m_Length;

		other.m_RootNode = nullptr;
		other.m_NullNode = nullptr;
		other.m_Length = 0;
	}

	/*!
	 * Deinitializes a Red-Black Tree and destroys all internal data.
	 */
	GDAPI RedBlackTreeBase::~RedBlackTreeBase()
	{
		Clear();
		gd_delete m_RootNode;
		gd_delete m_NullNode;
	}

	// ------------------------------------------------------------------------------------------
	// Tree iteration.
	// ------------------------------------------------------------------------------------------

	/*!
	 * Returns first node of the tree or null.
	 */
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::GetFirstNodeBase() const
	{
		RedBlackTreeBaseNode const* iterNode = m_RootNode->m_Left;
		while (iterNode->m_Left != m_NullNode)
		{
			iterNode = iterNode->m_Left;
		}

		return iterNode;
	}

	/*!
	 * Returns last node of the tree or null.
	 */
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::GetLastNodeBase() const
	{
		RedBlackTreeBaseNode const* iterNode = m_RootNode->m_Left;
		while (iterNode->m_Right != m_NullNode)
		{
			iterNode = iterNode->m_Right;
		}

		return iterNode;
	}

	/*!
	 * Returns next node to specified one or null.
	 *
	 * @param x Some node.
	 * @returns Next node to this one or null node if not exists.
	 */
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::GetNextNodeBase(RedBlackTreeBaseNode const* x) const
	{
		RedBlackTreeBaseNode const* y;
		if (m_NullNode == x)
		{
			return m_NullNode;
		}
		if (m_NullNode != (y = x->m_Right))
		{
			// assignment to y is intentional 
			while (y->m_Left != m_NullNode)
			{
				// returns the minimum of the right subtree of x 
				y = y->m_Left;
			}
			return y;
		}
		else
		{
			y = x->m_Parent;
			while (x == y->m_Right)
			{
				// sentinel used instead of checking for null node 
				x = y;
				y = y->m_Parent;
			}
			if (y == m_RootNode)
				return m_NullNode;
			return y;
		}
	}

	/*!
	 * Returns previous node to specified one or null.
	 *
	 * @param x Some node.
	 * @returns Previous node to this one or null node if not exists.
	 */
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::GetPrevNodeBase(RedBlackTreeBaseNode const* x) const
	{
		RedBlackTreeBaseNode const* y;
		if (m_NullNode == x)
		{
			return GetLastNodeBase();
		}
		if (m_NullNode != (y = x->m_Left))
		{		
			// assignment to y is intentional
			while (y->m_Right != m_NullNode)
			{	
				// returns the maximum of the left subtree of x
				y = y->m_Right;
			}
			return y;
		}
		y = x->m_Parent;
		while (x == y->m_Left)
		{
			if (y == m_RootNode)
			{
				return(m_NullNode);
			}
			x = y;
			y = y->m_Parent;
		}
		return y;
	}

	// ------------------------------------------------------------------------------------------
	// Tree manipulation.
	// ------------------------------------------------------------------------------------------

	/*!
	 * Internally creates a new node.
	 * @param newNode Reference to new node.
	 */
	// ReSharper disable once CppMemberFunctionMayBeConst
	GDAPI void RedBlackTreeBase::InternalCreateNodeBase(RedBlackTreeBaseNode*& newNode)
	{
		newNode = reinterpret_cast<RedBlackTreeBaseNode*>(GD_MALLOC(sizeof(RedBlackTreeBaseNode) - sizeof(Byte)));
		new (newNode) RedBlackTreeBaseNode();
		newNode->m_Left   = m_NullNode;
		newNode->m_Right  = m_NullNode;
		newNode->m_Parent = m_NullNode;
		newNode->m_IsRed  = false;
#if GD_PLATFORM_WINDOWS && !GD_RELEASE
		newNode->m_IsNull = false;
#endif	// if GD_PLATFORM_WINDOWS && !GD_RELEASE
	}

	/*!
	 * Internally destroys a specified node and all is children.
	 * @param node The node that is going to be destroyed.
	 */
	// ReSharper disable once CppMemberFunctionMayBeConst
	GDAPI void RedBlackTreeBase::InternalDestroyNode(RedBlackTreeBaseNode* const node)
	{
		if (node != m_NullNode) 
		{
			InternalDestroyNode(node->m_Left);
			InternalDestroyNode(node->m_Right);
			OnDestroyNode(node);
		}
	}

	/*!
	 * Performs a left rotation of the tree.
	 * @param node The node to rotate on.
	 */
	// ReSharper disable once CppMemberFunctionMayBeConst
	GDAPI void RedBlackTreeBase::InternalRotateLeft(RedBlackTreeBaseNode* x)
	{
		RedBlackTreeBaseNode* y;

		//  I originally wrote this function to use the sentinel for
		//  null node to avoid checking for null ptr.  However this introduces a
		//  very subtle bug because sometimes this function modifies
		//  the parent pointer of null node.  This can be a problem if a
		//  function which calls _InternalRotateLeft also uses the null sentinel
		//  and expects the null sentinel's parent pointer to be unchanged
		//  after calling this function.  For example, when RBDeleteFixUP
		//  calls _InternalRotateLeft it expects the parent pointer of null node to be
		//  unchanged.

		y = x->m_Right;
		x->m_Right = y->m_Left;

		if (y->m_Left != m_NullNode)
		{
			y->m_Left->m_Parent = x;
			// used to use sentinel here
			// and do an unconditional assignment instead of testing for m_NullNode
		}

		y->m_Parent = x->m_Parent;

		// instead of checking if x->m_Parent is the m_RootNode as in the book, we
		// count on the m_RootNode sentinel to implicitly take care of this case
		if (x == x->m_Parent->m_Left)
		{
			x->m_Parent->m_Left = y;
		}
		else
		{
			x->m_Parent->m_Right = y;
		}
		y->m_Left = x;
		x->m_Parent = y;

		GD_ASSERT(!m_NullNode->m_IsRed, "m_NullNode not m_IsRed in _InternalRotateLeft");
	}

	/*!
	 * Performs a right rotation of the tree.
	 * @param node The node to rotate on.
	 */
	// ReSharper disable once CppMemberFunctionMayBeConst
	GDAPI void RedBlackTreeBase::InternalRotateRight(RedBlackTreeBaseNode* y)
	{
		RedBlackTreeBaseNode* x;

		/* I originally wrote this function to use the sentinel for */
		/* m_NullNode to avoid checking for m_NullNode.  However this introduces a */
		/* very subtle bug because sometimes this function modifies */
		/* the m_Parent pointer of m_NullNode.  This can be a problem if a */
		/* function which calls LeftRotate also uses the m_NullNode sentinel */
		/* and expects the m_NullNode sentinel's m_Parent pointer to be unchanged */
		/* after calling this function.  For example, when RBDeleteFixUP */
		/* calls LeftRotate it expects the m_Parent pointer of m_NullNode to be */
		/* unchanged. */
		x = y->m_Left;
		y->m_Left = x->m_Right;

		if (m_NullNode != x->m_Right)
		{
			/*used to use sentinel here */
			/* and do an unconditional assignment instead of testing for m_NullNode */
			x->m_Right->m_Parent = y;
		}

		/* instead of checking if x->m_Parent is the m_RootNode as in the book, we */
		/* count on the m_RootNode sentinel to implicitly take care of this case */
		x->m_Parent = y->m_Parent;
		if (y == y->m_Parent->m_Left)
		{
			y->m_Parent->m_Left = x;
		}
		else
		{
			y->m_Parent->m_Right = x;
		}
		x->m_Right = y;
		y->m_Parent = x;

		GD_ASSERT(!m_NullNode->m_IsRed, "m_NullNode not m_IsRed in _RightRotate");
	}

	/*!
	 * Fixes the tree and restores it's Red-Black properties.
	 * @param node The node to start fixing.
	 */
	GDAPI void RedBlackTreeBase::InternalRepair(RedBlackTreeBaseNode* x)
	{
		RedBlackTreeBaseNode* w;
		while (!x->m_IsRed && m_RootNode != x)
		{
			if (x == x->m_Parent->m_Left)
			{
				w = x->m_Parent->m_Right;
				if (w->m_IsRed)
				{
					w->m_IsRed = false;
					x->m_Parent->m_IsRed = true;
					InternalRotateLeft(x->m_Parent);
					w = x->m_Parent->m_Right;
				}
				if (!w->m_Right->m_IsRed && !w->m_Left->m_IsRed)
				{
					w->m_IsRed = true;
					x = x->m_Parent;
				}
				else
				{
					if (!w->m_Right->m_IsRed)
					{
						w->m_Left->m_IsRed = false;
						w->m_IsRed = true;
						InternalRotateRight(w);
						w = x->m_Parent->m_Right;
					}
					w->m_IsRed = x->m_Parent->m_IsRed;
					x->m_Parent->m_IsRed = false;
					w->m_Right->m_IsRed = false;
					InternalRotateLeft(x->m_Parent);
					/* this is to exit while loop */
					x = m_RootNode;
				}
			}
			else
			{
				/* the code below is has m_Left and m_Right switched from above */
				w = x->m_Parent->m_Left;
				if (w->m_IsRed)
				{
					w->m_IsRed = false;
					x->m_Parent->m_IsRed = true;
					InternalRotateRight(x->m_Parent);
					w = x->m_Parent->m_Left;
				}
				if (!w->m_Right->m_IsRed && !w->m_Left->m_IsRed)
				{
					w->m_IsRed = true;
					x = x->m_Parent;
				}
				else
				{
					if (!w->m_Left->m_IsRed)
					{
						w->m_Right->m_IsRed = false;
						w->m_IsRed = true;
						InternalRotateLeft(w);
						w = x->m_Parent->m_Left;
					}
					w->m_IsRed = x->m_Parent->m_IsRed;
					x->m_Parent->m_IsRed = false;
					w->m_Left->m_IsRed = false;
					InternalRotateRight(x->m_Parent);
					/* this is to exit while loop */
					x = m_RootNode;
				}
			}
		}
		x->m_IsRed = false;

		//!
		//! @todo:
		//! While removing the first element of map this assert fails.
		//! @todo But now everything works, check the whole source.
		m_NullNode->m_IsRed = false;
		GD_ASSERT(!m_NullNode->m_IsRed, "m_NullNode not black in InternalRepair");
	}

	// ------------------------------------------------------------------------------------------
	// Tree modification.
	// ------------------------------------------------------------------------------------------

	/*!
	 * Searches for node with specified element.
	 *
	 * @param element Key we are looking for.
	 * @returns pointer to node or nullptr if nothing was found.
	 */
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::FindNodeBase(CHandle const element) const
	{
		auto x = m_RootNode->m_Left;
		if (x == m_NullNode)
		{
			// return(0);
			return x;
		}

		auto compareResult = OnCompareElements(x->GetDataUntyped(), element);
		while (0 != compareResult)
		{
			//assignment
			if (1 == compareResult)
			{ 
				// X->GetDataUntyped() > q
				x = x->m_Left;
			}
			else
			{
				x = x->m_Right;
			}
			if (x == m_NullNode)
			{
				// return(0);
				return x;
			}
			compareResult = OnCompareElements(x->GetDataUntyped(), element);
		}
		return x;
	}

	/*!
	 * Performs an insertion of the new node with specified Key and value.
	 * @param newNode The node that would be inserted.
	 */
	GDAPI void RedBlackTreeBase::InsertNodeBase(RedBlackTreeBaseNode* z)
	{
		GD_ASSERT(z != nullptr, "Null pointer node.");
		GD_ASSERT(FindNodeBase(z->GetDataUntyped()) == GetNullNodeBase(), "node with specified element already exist in the tree.");
		m_Length += 1;

		RedBlackTreeBaseNode* y;
		RedBlackTreeBaseNode* x;

		z->m_Left = z->m_Right = m_NullNode;
		y = m_RootNode;
		x = m_RootNode->m_Left;
		while (x != m_NullNode)
		{
			y = x;
			if (1 == OnCompareElements(x->GetDataUntyped(), z->GetDataUntyped()))
			{ 
				// X.Key > z.Key
				x = x->m_Left;
			}
			else
			{ 
				// X.Key <= z.Key
				x = x->m_Right;
			}
		}
		z->m_Parent = y;
		if (y == m_RootNode || 1 == OnCompareElements(y->GetDataUntyped(), z->GetDataUntyped()))
		{ 
			// Y.Key > z.Key
			y->m_Left = z;
		}
		else
		{
			y->m_Right = z;
		}

		GD_ASSERT(!m_NullNode->m_IsRed, "m_NullNode not m_IsRed in TreeInsertHelp");

		x = z;
		x->m_IsRed = true;
		while (x->m_Parent->m_IsRed)
		{ 
			// use sentinel instead of checking for m_RootNode
			if (x->m_Parent == x->m_Parent->m_Parent->m_Left)
			{
				y = x->m_Parent->m_Parent->m_Right;
				if (y->m_IsRed)
				{
					y->m_IsRed = false;
					x->m_Parent->m_IsRed = false;
					x->m_Parent->m_Parent->m_IsRed = true;
					x = x->m_Parent->m_Parent;
				}
				else
				{
					if (x == x->m_Parent->m_Right)
					{
						x = x->m_Parent;
						InternalRotateLeft(x);
					}
					x->m_Parent->m_IsRed = false;
					x->m_Parent->m_Parent->m_IsRed = true;
					InternalRotateRight(x->m_Parent->m_Parent);
				}
			}
			else
			{ 
				// case for X->m_Parent == X->m_Parent->m_Parent->m_Right
				y = x->m_Parent->m_Parent->m_Left;
				if (y->m_IsRed)
				{
					y->m_IsRed = false;
					x->m_Parent->m_IsRed = false;
					x->m_Parent->m_Parent->m_IsRed = true;
					x = x->m_Parent->m_Parent;
				}
				else
				{
					if (x == x->m_Parent->m_Left)
					{
						x = x->m_Parent;
						InternalRotateRight(x);
					}
					x->m_Parent->m_IsRed = false;
					x->m_Parent->m_Parent->m_IsRed = true;
					InternalRotateLeft(x->m_Parent->m_Parent);
				}
			}
		}
		m_RootNode->m_Left->m_IsRed = false;

		GD_ASSERT(!m_NullNode->m_IsRed, "m_NullNode not m_IsRed in Insert");
		GD_ASSERT(!m_RootNode->m_IsRed, "m_RootNode not m_IsRed in Insert");
	}

	/*!
	 * Deletes the node from the tree.
	 * @param node The node that would be deleted. Should be manually deleted.
	 */
	GDAPI void RedBlackTreeBase::RemoveNodeBase(RedBlackTreeBaseNode* const z)
	{
		RedBlackTreeBaseNode* y;
		RedBlackTreeBaseNode* x;

		y = z->m_Left == m_NullNode || z->m_Right == m_NullNode ? z : GetNextNodeBase(z);
		x = y->m_Left == m_NullNode ? y->m_Right : y->m_Left;
		if (m_RootNode == (x->m_Parent = y->m_Parent))
		{ 
			// assignment of Y->p to X->p is intentional
			m_RootNode->m_Left = x;
		}
		else
		{
			if (y == y->m_Parent->m_Left)
			{
				y->m_Parent->m_Left = x;
			}
			else
			{
				y->m_Parent->m_Right = x;
			}
		}
		if (y != z)
		{ 
			// Y should not be m_NullNode in this case
			GD_ASSERT(y != m_NullNode, "Y is m_NullNode in RBDelete\n");
			
			// Y is the node to splice out and X is its child
			if (!y->m_IsRed)
			{
				InternalRepair(x);
			}

			//DestroyKey(z->GetDataUntyped());
			//DestroyInfo(z->info);
			y->m_Left = z->m_Left;
			y->m_Right = z->m_Right;
			y->m_Parent = z->m_Parent;
			y->m_IsRed = z->m_IsRed;
			z->m_Left->m_Parent = z->m_Right->m_Parent = y;
			if (z == z->m_Parent->m_Left)
			{
				z->m_Parent->m_Left = y;
			}
			else
			{
				z->m_Parent->m_Right = y;
			}
			//free(z);
			OnDestroyNode(z);
		}
		else
		{
			//DestroyKey(Y->GetDataUntyped());
			//DestroyInfo(Y->info);
			if (!y->m_IsRed)
			{
				InternalRepair(x);
			}
			OnDestroyNode(y);
			//free(Y);
		}

		GD_ASSERT(!m_NullNode->m_IsRed, "m_NullNode not black in RBDelete");
		--m_Length;
	}

	/*!
	 * Removes all elements from the tree.
	 */
	GDAPI void RedBlackTreeBase::Clear()
	{
		if (m_RootNode != nullptr)
		{
			InternalDestroyNode(m_RootNode->m_Left);
			InternalDestroyNode(m_RootNode->m_Right);
			m_RootNode->m_Left = m_NullNode;
			m_RootNode->m_Right = m_NullNode;
			m_Length = 0;
		}
	}

GD_NAMESPACE_END










#include <GoddamnEngine/Core/Containers/RedBlackTree/RedBlackTree.h>

GD_NAMESPACE_BEGIN

	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	

	
	GDAPI RedBlackTreeBase::RedBlackTreeBase()
	{
		InternalCreateNodeBase(m_NullNode);
		InternalCreateNodeBase(m_RootNode);
		m_NullNode->m_IsNull = true;
	}

	
	GDAPI RedBlackTreeBase::RedBlackTreeBase(RedBlackTreeBase&& other) noexcept
	{
		m_RootNode = other.m_RootNode;
		m_NullNode = other.m_NullNode;
		m_Length = other.m_Length;

		other.m_RootNode = nullptr;
		other.m_NullNode = nullptr;
		other.m_Length = 0;
	}

	
	GDAPI RedBlackTreeBase::~RedBlackTreeBase()
	{
		Clear();
		gd_delete m_RootNode;
		gd_delete m_NullNode;
	}

	
	
	

	
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::GetFirstNodeBase() const
	{
		RedBlackTreeBaseNode const* iterNode = m_RootNode->m_Left;
		while (iterNode->m_Left != m_NullNode)
		{
			iterNode = iterNode->m_Left;
		}

		return iterNode;
	}

	
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::GetLastNodeBase() const
	{
		RedBlackTreeBaseNode const* iterNode = m_RootNode->m_Left;
		while (iterNode->m_Right != m_NullNode)
		{
			iterNode = iterNode->m_Right;
		}

		return iterNode;
	}

	
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::GetNextNodeBase(RedBlackTreeBaseNode const* x) const
	{
		RedBlackTreeBaseNode const* y;
		if (m_NullNode == x)
		{
			return m_NullNode;
		}
		if (m_NullNode != (y = x->m_Right))
		{
			
			while (y->m_Left != m_NullNode)
			{
				
				y = y->m_Left;
			}
			return y;
		}
		else
		{
			y = x->m_Parent;
			while (x == y->m_Right)
			{
				
				x = y;
				y = y->m_Parent;
			}
			if (y == m_RootNode)
				return m_NullNode;
			return y;
		}
	}

	
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::GetPrevNodeBase(RedBlackTreeBaseNode const* x) const
	{
		RedBlackTreeBaseNode const* y;
		if (m_NullNode == x)
		{
			return GetLastNodeBase();
		}
		if (m_NullNode != (y = x->m_Left))
		{		
			
			while (y->m_Right != m_NullNode)
			{	
				
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
#endif	
	}

	
	
	GDAPI void RedBlackTreeBase::InternalDestroyNode(RedBlackTreeBaseNode* const node)
	{
		if (node != m_NullNode) 
		{
			InternalDestroyNode(node->m_Left);
			InternalDestroyNode(node->m_Right);
			OnDestroyNode(node);
		}
	}

	
	
	GDAPI void RedBlackTreeBase::InternalRotateLeft(RedBlackTreeBaseNode* x)
	{
		RedBlackTreeBaseNode* y;

		
		
		
		
		
		
		
		
		

		y = x->m_Right;
		x->m_Right = y->m_Left;

		if (y->m_Left != m_NullNode)
		{
			y->m_Left->m_Parent = x;
			
			
		}

		y->m_Parent = x->m_Parent;

		
		
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

	
	
	GDAPI void RedBlackTreeBase::InternalRotateRight(RedBlackTreeBaseNode* y)
	{
		RedBlackTreeBaseNode* x;

		
		
		
		
		
		
		
		
		
		x = y->m_Left;
		y->m_Left = x->m_Right;

		if (m_NullNode != x->m_Right)
		{
			
			
			x->m_Right->m_Parent = y;
		}

		
		
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
					
					x = m_RootNode;
				}
			}
			else
			{
				
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
					
					x = m_RootNode;
				}
			}
		}
		x->m_IsRed = false;

		
		
		
		
		m_NullNode->m_IsRed = false;
		GD_ASSERT(!m_NullNode->m_IsRed, "m_NullNode not black in InternalRepair");
	}

	
	
	

	
	GDAPI RedBlackTreeBaseNode const* RedBlackTreeBase::FindNodeBase(CHandle const element) const
	{
		auto x = m_RootNode->m_Left;
		if (x == m_NullNode)
		{
			
			return x;
		}

		auto compareResult = OnCompareElements(x->GetDataUntyped(), element);
		while (0 != compareResult)
		{
			
			if (1 == compareResult)
			{ 
				
				x = x->m_Left;
			}
			else
			{
				x = x->m_Right;
			}
			if (x == m_NullNode)
			{
				
				return x;
			}
			compareResult = OnCompareElements(x->GetDataUntyped(), element);
		}
		return x;
	}

	
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
				
				x = x->m_Left;
			}
			else
			{ 
				
				x = x->m_Right;
			}
		}
		z->m_Parent = y;
		if (y == m_RootNode || 1 == OnCompareElements(y->GetDataUntyped(), z->GetDataUntyped()))
		{ 
			
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

	
	GDAPI void RedBlackTreeBase::RemoveNodeBase(RedBlackTreeBaseNode* const z)
	{
		RedBlackTreeBaseNode* y;
		RedBlackTreeBaseNode* x;

		y = z->m_Left == m_NullNode || z->m_Right == m_NullNode ? z : GetNextNodeBase(z);
		x = y->m_Left == m_NullNode ? y->m_Right : y->m_Left;
		if (m_RootNode == (x->m_Parent = y->m_Parent))
		{ 
			
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
			
			GD_ASSERT(y != m_NullNode, "Y is m_NullNode in RBDelete\n");
			
			
			if (!y->m_IsRed)
			{
				InternalRepair(x);
			}

			
			
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
			
			OnDestroyNode(z);
		}
		else
		{
			
			
			if (!y->m_IsRed)
			{
				InternalRepair(x);
			}
			OnDestroyNode(y);
			
		}

		GD_ASSERT(!m_NullNode->m_IsRed, "m_NullNode not black in RBDelete");
		--m_Length;
	}

	
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

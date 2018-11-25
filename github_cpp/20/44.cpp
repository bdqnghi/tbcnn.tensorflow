

#ifndef MODULES_OTL_REDBLACKTREENODE_H
#define MODULES_OTL_REDBLACKTREENODE_H


template<typename T>
class OtlRedBlackTreeNode
{
public:

	OtlRedBlackTreeNode(const T& item);
	~OtlRedBlackTreeNode();

	void Initialize();

	
	void DeleteChildren();

	
	void SetParent(OtlRedBlackTreeNode* p);

	
	OtlRedBlackTreeNode* Child(int dir) const;

	
	void SetChild(OtlRedBlackTreeNode* n, int dir);

	
	void UnlinkChild(OtlRedBlackTreeNode* n);

	
	OtlRedBlackTreeNode* Sibling() const;

	
	OtlRedBlackTreeNode* Parent() const;

	bool HasNoRedChildren() const;
	bool HasTwoRedChildren() const;

	
	OtlRedBlackTreeNode* Furthest(int dir);

	
	bool IsRoot() const;

	
	bool IsLeaf() const;

	bool IsBlack() const;
	bool IsRed() const;
	void SetBlack();
	void SetRed();

	static bool IsRed(OtlRedBlackTreeNode* n)
	{
		return n ? n->color == RED : false;
	}

	
	OtlRedBlackTreeNode* Neighbour(int dir) const;

	
	OtlRedBlackTreeNode* Next() const;

	
	OtlRedBlackTreeNode* Previous() const;

#if defined(RBTREE_DEBUG) || defined(SELFTEST)
	
	size_t BlackDepth() const;

	
	size_t Depth() const;

	
	bool FindDoubleRed() const;
#endif 
	T item;
	enum { RED, BLACK } color;
	OtlRedBlackTreeNode* parent;
	OtlRedBlackTreeNode* child[2];
}; 



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

	
	OtlRedBlackTreeNode* p = n->parent;
	if (p)
	{
		
		if (p->child[!dir] == n)
			return p;

		
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
#endif 

#endif 

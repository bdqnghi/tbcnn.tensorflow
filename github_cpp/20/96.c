#ifdef _REDBLACKTREE_H_



template <class T>
RedBlackTree<T>::RedBlackTree()
{
	root = NULL;
	size = 0;
}


template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree) 
{

	if (rbtree.root != NULL)
	{
		
		this->root = new Node<T>((rbtree.root)->data);
		(this->root)->is_black = (rbtree.root)->is_black;

		CopyTree(this->root, rbtree.root, (rbtree.root)->p);
		this->size = rbtree.size;
	}
	else
	{
		this->root = NULL;
	}

}


template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode)
{
	Node<T>* ref = NULL;

	
	
	
	

	if (parentnode == NULL)
	{
		
		
		ref = thisnode;
	}
	else if (parentnode->left == sourcenode)
	{
		ref = new Node<T>(sourcenode->data);
		ref->is_black = sourcenode->is_black;
		ref->p = thisnode;
		thisnode->left = ref;
	}
	else
	{
		ref = new Node<T>(sourcenode->data);
		ref->is_black = sourcenode->is_black;
		ref->p = thisnode;
		thisnode->right = ref;
	}

	if (sourcenode->left != NULL)
		CopyTree(ref, sourcenode->left, sourcenode);
	if (sourcenode->right != NULL)
		CopyTree(ref, sourcenode->right, sourcenode);

	return GetRoot(); 

}


template<class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll();
}


template<class T>
void RedBlackTree<T>::RemoveAll()
{
	RemoveAll(root);
	if (size == 0)
		root = NULL;
}


template<class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	
	
	if (node != NULL)
	{
		if (node->left != NULL)
			RemoveAll(node->left);
		if (node->right != NULL)
			RemoveAll(node->right);

		node->left = NULL;
		node->right = NULL;
		node->p = NULL;
		node = NULL;

		delete node;
		size--;
	}
}

template<class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
{
	if (this == &rbtree)
	{
		return *this;
	}
	else
	{
		
		RemoveAll();
		if (rbtree.root != NULL)
		{
			
			this->root = new Node<T>((rbtree.root)->data);
			(this->root)->is_black = (rbtree.root)->is_black;

			CopyTree(this->root, rbtree.root, (rbtree.root)->p);
			this->size = rbtree.size;
		}
		else
		{
			this->root = NULL;
			return *this;
		}

	}
}



template <class T>
bool RedBlackTree<T>::Insert(T item)
{
	Node<T>* x = NULL;
	Node<T>* y = NULL;

	
	if (size <= 0 && root == NULL)
	{
		BSTInsert(item);
		root->is_black = true;
		size = 1;
		return true;
	}
	
	else if (Search(item) == true)
	{
		
		return false;
	}
	
	else
	{
		
		x = BSTInsert(item);
		x->is_black = false;

		while (x != root && (x->p)->is_black == false)
		{
			if (((x->p) == ((x->p)->p)->left))
			{
				y = ((x->p)->p)->right; 

				if (y != NULL && y->is_black == false) 
				{
					(x->p)->is_black = true;
					y->is_black = true;
					((x->p)->p)->is_black = false;
					x = (x->p)->p;
				}
				else
				{
					if (x == (x->p)->right)
					{
						x = (x->p);
						LeftRotate(x);
					}
					(x->p)->is_black = true;
					((x->p)->p)->is_black = false;
					RightRotate((x->p)->p);
				}
			}
			else
			{
				y = ((x->p)->p)->left;

				if (y != NULL && y->is_black == false) 
				{
					(x->p)->is_black = true;
					y->is_black = true;
					((x->p)->p)->is_black = false;
					x = (x->p)->p;
				}
				else
				{
					if (x == (x->p)->left)
					{
						x = (x->p);
						RightRotate(x);
					}
					(x->p)->is_black = true;
					((x->p)->p)->is_black = false;
					LeftRotate((x->p)->p);
				}

			}

		}

	}

	root->is_black = true;
	size++;
	return true;
}

template<class T>
bool RedBlackTree<T>::Remove(T item)
{

	Node<T>* y = NULL; 
	Node<T>* yparent = NULL; 
	Node<T>* node = root; 
	Node<T>* x = NULL; 
	bool xisleftchild = true;

	if (Search(item) == false)
	{
		cout << "Failed to remove; Item does not exist" << endl;
		return false;
	}
	else
	{
		while (node != NULL)
		{
			if (item == node->data)
			{
				break; 
			}
			else if (item < node->data)
				node = node->left;
			else
				node = node->right;
		}
	}

	if (node == root)
	{
		root = NULL;
		size--;
		return true;
	}

	if (node->left == NULL || node->right == NULL) 
		y = node;
	else
		y = Predecessor(node);

	if (y->left != NULL) 
		x = y->left;
	else if (y->right != NULL)
		x = y->right;

	if (x != NULL && y->p != NULL) 
		x->p = y->p;


	if (y->p == NULL) 
		root = x;
	else
	{
		
		yparent = y->p;
		if (y == yparent->left)
			yparent->left = x;
		else
			yparent->right = x;
	}

	if (node != y)
		node->data = y->data; 

	if (y->is_black == true) 
	{
		if (yparent->left == x)
			xisleftchild = true;
		else
			xisleftchild = false;

		RBDeleteFixUp(x, yparent, xisleftchild);
	}

	if (y != NULL)
	{
		y->right = NULL;
		y->p = NULL;
		y->left = NULL;
		delete y;
	}
	else
		delete y;

	size--;
	return true;
}

template<class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	Node<T>* y = NULL;

	while (x != root && (x == NULL || x->is_black == true))
	{
		if (xisleftchild == true)
		{
			y = xparent->right; 

			if (y->is_black == false) 
			{
				y->is_black = true;
				xparent->is_black = false; 
				LeftRotate(xparent);
				y = xparent->right;
			}

			if ((y->left == NULL || (y->left)->is_black == true) && (y->right == NULL || (y->right)->is_black == true)) 
			{
				
				y->is_black = false;
				x = xparent;

				
				if (x->p != NULL)
				{
					xparent = x->p;
					if (x == xparent->left)
						xisleftchild = true;
					else
						xisleftchild = false;
				}
				
			}
			else
			{
				if (y->right == NULL || (y->right)->is_black == true)
				{
					

					(y->left)->is_black = true;
					y->is_black = false;
					RightRotate(y);
					y = xparent->right; 
				}

				y->is_black = xparent->is_black;
				xparent->is_black = true;
				if (y->right != NULL)
				{
					(y->right)->is_black = true;
				}
				LeftRotate(xparent);
				x = root;
			}
		}
		else 
		{
			y = xparent->left;
			if (y->is_black == false) 
			{
				y->is_black = true;
				xparent->is_black = false; 
				RightRotate(xparent);
				y = xparent->left;
			}

			if ((y->left == NULL || (y->left)->is_black == true) && (y->right == NULL || (y->right)->is_black == true)) 
			{
				
				y->is_black = false;
				x = xparent;

				
				if (x->p != NULL)
				{
					xparent = x->p;
					if (x == xparent->left)
						xisleftchild = true;
					else
						xisleftchild = false;
				}
				
			}
			else
			{
				if (y->left == NULL || (y->left)->is_black == true)
				{
					

					(y->right)->is_black = true;
					y->is_black = false;
					LeftRotate(y);
					y = xparent->left; 
				}

				y->is_black = xparent->is_black;
				xparent->is_black = true;
				if (y->left != NULL)
				{
					(y->left)->is_black = true;
				}
				RightRotate(xparent);
				x = root;
			}
		}
	}

	x->is_black = true;
}

template<class T>
unsigned int RedBlackTree<T>::Size() const
{
	return size;
}

template<class T>
unsigned int RedBlackTree<T>::Height() const
{
	return CalculateHeight(root);
}

template<class T>
unsigned int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
	
	
	
	
	unsigned int heightleft = 0;
	unsigned int heightright = 0;

	if (root == NULL)
	{
		return 0;
	}
	else if (root->left == NULL || root->right == NULL)
	{
		return 1;
	}

	if (node->left != NULL)
		heightleft = CalculateHeight(node->left);

	if (node->right != NULL)
		heightright = CalculateHeight(node->right);

	if (heightleft > heightright)
		return heightleft + 1;
	else
		return heightright + 1;
}

#endif

#include "redblacktree.h";
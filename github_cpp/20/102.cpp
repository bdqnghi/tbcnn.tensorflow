#ifdef _REDBLACKTREE_H_
#include<stdexcept>

#include <iostream>
#include <math.h>






template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode)
{
	if(sourcenode != NULL)
	{
		if(thisnode == NULL)
		{
			thisnode = new Node<T>();
		}
		thisnode->data = sourcenode->data; 
		thisnode->is_black = sourcenode->is_black; 

		thisnode = parentnode;

		if(sourcenode->left != NULL)
		{
			CopyTree( new Node<T>(),sourcenode->left,thisnode);
		}
		if(sourcenode->right != NULL)
		{
			CopyTree( new Node<T>(),sourcenode->right,thisnode);
		}
	}
}




template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	
	if(node != NULL)
	{
		RemoveAll(node->left);
		RemoveAll(node->right);	
		delete node;
		size--;
	}
}



template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	bool isBlack = false; 
	Node<T>* w = NULL;
	if (x == NULL || x->is_black) 
	{
		isBlack = true;
	}

	while (x != root && isBlack)
	{
		if (xisleftchild)
		{
			w = xparent->right; 
			if (!w->is_black)
			{
				w->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent); 
				w = xparent->right;
			}
			if ((w->left == NULL || w->left->is_black) && (w->right == NULL || w->right->is_black)) 
			{
				w->is_black = false;
				x = xparent;
				xparent = x->p;
				xisleftchild = (xparent != NULL && x == xparent->left);
			}
			else {
				if (w->right == NULL || w->right->is_black)
				{
					w->left->is_black = true;
					w->is_black = false;
					RightRotate(w);
					w = xparent->right;
				}
				w->is_black = xparent->is_black;
				xparent->is_black = true;
				if (w->right != NULL)
				{
					w->right->is_black = true;
				}
				LeftRotate(xparent);
				x = root;
				xparent = NULL;
			}
		}
		else 
		{
			w = xparent->left;
			if (!w->is_black)
			{
				w->is_black = true;
				xparent->is_black = false;
				RightRotate(xparent);
				w = xparent->left;
			}
			if ((w->left == NULL || w->left->is_black) && (w->right == NULL || w->right->is_black))
			{
				w->is_black = false;
				x = xparent;
				xparent = x->p;
				xisleftchild = (xparent != NULL && x == xparent->left);
			}
			else
			{
				if (w->left == NULL || w->left->is_black)
				{
					w->right->is_black = true;
					w->is_black = false;
					LeftRotate(w);
					w = xparent->left;
				}
				w->is_black = xparent->is_black;
				xparent->is_black = true;
				if (w->left != NULL)
				{
					w->left->is_black = true;
				}
				RightRotate(xparent);
				x = root;
				xparent = NULL;
			}
		}
	}
	if (x != NULL) 
	{
		x->is_black = true;
	}
}



template <class T>
unsigned int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
	if(node == NULL) 
	{
		return 0;
	}
	else
	{
		unsigned int tempLeft = 0; 
		unsigned int tempRight = 0; 

		if(node->left != NULL)
		{
			unsigned int tempLeft = CalculateHeight(node->left);
		}
		if(node->right != NULL)
		{
			unsigned int tempRight = CalculateHeight(node->right);
		}

		if(tempLeft > tempRight) 
		{
			return tempLeft + 1;
		}
		else
		{
			return tempRight + 1;
		}
	}

}




template <class T>
RedBlackTree<T>::RedBlackTree()
{
	size = 0;
	root = NULL;
}


template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
	root = new Node<T>(root->data); 
	CopyTree(root, rbtree.GetRoot(), NULL);	
}



template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll();
}


template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
{
	if (this != &rbtree) 
	{
		this->RemoveAll(root);
		CopyTree(NULL, rbtree.root, NULL);
		size = rbtree.size;
	}
	return *this;
}






template <class T>
bool RedBlackTree<T>::Insert(T item)
{
	
	if(Search(item) == false)  
	{
		Node<T>* x = BSTInsert(item);  
		Node<T>* y = NULL;
		x->is_black = false;  
		while(x->p != NULL && x->p->is_black == false) 
		{
			if(x->p == x->p->p->left)
			{
				y = x->p->p->right; 
				if(y != NULL && y->is_black == false) 
				{
					x->p->is_black = true;
					y->is_black = true;
					x->p->p->is_black = false;
					x = x->p->p;
				}
				else
				{
					if(x == x->p->right)
					{
						x = x->p;
						LeftRotate(x);
					}
					x->p->is_black = true;
					x->p->p->is_black = false;
					RightRotate(x->p->p);
				}
			}
			else 
			{
				y = x->p->p->left;
				if(y != NULL && y->is_black == false)
				{
					x->p->is_black = true;
					y->is_black = true;
					x->p->p->is_black = false;
					x = x->p->p;
				}
				else
				{
					if(x == x->p->left)
					{
						x = x->p;
						RightRotate(x);
					}

					x->p->is_black = true;
					x->p->p->is_black = false;					
					LeftRotate(x->p->p);

				}
			}

		}
		root->is_black = true;
		size++; 
		return true;
	}
	return false;
}



template <class T>
bool RedBlackTree<T>::Remove(T item)
{
	if(Search(item) == false) 
	{
		return false;
	}

	Node<T>* z = root;

	while (z != NULL) 
	{
		if (item == z->data)
			break;
		else if (item < z->data)
			z = z->left;
		else
			z = z->right;
	}

	Node<T>* y = NULL;
	if (z->left == NULL || z->right == NULL)
	{
		y = z; 
	}
	else
	{
		y = Predecessor(z); 
	}

	Node<T>* x = NULL;
	if (y->left != NULL)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}
	if (x != NULL)
	{
		x->p = y->p;
	}
	Node<T>* xParent = y->p;
	bool yLCH = false;

	if (y->p == NULL) 
	{
		root = x;
	}
	else if (y == y->p->left) 
	{
		y->p->left = x;
		yLCH = true;
	}
	else
	{
		y->p->right = x;
		yLCH = false;
	}

	if (y != z)
	{
		z->data = y->data;
	}

	if (y->is_black)
	{
		RBDeleteFixUp(x, xParent, yLCH);
	}

	delete y; 
	size--; 
	z = NULL;
	return true;
}


template <class T>
void RedBlackTree<T>::RemoveAll()
{
	RemoveAll(root);
	root = NULL;
}


template <class T>
unsigned int RedBlackTree<T>::Size() const
{
	return size;
}



template <class T>
unsigned int RedBlackTree<T>::Height() const
{
	return CalculateHeight(root);
}


#endif
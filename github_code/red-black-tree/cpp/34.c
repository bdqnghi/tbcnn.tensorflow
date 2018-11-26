




#ifdef _REDBLACKTREE_H_
#include "redblacktree.h"

template<class T>
unsigned int RedBlackTree<T>::Size() const
{
	return size;
}

template<class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	if (node!= NULL)
	{
		RemoveAll(node->left);
		RemoveAll(node->right);
		delete node;
	}
}

template<class T>
void RedBlackTree<T>::RemoveAll()
{
	RemoveAll(root);
	size=0;
}

template<class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll();
}

template<class T>
RedBlackTree<T>::RedBlackTree()
{
	root = NULL;
	size = 0;
}

template <class T>
unsigned int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
	if (node == NULL)
		return 0;
	else 
		return max(CalculateHeight(node->left),CalculateHeight(node->right))+1;

}

template <class T>
unsigned int RedBlackTree<T>::Height() const
{
	return CalculateHeight(root);
}


template<class T>
bool RedBlackTree<T>::Insert(T item)
{
	if (Search(item))
	{
		return false;              // if item is alreay in the tree then return false;
	}
	else
	{
		Node<T>* x = BSTInsert(item);              //new node inserted
		Node<T>* y ;					//x's uncle node
		while((x!=root) && (!(x->p->is_black)))
		{
			if (x->p == x->p->p->left)    //check if x's parent is a left child
			{
				y = x->p->p->right;          //uncle of "x"
				if (y->is_black == false)           //same as x.p
				{
					x->p->is_black = true;
					y->is_black = true;
					x->p->p->is_black = false;
					x= x->p->p;
				}
				else
				{
					if (x == x->p->right)
					{
						x = x->p ;
						LeftRotate(x) ;
					} 
					x->p->is_black= true;
					x->p->p->is_black = false ;
					RightRotate(x->p->p);
				}
			}
			else
			{
				y=x->p->p->left;
				if (!(y->is_black))
				{
					x->p->is_black = true;
					y->is_black = true;
					x->p->p->is_black=false;
					x=x->p->p;
				}
				else 
				{
					if (x == x->p->left)
					{
						x=x->p;
						RightRotate(x);
					}
					x->p->is_black = true;
					x->p->p->is_black = false;
					LeftRotate(x->p->p);
				}
			}
		}
	}
	root->is_black=true;
	size++;
	return true;
}




template<class T>
bool RedBlackTree<T>::Remove(T item)
{
	Node<T>* z = root;
	Node<T>* y;
	Node<T>* x;
	if(!Search(item)|| (root==NULL ))
	{
		return false;     //item not found
	}
	else
	{
		while (item!=z->data)
		{
			if (item < z->data)
			{z=z->left;}
			else
			{z=z->right;}
		}
		if ((z->left == NULL) || (z->right == NULL))
		{
			y = z;
		}
		else
		{
			y = Predecessor(z);
		}
		if (y->left != NULL)
		{
			x = y->left;
		}
		else
		{
			x = y->right;
			x->p = y->p;
		}
		if (y->p == NULL)
		{root = x;}
		else
			if (y==y->p->left)
			{y->p->left=x;}
			else
			{y->p->right=x;}
		if (y!=z)
		{z->data=y->data;}
		if(y->is_black)
		{

			RBDeleteFixUp(x,x->p,x->is_black);
		}


	}
	return true;
}


template<class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	while((x!=root)&&(x->is_black))
	{
		if(x == xparent->left)    //x is left child
		{
			Node<T>* y = xparent->right;
			if (!(y->is_black))
			{
				y->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent);
				y=xparent->right;
			}
			if ((y->left->is_black) && (y->right->is_black))
			{
				y->is_black = false;
				x=xparent;
			}
			else
			{
				if(y->right->is_black)
				{
					y->left->is_black = true;
					y->is_black = false;
					RightRotate(y);
					y = xparent->right;
				}
				y->is_black = xparent->is_black;
				xparent->is_black= true;
				y->right->is_black = true;
				LeftRotate(xparent);
				x = root;
			}
		}
		else
		{
			Node<T>* y=xparent->left;
			if (!(y->is_black))
			{
				y->is_black = true;
				xparent->is_black = false;
				RightRotate(xparent);
				y=xparent->left;
			}
			if ((y->left->is_black) && (y->right->is_black))
			{
				y->is_black = false;
				x=xparent;
			}
			else
			{
				if(y->right->is_black)
				{
					y->right->is_black = true;
					y->is_black = false;
					LeftRotate(y);
					y = xparent->left;
				}
				y->is_black = xparent->is_black;
				xparent->is_black= true;
				y->left->is_black = true;
				RightRotate(xparent);
				x = root;
			}
		}

	}
	x->is_black = true;
}

template<class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
{
	if(this != &rbtree)
	{
		Node<T>* thisnode;
		RemoveAll();
		root = CopyTree(thisnode,rbtree.GetRoot(),root);
		size=rbtree.size;
	}
	return *this;
}


template <class T>
 Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode)
 {
	 if (sourcenode!=null)
	 {
		 thisnode = new Node<T>(sourcenode.data);
		 thisnode->is_black = sourcenode->is_black;
		 parentnode = thisnode;
		 parentnode.left=copytree(thisnode,sourcenode.left,parentnode.left);
		 parentnode.right=copytree(thisnode,sourcenode.right,parentnode.right);
	 }
	 
 }

#endif
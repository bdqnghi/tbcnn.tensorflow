



#ifdef _REDBLACKTREE_H_

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <iostream>






template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode)
{

	if (sourcenode != NULL)
	{
		Node<T> *thisnode = NULL;
		thisnode = new Node<T>(sourcenode->data);
		thisnode->is_black = sourcenode->is_black;

		if (this->root != NULL && sourcenode->data != this->root->data)
		{
			if (sourcenode->p->left != NULL && sourcenode == sourcenode->p->left)
			{
				parentnode->left = thisnode;
				thisnode->p = parentnode;
				parentnode = thisnode;
			}
			else if (sourcenode->p->right != NULL && sourcenode == sourcenode->p->right)
			{
				parentnode->right = thisnode;
				thisnode->p = parentnode;
				parentnode = thisnode;
			}
		}
		if (this->root == NULL)
		{
			root = thisnode;
			parentnode = root;
		}

		CopyTree(sourcenode->left, parentnode);
		CopyTree(sourcenode->right, parentnode);

	} 
	return sourcenode;
}



template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	if (node != NULL)
	{
		RemoveAll(node->left);
		node->left = NULL;
		RemoveAll(node->right);
		node->right = NULL;

		node->p = NULL;
		delete(node);
	}
}




template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{

	while (x != root && (x == NULL || x->is_black == true))
	{
		if (xisleftchild == true)
		{
			Node<T>* Y;
			Y = xparent->right;

			if (Y->is_black == false)
			{
				Y->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent);
				Y = xparent->right;
			}
			if ((Y->left == NULL || Y->left->is_black == true) && (Y->right == NULL || Y->right->is_black == true))
			{
				Y->is_black = false;
				x = xparent; 
				if (xparent->p != NULL)
				{
					xparent = xparent->p;
					if (x == xparent->left) {xisleftchild = true;}
					else {xisleftchild = false;}
				}
			}
			else
			{
				if (Y->right == NULL ||Y->right->is_black == true)
				{
					Y->left->is_black = true;
					Y->is_black = false;
					RightRotate(Y);
					Y = xparent->right;
				}
				Y->is_black = xparent->is_black;
				xparent->is_black = true;
				Y->right->is_black = true;
				LeftRotate(xparent);
				x = root;
			}
		}
		else 
		{
			Node<T>* Y;
			Y = xparent->left;

			if (Y->is_black == false)
			{
				Y->is_black = true;
				xparent->is_black = false;
				RightRotate(xparent);
				Y = xparent->left;
			}
			if ((Y->left == NULL || Y->left->is_black == true) && (Y->right == NULL || Y->right->is_black == true))
			{
				Y->is_black = false;
				x = xparent; 
				if (xparent->p != NULL)
				{
					xparent = xparent->p;
					if (x == xparent->left) {xisleftchild = true;}
					else {xisleftchild = false;}
				}
			}
			else
			{
				if (Y->left == NULL || Y->left->is_black == true)
				{
					Y->right->is_black = true;
					Y->is_black = false;
					LeftRotate(Y);
					Y = xparent->left;
				}
				Y->is_black = xparent->is_black;
				xparent->is_black = true;
				Y->left->is_black = true;
				RightRotate(xparent);
				x = root;
			}
		}
	}
	x->is_black = true;
}



template <class T>
int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
	if (node == NULL)
	{
		return 0;
	}

	int Left = CalculateHeight(node->left);
	int Right = CalculateHeight(node->right);

	if (Left > Right)
	{
		Left = Left + 1;
		return Left;
	}
	else
	{
		Right = Right + 1;
		return Right;
	}

}




template <class T>
RedBlackTree<T>::RedBlackTree()
{
	root = NULL;
	size = 0;
}


template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
	if (rbtree.Size() == 0)
	{
		this->size = 0;
		this->root = NULL;
		return;
	}


	Node<T>* R = rbtree.GetRoot();
	this->size = rbtree.Size();
	CopyTree(R, NULL);
}



template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll();
}







template <class T>
bool RedBlackTree<T>::Insert(T item)
{
	if (Search(item) == true)
	{
		return false;
	}

	Node<T>*node;
	node = BSTInsert(item);
	node->is_black = false;

	if (size == 2)
	{
		if (node->data > root->data && node->data == root->right->data)
		{
			
		}
		else if (node->data < root->data && node->data == root->left->data)
		{
			
		}
		else if (node->p->p != NULL && node->p->p->left != NULL &&
			node->p->p->left->left != NULL && node == node->p->p->left->left)
		{
			RightRotate(root);
		}
		else if (node->p->p != NULL && node->p->p->right != NULL &&
			node->p->p->right->right != NULL && node == node->p->p->right->right)
		{
			LeftRotate(root);
		}
		else if (node->p->p->left != NULL && node->p->p->left->right != NULL && node == node->p->p->left->right)
		{
			LeftRotate(node->p);
			RightRotate(root);
		}
		else if (node->p->p->right != NULL && node->p->p->right->left != NULL && node == node->p->p->right->left)
		{
			RightRotate(node->p);
			LeftRotate(root);
		}

		root->is_black = true;
		root->left->is_black = false;
		root->right->is_black = false;
	}

	while (node != root && node->p->is_black == false)
	{
		if (node->p == node->p->p->left)
		{
			Node<T>* Y;
			Y = node->p->p->right; 

			if (Y != NULL && Y->is_black == false) 
			{
				node->p->is_black = true;
				Y->is_black = true;
				node->p->p->is_black = false;
				node = node->p->p;
			}
			else 
			{
				if (node == node->p->right)
				{
					node = node->p;
					LeftRotate(node);
				}
				node->p->is_black = true;
				node->p->p->is_black = false;
				RightRotate(node->p->p);
			}
		}
		else 
		{
			Node<T>* Y;
			Y = node->p->p->left; 

			if (Y != NULL && Y->is_black == false) 
			{
				node->p->is_black = true;
				Y->is_black = true;
				node->p->p->is_black = false;
				node = node->p->p;
			}
			else 
			{
				if (node == node->p->left)
				{
					node = node->p;
					RightRotate(node);
				}
				node->p->is_black = true;
				node->p->p->is_black = false;
				LeftRotate(node->p->p);
			}

		}
	}
	this->root->is_black = true;
	this->size++;
	return true;
}



template <class T>
bool RedBlackTree<T>::Remove(T item)
{
	if (Search(item) == false) { return false; }

	Node<T>* node = root;

	bool IsLeft = false;
	bool Black = false;

	while (node != NULL)
	{
		if (item == node->data) { break; }
		else if (item < node->data) { node = node->left; }
		else { node = node->right; }
	}

	if (size == 2)
	{
		if (node == root)
		{
			if (root->left != NULL) 
			{ 
				root->data = root->left->data;
				delete root->left;
			}
			else if (root->right != NULL) 
			{ 
				root->data = root->right->data;
				delete root->right;
			}
		}

		node = NULL;
		root->left = NULL;
		root->right = NULL;
		root->is_black = true;
		size--;
		return true;
	}
	if (size == 1)
	{
		root = NULL;
		size--;
		return true;
	}

	Node<T>* predecessor = Predecessor(node);
	predecessor = Predecessor(node);

	if (predecessor != NULL)
	{
		if (predecessor->p->left != NULL && predecessor == predecessor->p->left)
		{
			IsLeft = true;
		}
		else if (predecessor->p->right != NULL && predecessor == predecessor->p->right)
		{
			IsLeft = false;
		}
	}
	else
	{
		if (node->p->left != NULL && node == node->p->left)
		{
			IsLeft = true;
		}
		else if (node->p->right != NULL && node == node->p->right)
		{
			IsLeft = false;
		}
	}

	Node<T>* x = node;
	Node<T>* y = predecessor;
	Node<T>* z = node;

	
	if (predecessor != NULL)
	{
		y = predecessor;
	}
	else
	{
		y = z;
	}
	
	if (y->right != NULL)
	{
		x = y->right;
	}
	else
	{
		x = y->left;
	}
	
	if (y == root)
	{
		root = x;
	}
	else
	{
		if (y->left == NULL && y->right == NULL)
		{
			
		}
		else if (y == y->p->left)
		{
			y->p->left = x;
			x->p = y->p;
		}
		else if (y == y->p->right)
		{
			y->p->right = x;
			x->p = y->p;
		}
	}
	
	if (y == predecessor)
	{
		z->data = y->data;
	}
	
	if (y == y->p->left)
	{
		y->p->left = NULL;
	}
	else if (y == y->p->right)
	{
		y->p->right = NULL;
	}

	Black = y->is_black;

	
	if (Black == true)
	{
		RBDeleteFixUp(x, y->p, IsLeft);
	}

	delete y;

	z = NULL;
	predecessor = NULL;
	node = NULL;
	size--;
	root->is_black = true;
	return true;
}


template <class T>
void RedBlackTree<T>::RemoveAll()
{
	if (this->root != NULL && size != 0)
	{
		RemoveAll(this->root);
		size = 0;
		root = NULL;
	}
}





template <class T>
int RedBlackTree<T>::Size() const
{
	return this->size;
}



template <class T>
int RedBlackTree<T>::Height() const
{
	if (root == NULL)
	{
		return 0;
	}
	else if (root != NULL && root->left == NULL && root->right == NULL)
	{
		return 1;
	}

	return CalculateHeight(root);
}



template <class T>
RedBlackTree<T>& RedBlackTree<T>:: operator= (const RedBlackTree<T>& rbtree)
{
	if (rbtree.Size() == 0)
	{
		this->RemoveAll();
		root = NULL;
		return *this;
	}

	if (this != &rbtree)
	{
		if (this->root != NULL)
		{
			this->RemoveAll();
		}

		Node<T>* R = rbtree.GetRoot();
		this->root = new Node<T>(R->data);
		this->size = rbtree.Size();
		CopyTree(R, this->root);
		
	}
	this->root->is_black = true;
	return *this;
}


#endif _REDBLACKTREE_H_
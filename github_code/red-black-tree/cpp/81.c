// File:        redblacktree.cpp
// Date:        2016-02-27
// Description: Implementation of a RedBlackTree class and template Node class 

#ifdef _REDBLACKTREE_H_

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <iostream>

//------------------------------------HELPER FUNCTIONS-----------------------------------------

// recursive helper function for deep copy
// creates a new node "thisnode" based on sourcenode's contents, links back to parentnode,
// and recurses to create left and right children
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

// recursive helper function for tree deletion
// deallocates nodes in post-order
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


// Tree fix, performed after removal of a black node
// Note that the parameter x may be NULL
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
				x = xparent; //and into while again
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
		else // Symmetric
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
				x = xparent; //and into while again
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

// Calculates the height of the tree
// Requires a traversal of the tree, O(n)
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

//--------------------------------------------Constructors--------------------------------------------   

// default constructor
template <class T>
RedBlackTree<T>::RedBlackTree()
{
	root = NULL;
	size = 0;
}

// copy constructor, performs deep copy of parameter
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

// destructor
// Must deallocate memory associated with all nodes in tree
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll();
}


//------------------------------------------------MUTATOR---------------------------------------------   

// Calls BSTInsert and then performs any necessary tree fixing.
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
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
			//Do Nothing
		}
		else if (node->data < root->data && node->data == root->left->data)
		{
			//Do Nothing
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
			Y = node->p->p->right; // �uncle� of node

			if (Y != NULL && Y->is_black == false) //color same as node->p
			{
				node->p->is_black = true;
				Y->is_black = true;
				node->p->p->is_black = false;
				node = node->p->p;
			}
			else // Y->colour == black
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
		else //node->p == node->p->p->right
		{
			Node<T>* Y;
			Y = node->p->p->left; // �uncle� of node

			if (Y != NULL && Y->is_black == false) //color same as node->p
			{
				node->p->is_black = true;
				Y->is_black = true;
				node->p->p->is_black = false;
				node = node->p->p;
			}
			else // Y->colour == black
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

// Removal of an item from the tree.
// Must deallocate deleted node after RBDeleteFixUp returns
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

	//Predecessor exists ?
	if (predecessor != NULL)
	{
		y = predecessor;
	}
	else
	{
		y = z;
	}
	//x = y's child
	if (y->right != NULL)
	{
		x = y->right;
	}
	else
	{
		x = y->left;
	}
	//Is y root ?
	if (y == root)
	{
		root = x;
	}
	else
	{
		if (y->left == NULL && y->right == NULL)
		{
			//Do Nothing
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
	//Y is predecessor?
	if (y == predecessor)
	{
		z->data = y->data;
	}
	//UNLINK Y
	if (y == y->p->left)
	{
		y->p->left = NULL;
	}
	else if (y == y->p->right)
	{
		y->p->right = NULL;
	}

	Black = y->is_black;

	//IF predecessor is BLACK
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

// deletes all nodes in the tree. Calls recursive helper function.
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


//------------------------------------------------ACCESSOR--------------------------------------------

// returns the number of items in the tree
template <class T>
int RedBlackTree<T>::Size() const
{
	return this->size;
}

// returns the height of the tree, from root to deepest null child. Calls recursive helper function.
// Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
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


// overloaded assignment operator
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
#ifdef _REDBLACKTREE_H_


// Default Constructor
template <class T>
RedBlackTree<T>::RedBlackTree()
{
	root = NULL;
	size = 0;
}

// Copy Constructor
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree) //rbtree is the object source
{

	if (rbtree.root != NULL)
	{
		// these 2 lines will make the root not NULL
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

// Copy Helper
template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode)
{
	Node<T>* ref = NULL;

	// We need 3 pointers for this to all work
	// First, a pointer to the parent node in the original tree
	// Second, a pointer to the node itself in the original tree
	// Third, a pointer to the parent node in the copy tree

	if (parentnode == NULL)
	{
		/*thisnode = new Node<T>(sourcenode->data);*/
		/*thisnode->p = NULL;*/
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

	return GetRoot(); // this function could have been void instead, this is just to return a dummy address

}

// Default Destructor
template<class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll();
}

// Remove all 'call helper'
template<class T>
void RedBlackTree<T>::RemoveAll()
{
	RemoveAll(root);
	if (size == 0)
		root = NULL;
}

// Helper Remove All
template<class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	/*Node<T>* ref = node;*/
	// traveling in post order
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
		// remove all nodes first
		RemoveAll();
		if (rbtree.root != NULL)
		{
			// these 2 lines will make the root not NULL
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


// Insert RedBlackTree
template <class T>
bool RedBlackTree<T>::Insert(T item)
{
	Node<T>* x = NULL;
	Node<T>* y = NULL;

	// empty tree
	if (size <= 0 && root == NULL)
	{
		BSTInsert(item);
		root->is_black = true;
		size = 1;
		return true;
	}
	// if item is a dupe
	else if (Search(item) == true)
	{
		//cout << "Item already exists" << endl;
		return false;
	}
	// general case
	else
	{
		// x contains the pointer to the newly added node
		x = BSTInsert(item);
		x->is_black = false;

		while (x != root && (x->p)->is_black == false)
		{
			if (/*((x->p)->p)->left != NULL && */((x->p) == ((x->p)->p)->left))
			{
				y = ((x->p)->p)->right; // uncle of 'x'

				if (y != NULL && y->is_black == false) // if x's parent is red and uncle is red
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

				if (y != NULL && y->is_black == false) // if x's parent is red and uncle is red
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

	Node<T>* y = NULL; // to be predecessor
	Node<T>* yparent = NULL; // to be predecessor's parent
	Node<T>* node = root; // reference
	Node<T>* x = NULL; // to be predecessor's child
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
				break; // item has been found, exit while loop	
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

	if (node->left == NULL || node->right == NULL) // checking if node has at most 1 child
		y = node;
	else
		y = Predecessor(node);

	if (y->left != NULL) // get a reference to the predecessor's child
		x = y->left;
	else if (y->right != NULL)
		x = y->right;

	if (x != NULL && y->p != NULL) // predecessor's child to link with predecessor's parent
		x->p = y->p;


	if (y->p == NULL) // if predecessor is the root; only happens if node has at most 1 child
		root = x;
	else
	{
		// predecessor's parent must re link left or right pointers to predecessor's child
		yparent = y->p;
		if (y == yparent->left)
			yparent->left = x;
		else
			yparent->right = x;
	}

	if (node != y)
		node->data = y->data; // if y was a predecessor

	if (y->is_black == true) // is y black?
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
			y = xparent->right; // sibling of x

			if (y->is_black == false) // case1; y is red
			{
				y->is_black = true;
				xparent->is_black = false; // x's parent must be black since y is red
				LeftRotate(xparent);
				y = xparent->right;
			}

			if ((y->left == NULL || (y->left)->is_black == true) && (y->right == NULL || (y->right)->is_black == true)) // case2; both y's childs are black
			{
				// this block of code will push the fix up the tree
				y->is_black = false;
				x = xparent;

				////////////////////////
				if (x->p != NULL)
				{
					xparent = x->p;
					if (x == xparent->left)
						xisleftchild = true;
					else
						xisleftchild = false;
				}
				////////////////////////
			}
			else
			{
				if (y->right == NULL || (y->right)->is_black == true)
				{
					// we want to make x's sibling right child red

					(y->left)->is_black = true;
					y->is_black = false;
					RightRotate(y);
					y = xparent->right; // (3 nodes in a line)
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
		else // symmetric case
		{
			y = xparent->left;
			if (y->is_black == false) // case1; y is red
			{
				y->is_black = true;
				xparent->is_black = false; // x's parent must be black since y is red
				RightRotate(xparent);
				y = xparent->left;
			}

			if ((y->left == NULL || (y->left)->is_black == true) && (y->right == NULL || (y->right)->is_black == true)) // case2; both y's childs are black
			{
				// this block of code will push the fix up the tree
				y->is_black = false;
				x = xparent;

				////////////////////////
				if (x->p != NULL)
				{
					xparent = x->p;
					if (x == xparent->left)
						xisleftchild = true;
					else
						xisleftchild = false;
				}
				////////////////////////
			}
			else
			{
				if (y->left == NULL || (y->left)->is_black == true)
				{
					// we want to make x's sibling left child red

					(y->right)->is_black = true;
					y->is_black = false;
					LeftRotate(y);
					y = xparent->left; // (3 nodes in a line)
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
	// Traversal order as follows (post order)
	// Left
	// Right
	// Calculate height
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
#ifdef _REDBLACKTREE_H_
#include<stdexcept>

#include <iostream>
#include <math.h>
//W
//private

// recursive helper function for deep copy
// creates a new node "thisnode" based on sourcenode's contents, links back to parentnode,
//   and recurses to create left and right children
template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode)
{
	if(sourcenode != NULL)
	{
		if(thisnode == NULL)
		{
			thisnode = new Node<T>();
		}
		thisnode->data = sourcenode->data; //creates a new node
		thisnode->is_black = sourcenode->is_black; //sets node's color

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


// recursive helper function for tree deletion
// deallocates nodes in post-order
template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	//Postorder traversal
	if(node != NULL)
	{
		RemoveAll(node->left);
		RemoveAll(node->right);	
		delete node;
		size--;
	}
}
// hard!
// Tree fix, performed after removal of a black node
// Note that the parameter x may be NULL
template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	bool isBlack = false; //go into while loop with x = NULL
	Node<T>* w = NULL;
	if (x == NULL || x->is_black) //null = black node
	{
		isBlack = true;
	}

	while (x != root && isBlack)
	{
		if (xisleftchild)//x is leftchild
		{
			w = xparent->right; //w = x's sibling
			if (!w->is_black)
			{
				w->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent); //rotate around x's parent
				w = xparent->right;
			}
			if ((w->left == NULL || w->left->is_black) && (w->right == NULL || w->right->is_black)) //performing on NULL crashes
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
		else //swap left and right
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
	if (x != NULL) //performing is_black on NULL errors
	{
		x->is_black = true;
	}
}

// Calculates the height of the tree
// Requires a traversal of the tree, O(n)
template <class T>
unsigned int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
	if(node == NULL) //empty so height of 0
	{
		return 0;
	}
	else
	{
		unsigned int tempLeft = 0; //count the left children
		unsigned int tempRight = 0; //count the right children

		if(node->left != NULL)
		{
			unsigned int tempLeft = CalculateHeight(node->left);
		}
		if(node->right != NULL)
		{
			unsigned int tempRight = CalculateHeight(node->right);
		}

		if(tempLeft > tempRight) //compares which one is more
		{
			return tempLeft + 1;
		}
		else
		{
			return tempRight + 1;
		}
	}

}

//public

// default constructor
template <class T>
RedBlackTree<T>::RedBlackTree()
{
	size = 0;
	root = NULL;
}

// copy constructor, performs deep copy of parameter
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
	root = new Node<T>(root->data); 
	CopyTree(root, rbtree.GetRoot(), NULL);	
}

// destructor
// Must deallocate memory associated with all nodes in tree
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll();
}

// overloaded assignment operator
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

// Accessor functions

// Calls BSTInsert and then performs any necessary tree fixing.
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
template <class T>
bool RedBlackTree<T>::Insert(T item)
{
	//performs if item is not found in tree
	if(Search(item) == false)  
	{
		Node<T>* x = BSTInsert(item);  //calls BSTinsert and sets to x
		Node<T>* y = NULL;
		x->is_black = false;  //defaults to black node
		while(x->p != NULL && x->p->is_black == false) //iterates until root or black parent reached
		{
			if(x->p == x->p->p->left)
			{
				y = x->p->p->right; //uncle of x
				if(y != NULL && y->is_black == false) //NULL means black 
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
			else //x->p == x->p->p->right
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
		size++; //increment size by 1
		return true;
	}
	return false;
}

// Removal of an item from the tree.
// Must deallocate deleted node after RBDeleteFixUp returns
template <class T>
bool RedBlackTree<T>::Remove(T item)
{
	if(Search(item) == false) //returns false if Search does not find item
	{
		return false;
	}

	Node<T>* z = root;

	while (z != NULL) //binary search through tree for item
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
		y = z; //y is the node to be removed
	}
	else
	{
		y = Predecessor(z); //sets y to predecessor
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

	if (y->p == NULL) //x is root
	{
		root = x;
	}
	else if (y == y->p->left) //y is predecessor
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

	delete y; //DELETE Y AFTER
	size--; //decrement
	z = NULL;
	return true;
}

// deletes all nodes in the tree. Calls recursive helper function.
template <class T>
void RedBlackTree<T>::RemoveAll()
{
	RemoveAll(root);
	root = NULL;
}

// returns the number of items in the tree
template <class T>
unsigned int RedBlackTree<T>::Size() const
{
	return size;
}

// returns the height of the tree, from root to deepest null child. Calls recursive helper function.
// Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
template <class T>
unsigned int RedBlackTree<T>::Height() const
{
	return CalculateHeight(root);
}


#endif
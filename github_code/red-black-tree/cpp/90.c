// File:        stocksystem.cpp
// Author:      BeiBei Li, Zisu Geng
// Description: implementation part of the functions in redblacktree.h 

#ifdef _REDBLACKTREE_H_


// private recursive helper function for deep copy,creates a new node "thisnode" based on sourcenode's contents, links back to parentnode,
// pre:copy start position should be null pointer,otherwise may cause memory leak
// parmeter: copy start position(),copy origin start position, copy origin's parent
// post:copy finished, return the start copying position
template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode)
{

	if (sourcenode != NULL) 
	{
		thisnode = new Node<T>(sourcenode->data);
		//copying
		thisnode->p = parentnode;
		thisnode->is_black = sourcenode->is_black;
		//going left
		thisnode->left = CopyTree(thisnode->left, sourcenode->left, thisnode);
		//going right
		thisnode->right = CopyTree(thisnode->right, sourcenode->right, thisnode);
		return thisnode;
	}
	return NULL;

}

// recursive helper function for tree deletion
//pre:
//parameter:a delete start position
//post:deallocates nodes in post-order
template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	if (node != NULL) 
	{
		RemoveAll(node->left);
		RemoveAll(node->right);
		delete node;
		node = NULL;
	}

}



// Tree fix, performed after removal of a black node
// Note that the parameter x may be NULL
template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	// The case x==NULL is regarded as x is a black node
	while (x != root && (x==NULL || x->is_black ))
	{
		if (xisleftchild) 
		{
			//y is the sibling of x,this could be null,so need to pay attention
			Node<T>* y = xparent->right; 
			if (y!=NULL && !y->is_black) 
			{
				y->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent);
				y = xparent->right;
			}
			// The case y.left==NULL and y.right=NULL are regarded as y.left and y.right are black nodes
			if ( y!=NULL && (y->left ==NULL || y->left->is_black) && (y->right==NULL || y->right->is_black) )
			{
				y->is_black = false;
				x = xparent;
				//to loop back,x can not be null pointer here,so can access x->p
				if(x->p==NULL)
				{
					x=root;
				}
				else
				{
					xparent=x->p;
					if(x==xparent->left) 
					{
                        xisleftchild = true;
					}
                    else
					{
                        xisleftchild = false; 
					}
                }
			}
			else {
				if (y!=NULL && y->right!=NULL && y->left!=NULL && y->right->is_black) 
				{
					y->left->is_black = true;
					y->is_black = false;
					RightRotate(y);
					y = xparent->right;
				}
				if(y!=NULL)
				{
					y->is_black = xparent->is_black;
				}
				xparent->is_black = true;
				if(y!=NULL && y->right!=NULL)
				{
					y->right->is_black = true;
				}
				LeftRotate(xparent);
				// all done, so has to break the while loop
				x = root;
			}
		}
		
		else 
		{
			//y is the sibling of x,this could be null,so need to pay attention
			Node<T>* y = xparent->left; 
			if (y!=NULL && !y->is_black) 
			{
				y->is_black = true;
				xparent->is_black = false;
				RightRotate(xparent);
				y = xparent->left;
			}
			// The cases y.left==NULL and y.right=NULL is regarded as y.left and y.right are a black nodes
			if ( y!=NULL && (y->left ==NULL || y->left->is_black) && (y->right==NULL || y->right->is_black) )
			{
				y->is_black = false;
				x = xparent;
				//to loop back,x can not be null pointer here,so can access x->p
				if(x->p==NULL)
				{
					x=root;
				}
				else
				{
					xparent=x->p;
					if(x==xparent->left) 
					{
                        xisleftchild = true;
					}
                    else
					{
                        xisleftchild = false; 
					}
                }
			}
			else 
			{
				if (y!=NULL && y->left!=NULL && y->right!=NULL && y->left->is_black) 
				{
					y->right->is_black = true;
					y->is_black = false;
					LeftRotate(y);
					y = xparent->left;
				}
				if(y!=NULL)
				{
					y->is_black = xparent->is_black;
				}
				xparent->is_black = true;
				if(y!=NULL && y->left!=NULL)
				{
					y->left->is_black = true;
				}
				RightRotate(xparent);
				// all done, so has to break the while loop
				x = root;
			}
		}
		
	}
	if(x!=NULL)
	{
		x->is_black=true;
	}
}

// Calculates the height of the tree
// Requires a traversal of the tree, O(n)
template <class T>
unsigned int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
	if (node == NULL) 
	{
		return 0;
	}
	int lefthight = CalculateHeight(node->left);
	int righthight = CalculateHeight(node->right);
	if (lefthight > righthight) 
	{
		return lefthight + 1;
	}
	else 
	{
		return righthight + 1;
	}
}

//default constructor
template <class T>
RedBlackTree<T>::RedBlackTree()
{
    size = 0;
    root = NULL;
}

//copy constructor
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
        root=NULL;
        root=CopyTree(root, rbtree.root, NULL);
        size = rbtree.size;
}

//destructor
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
    RemoveAll();
}

template <class T>
RedBlackTree<T> & RedBlackTree<T>::operator=(const RedBlackTree<T> & rbtree)
{
    if (this != &rbtree) 
	{
        RemoveAll();
        root=CopyTree(root, rbtree.root, NULL);
		size=rbtree.size;
    }
    return *this;
}












// Calls BSTInsert and then performs any necessary tree fixing.
template <class T>
bool RedBlackTree<T>::Insert(T item)
{
	// If item already exists, do not insert and return false.
	if (Search(item)) 
	{
		return false;
	}

	// Otherwise, Call BSTInsert, increment size,then performs any necessary tree fixing,then return true.
	Node<T>* x = BSTInsert(item);
	if (x != NULL) 
	{
		size++;
	}
	else
	{
		return false;
	}
	x->is_black = false;

	//Iterates until root or a black parent is reached
	while (x != root && !x->p->is_black ) 
	{
		//if x'parent is a left child
		if (x->p == x->p->p->left) 
		{
			Node<T>* y = x->p->p->right;
			//if x'parent and uncle are both red
			if (y!=NULL && !y->is_black ) 
			{
				//Colour parent & uncle black;Colour grandparent red;Set x to grandparent
				x->p->is_black = true;
				y->is_black = true;
				x->p->p->is_black = false;
				x = x->p->p;
			}
			//if x'parent is red and uncle is black(uncle is black || uncle is NULL)
			else {
				//x is a right child, that means, x,parent,grand parent not in a line
				if (x == x->p->right) 
				{
					x = x->p;
					LeftRotate(x);
				}
				//otherwise x is a left child(they are in line already)
				x->p->is_black = true;
				x->p->p->is_black = false;
				RightRotate(x->p->p);
			}
		}
		//if x'parent is a right child
		else 
		{
			Node<T>* y = x->p->p->left;
			//if x'parent and uncle are both red
			if (y!=NULL && !y->is_black ) 
			{
				//Colour parent & uncle black;Colour grandparent red;Set x to grandparent
				x->p->is_black = true;
				y->is_black = true;
				x->p->p->is_black = false;
				x = x->p->p;
			}
			//if x'parent is red and uncle is black(uncle is black || uncle is NULL)
			else 
			{
				//x is a left child, that means, x,parent,grand parent not in a line
				if (x == x->p->left) 
				{
					x = x->p;
					RightRotate(x);
				}
				//otherwise x is a right child(they are in line already)
				x->p->is_black = true;
				x->p->p->is_black = false;
				LeftRotate(x->p->p);
			}
		}
	}
	root->is_black = true;
	return true;
}

// Removal of an item from the tree.
template <class T>
bool RedBlackTree<T>::Remove(T item)
{
	if (Search(item) == false) 
	{
		return false;
	}
	size--;

	Node<T>* z= root; 
	while (z != NULL)
	{
		if (item == z->data) 
		{
			break;
		}
		else if (item < z->data)
		{
			z = z->left;
		}
		else 
		{
			z = z->right;
		}
	}


	Node<T>* y;//y is the node to be romoved
	if (z->left != NULL && z->right != NULL) 
	{
		y = Predecessor(z);
	}
	else 
	{
		y=z;
	}

	Node<T>* x;
	if (y->left != NULL) 
	{
		x = y->left;
	}
	else 
	{
		x = y->right;
	}

	if(x!=NULL)
	{
		x->p = y->p;
	}

	if (y->p == NULL) 
	{
		root = x;
	}
	else 
	{
		if (y == y->p->left) 
		{
			y->p->left = x;
		}
		else 
		{
			y->p->right = x;
		}
	}
	if (y != z) 
	{
		z->data = y->data;
	}
	if (y->is_black) 
	{
		if(y->p!=NULL)
		{
			if(x == y->p->left) 
				RBDeleteFixUp(x, y->p, true);
			else
				RBDeleteFixUp(x, y->p, false);
		}
	}

	delete y;

	return true;
}






// deletes all nodes in the tree. Calls recursive helper function.
template <class T>
void RedBlackTree<T>::RemoveAll()
{
	if(root!=NULL)
	{
		RemoveAll(root);
	}
	size = 0;
	root=NULL;
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
	unsigned int result = CalculateHeight(root);
	return result;
}

#endif

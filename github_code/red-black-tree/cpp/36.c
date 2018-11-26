#ifdef _REDBLACKTREE_H_


// recursive helper function for deep copy
// creates a new node "thisnode" based on sourcenode's contents, links back to parentnode,
//   and recurses to create left and right children
template <class T>
Node<T>* RedBlackTree<T>::CopyTree( Node<T>* sourcenode, Node<T>* parentnode)
{
	Node<T>*thisnode;
	thisnode=new Node<T>(sourcenode->data);
	thisnode->p=parentnode;
	thisnode->is_black=sourcenode->is_black;
	if(sourcenode->left!=NULL)
	{
		thisnode=this->CopyTree(sourcenode->left,thisnode);
	}
	if(sourcenode->right!=NULL)
	{
		thisnode=this->CopyTree(sourcenode->right,thisnode);
	}
	return thisnode;
}

// recursive helper function for tree deletion
// deallocates nodes in post-order
template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
	if(node!=NULL)
	{
		RemoveAll(node->left);
		RemoveAll(node->right);
		delete node;
	}
	root=NULL;
	size=0;
}


// Tree fix, performed after removal of a black node
// Note that the parameter x may be NULL
template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	//when x is not a root and it is black
	Node<T>* y;
	while (x != root && (x == NULL || x->is_black == true))
	{
		//if x is a left node
		if (xisleftchild == true)
		{
			//y is the right node(sibling)
			y = xparent->right;
			//if y is red
			if (y->is_black == false && y != NULL)
			{
				y->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent);
				y = xparent->right;
			}
			//both y's children are black
			if ((y->left->is_black == true || y->left == NULL) && (y->right->is_black == true || y->right == NULL)) 
			{
				y->is_black = false;
				x = xparent;
				xparent = xparent->p;
				if(xparent->left==x)
				{
					xisleftchild=true;
				}
				else
				{
					xisleftchild=false;
				}
			}

			else {
				// y's red child not in line with x's parent
				if (y->right == NULL || y->right->is_black == true) {
					y->left->is_black = true;
					y->is_black = false;
					RightRotate(y);
					y = xparent->right;
				}
				y->is_black = xparent->is_black;
				xparent->is_black = true;
				y->right->is_black = true;
				LeftRotate(xparent);
				x = root;
			}
		}
		else {//symmetric to if: x is rightchild
			y = xparent->left;
			if (y->is_black == false) {
				y->is_black = true;
				xparent->is_black = false;
				RightRotate(xparent);
				y = xparent->left;
			}
			if ((y->left == NULL || y->left->is_black == true) && (y->right == NULL || y->right->is_black == true)) {
				y->is_black = false;
				x = xparent;
				xparent = xparent->p;
				if(xparent->left==x)
				{
					xisleftchild=true;
				}
				else
				{
					xisleftchild=false;
				}
			}
			else {
				if (y->left == NULL || y->left->is_black == true) 
				{
					y->right->is_black = true;
					y->is_black = false;
					LeftRotate(y);
					y = xparent->left;
				}
				y->is_black = xparent->is_black;
				xparent->is_black = true;
				y->left->is_black = true;
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
	if (node==NULL)
	{
		return 0;
	}
	else if(node->left==NULL&&node->right==NULL)
	{
		return 1;
	}
	else if(node->left==NULL&&node->right!=NULL)
	{
		return 1+CalculateHeight(node->right);
	}
	else if(node->left!=NULL&&node->right==NULL)
	{
		return 1+CalculateHeight(node->left);
	}
	else if(CalculateHeight(node->left)>CalculateHeight(node->right))
	{
		return 1+CalculateHeight(node->left);
	}
	else
	{
		return 1+CalculateHeight(node->right);
	}


}


// default constructor
template <class T>
RedBlackTree<T>::RedBlackTree()
{
	root=NULL;
	size=0;
}

// copy constructor, performs deep copy of parameter
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
	size=rbtree.size;
	root=CopyTree(rbtree.root,NULL);
	
}

// destructor
// Must deallocate memory associated with all nodes in tree
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll(root);
}

// overloaded assignment operator
template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
{
	if(this->root!=rbtree.root&&this->size!=rbtree.size)
	{
		RemoveAll(this->root);
		this->root=CopyTree(rbtree.root,NULL);
		this->size=rbtree.size;
	}
	return *this;
}

// Accessor functions

// Calls BSTInsert and then performs any necessary tree fixing.
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
template <class T>
bool RedBlackTree<T>::Insert(T item) {
	//check if item exists
	if (Search(item) == true) 
	{
		return false;
	}
	Node<T>* x = BSTInsert(item);
	if (x==NULL)
	{
		return false;
	}
	else
	{
	    size++;
	}
	x->is_black = false;

	while (x != root && x->p->is_black==false ) 
	{
		//x is left child and y is uncle
		if (x->p == x->p->p->left) {
			Node<T>* y = x->p->p->right;
			//uncle and parent both red y could be null
			if (y!=NULL && y->is_black==false )
			{
				x->p->is_black = true;
				y->is_black = true;
				x->p->p->is_black = false;
				x = x->p->p;
			}
			else 
			{
				if (x == x->p->right) 
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
		{ //x.p ==x.p.p.right
			Node<T>* y = x->p->p->left;
			if ( y != NULL && y->is_black==false) {
				x->p->is_black = true;
				y->is_black = true;
				x->p->p->is_black = false;
				x = x->p->p;
			}

			
			
			else 
			{
				if (x == x->p->left) {
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
	return true;
}

// Removal of an item from the tree.
// Must deallocate deleted node after RBDeleteFixUp returns
template <class T>
bool RedBlackTree<T>::Remove(T item) {
	Node<T>* node = root;
	if (Search(item) == false) 
	{
		return false;
	}
	//iteratively search for the item and point it with *node
	while (node != NULL)
	{
		if (item == node->data)
			break;					//when the item is found
		else if (item < node->data)
			node = node->left;
		else
			node = node->right;
	}
	//when there's an empty tree or item to be remove is not found
	if(node == NULL)
		return false;

	Node<T>* x;
	Node<T>* y;
	//if item has at most one child
	if(node->left == NULL || node->right == NULL)
	{
		y = node;
	}
	//when predecessor exists (having 2 children)
	else
	{
		y = Predecessor(node);
	}

	//set x to be the child/subtree of y
	if(y->left != NULL)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}
	//if y is the root, just replace it by x
	if(y->p == NULL)
	{
		root = x;
	}
	//otherwise, set x to be child of y's parent
	else
	{
		//check to see if x isright or isleft
		if(y == y->p->left)
			y->p->left = x;
		if(y == y->p->right)
			y->p->right = x;
		//attach x to y's parent
		if(x != NULL){
			x->p = y->p;
		}
	}
	//if y is the predecessor, replace the item node with y
	if(y !=node)
	{
		node->data = y->data;
	}
	
	//if y is red, nothing is needed(amount of black does not change)
	//if y is black, fixup needed
	if(y->is_black  == true)
	{
		if(x == y->p->right)
		{
			RBDeleteFixUp(x,y->p,false);	//here using y->p instead of x->p since x might be NULL
		}
		else 
		{
			RBDeleteFixUp(x,y->p,true);
		}
	}
	//deallocate the node
	delete y;
	size--;
	return true;
}


// deletes all nodes in the tree. Calls recursive helper function.
template <class T>
void RedBlackTree<T>::RemoveAll()
{
	RemoveAll(root);
}



// returns the number of items in the tree
template <class T>
 int RedBlackTree<T>::Size() const
{
	return size;
}

// returns the height of the tree, from root to deepest null child. Calls recursive helper function.
// Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
template <class T>
int RedBlackTree<T>::Height() const
{
	return this->CalculateHeight(root);
}





#endif




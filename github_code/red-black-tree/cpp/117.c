
#ifdef _REDBLACKTREE_H_



// recursive helper function for deep copy
// creates a new node based on sourcenode's contents, links back to parentnode,
//   and recurses to create left and right children
template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode) {
	Node<T>* copynode;
	if (sourcenode != NULL) {
		copynode = new Node<T>(sourcenode->data);
		copynode->p = parentnode;
		copynode->is_black = sourcenode->is_black;
		//left and right
		copynode->left = CopyTree(sourcenode->left, copynode);
		copynode->right = CopyTree(sourcenode->right, copynode);
		return copynode;
	}
	//return NULL if sourcenode == NULL
	return NULL;
}

// recursive helper function for tree deletion
// deallocates nodes in post-order
template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node) {
	//post order left right self
	if (node != NULL) {
		RemoveAll(node->left);
		RemoveAll(node->right);
		//deallocate
		delete node;
	}
	//reassign NULL pointer
	root = NULL;
	size = 0;
}

// Tree fix, performed after removal of a black node
// Note that the parameter x may be NULL
template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild) {
	Node<T>* y;
	//x == NULL is imaginary node(treated as black too) x.is_black is black node
	while (x != root && (x == NULL || x->is_black == true)) {
		//x is leftchild -->if (x == x.p.left)
		if (xisleftchild == true)
		{
			y = xparent->right;
			//uncle y is red
			if (y->is_black == false && y != NULL) {
				y->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent);
				y = xparent->right;
			}
			//both y's children are black
			if ((y->left->is_black == true || y->left == NULL) && (y->right->is_black == true || y->right == NULL)) {
				//make y red
				y->is_black = false;
				x = xparent;
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
				//??
			}
			else {
				if (y->left == NULL || y->left->is_black == true) {
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
int RedBlackTree<T>::CalculateHeight(Node<T>* node) const {
	if (node == NULL) {
		return 0;
	}
	else if (node->left == NULL&&node->right == NULL) {
		return 1;
	}
	else if (node->left != NULL && node->right == NULL) {
		return 1 + CalculateHeight(node->left);
	}
	else if (node->left == NULL && node->right != NULL) {
		return 1 + CalculateHeight(node->right);
	}
	if (CalculateHeight(node->left) > CalculateHeight(node->right)) {
		return 1 + CalculateHeight(node->left);
	}
	else {
		return 1 + CalculateHeight(node->right);
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

	root = CopyTree(rbtree.root, NULL);
	size = rbtree.size;
}

//destructor
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll(root);
}

template <class T>
RedBlackTree<T> & RedBlackTree<T>::operator=(const RedBlackTree<T> & rbtree)
{
	if (this != &rbtree)
	{
		RemoveAll();
		this->root = CopyTree(rbtree.root, NULL);
		this->size = rbtree.size;
	}
	return *this;
}

// Accessor functions

// Calls BSTInsert and then performs any necessary tree fixing.
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
template <class T>
bool RedBlackTree<T>::Insert(T item) {
	//item already exist
	if (Search(item) == true) {
		return false;
	}
	Node<T>* x = BSTInsert(item);
	if (x == NULL) {
		return false;
	}

	size++;

	x->is_black = false;

	while (x != root && !x->p->is_black)
	{
		//y is uncle x is left child
		if (x->p == x->p->p->left) {
			Node<T>* y = x->p->p->right;
			//uncle and parent both red y could be null?
			if (y != NULL && !y->is_black) {
				//grand[arent turn to red;uncle and parent turn to black
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
		else { //x.p ==x.p.p.right
			Node<T>* y = x->p->p->left;
			if (y != NULL && !y->is_black) {
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
	//if item not found return false
	if (Search(item) == false) {
		return false;
	}
	//Find the node z that has the value item 
	Node<T>*z = root;
	while (z != NULL) {
		if (item == z->data) {
			break;
		}
		else if (item < z->data) {
			z = z->left;
		}
		else {
			z = z->right;
		}
	}
	//item has at most one child
	Node<T>* y;
	Node<T>* x;
	if (z->left == NULL || z->right == NULL) {
		y = z;
	}
	else {
		y = Predecessor(z);
	}
	if (y->left != NULL) {
		x = y->left;
	}
	else {
		x = y->right;
	}
	//x->p = y->p; cant do this because x could be NULL
	//check if y is root, replace it by x
	if (y->p == NULL) {
		root = x;
	}
	else {
		if (y == y->p->left) {
			y->p->left = x;
		}
		else {
			y->p->right = x;
		}
		//need to check x is not null ptr
		if (x != NULL) {
			x->p = y->p;
		}
	}
	if (y != z) {
		z->data = y->data;
	}
	if (y->is_black == true) {

		if (x == y->p->left) {
			RBDeleteFixUp(x, y->p, true);
		}
		//x is rightchold
		else {
			RBDeleteFixUp(x, y->p, false);
		}
	}
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

// Returns existence of item in the tree.
// Return true if found, false otherwise.

// returns the number of items in the tree
template <class T>
int RedBlackTree<T>::Size() const {
	return size;
}

// returns the height of the tree, from root to deepest null child. Calls recursive helper function.
// Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
template <class T>
int RedBlackTree<T>::Height() const {
	//only want the int part eg. >2 log3 >1 use 1
	return CalculateHeight(root);
}




#endif


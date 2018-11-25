
#ifdef _REDBLACKTREE_H_






template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode) {
	Node<T>* copynode;
	if (sourcenode != NULL) {
		copynode = new Node<T>(sourcenode->data);
		copynode->p = parentnode;
		copynode->is_black = sourcenode->is_black;
		
		copynode->left = CopyTree(sourcenode->left, copynode);
		copynode->right = CopyTree(sourcenode->right, copynode);
		return copynode;
	}
	
	return NULL;
}



template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node) {
	
	if (node != NULL) {
		RemoveAll(node->left);
		RemoveAll(node->right);
		
		delete node;
	}
	
	root = NULL;
	size = 0;
}



template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild) {
	Node<T>* y;
	
	while (x != root && (x == NULL || x->is_black == true)) {
		
		if (xisleftchild == true)
		{
			y = xparent->right;
			
			if (y->is_black == false && y != NULL) {
				y->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent);
				y = xparent->right;
			}
			
			if ((y->left->is_black == true || y->left == NULL) && (y->right->is_black == true || y->right == NULL)) {
				
				y->is_black = false;
				x = xparent;
			}

			else {
				
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
		else {
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


template <class T>
RedBlackTree<T>::RedBlackTree()
{
	size = 0;
	root = NULL;
}


template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{

	root = CopyTree(rbtree.root, NULL);
	size = rbtree.size;
}


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






template <class T>
bool RedBlackTree<T>::Insert(T item) {
	
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
		
		if (x->p == x->p->p->left) {
			Node<T>* y = x->p->p->right;
			
			if (y != NULL && !y->is_black) {
				
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
		else { 
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



template <class T>
bool RedBlackTree<T>::Remove(T item) {
	
	if (Search(item) == false) {
		return false;
	}
	
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
		
		else {
			RBDeleteFixUp(x, y->p, false);
		}
	}
	delete y;
	size--;
	return true;
}



template <class T>
void RedBlackTree<T>::RemoveAll()
{
	RemoveAll(root);
}





template <class T>
int RedBlackTree<T>::Size() const {
	return size;
}



template <class T>
int RedBlackTree<T>::Height() const {
	
	return CalculateHeight(root);
}




#endif


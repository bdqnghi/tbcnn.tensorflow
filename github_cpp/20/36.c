#ifdef _REDBLACKTREE_H_





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




template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	
	Node<T>* y;
	while (x != root && (x == NULL || x->is_black == true))
	{
		
		if (xisleftchild == true)
		{
			
			y = xparent->right;
			
			if (y->is_black == false && y != NULL)
			{
				y->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent);
				y = xparent->right;
			}
			
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



template <class T>
RedBlackTree<T>::RedBlackTree()
{
	root=NULL;
	size=0;
}


template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
	size=rbtree.size;
	root=CopyTree(rbtree.root,NULL);
	
}



template <class T>
RedBlackTree<T>::~RedBlackTree()
{
	RemoveAll(root);
}


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






template <class T>
bool RedBlackTree<T>::Insert(T item) {
	
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
		
		if (x->p == x->p->p->left) {
			Node<T>* y = x->p->p->right;
			
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
		{ 
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



template <class T>
bool RedBlackTree<T>::Remove(T item) {
	Node<T>* node = root;
	if (Search(item) == false) 
	{
		return false;
	}
	
	while (node != NULL)
	{
		if (item == node->data)
			break;					
		else if (item < node->data)
			node = node->left;
		else
			node = node->right;
	}
	
	if(node == NULL)
		return false;

	Node<T>* x;
	Node<T>* y;
	
	if(node->left == NULL || node->right == NULL)
	{
		y = node;
	}
	
	else
	{
		y = Predecessor(node);
	}

	
	if(y->left != NULL)
	{
		x = y->left;
	}
	else
	{
		x = y->right;
	}
	
	if(y->p == NULL)
	{
		root = x;
	}
	
	else
	{
		
		if(y == y->p->left)
			y->p->left = x;
		if(y == y->p->right)
			y->p->right = x;
		
		if(x != NULL){
			x->p = y->p;
		}
	}
	
	if(y !=node)
	{
		node->data = y->data;
	}
	
	
	
	if(y->is_black  == true)
	{
		if(x == y->p->right)
		{
			RBDeleteFixUp(x,y->p,false);	
		}
		else 
		{
			RBDeleteFixUp(x,y->p,true);
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
 int RedBlackTree<T>::Size() const
{
	return size;
}



template <class T>
int RedBlackTree<T>::Height() const
{
	return this->CalculateHeight(root);
}





#endif




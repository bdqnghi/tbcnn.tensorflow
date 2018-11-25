



#ifdef _REDBLACKTREE_H_






template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode)
{

	if (sourcenode != NULL) 
	{
		thisnode = new Node<T>(sourcenode->data);
		
		thisnode->p = parentnode;
		thisnode->is_black = sourcenode->is_black;
		
		thisnode->left = CopyTree(thisnode->left, sourcenode->left, thisnode);
		
		thisnode->right = CopyTree(thisnode->right, sourcenode->right, thisnode);
		return thisnode;
	}
	return NULL;

}





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





template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
	
	while (x != root && (x==NULL || x->is_black ))
	{
		if (xisleftchild) 
		{
			
			Node<T>* y = xparent->right; 
			if (y!=NULL && !y->is_black) 
			{
				y->is_black = true;
				xparent->is_black = false;
				LeftRotate(xparent);
				y = xparent->right;
			}
			
			if ( y!=NULL && (y->left ==NULL || y->left->is_black) && (y->right==NULL || y->right->is_black) )
			{
				y->is_black = false;
				x = xparent;
				
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
				
				x = root;
			}
		}
		
		else 
		{
			
			Node<T>* y = xparent->left; 
			if (y!=NULL && !y->is_black) 
			{
				y->is_black = true;
				xparent->is_black = false;
				RightRotate(xparent);
				y = xparent->left;
			}
			
			if ( y!=NULL && (y->left ==NULL || y->left->is_black) && (y->right==NULL || y->right->is_black) )
			{
				y->is_black = false;
				x = xparent;
				
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
				
				x = root;
			}
		}
		
	}
	if(x!=NULL)
	{
		x->is_black=true;
	}
}



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


template <class T>
RedBlackTree<T>::RedBlackTree()
{
    size = 0;
    root = NULL;
}


template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
        root=NULL;
        root=CopyTree(root, rbtree.root, NULL);
        size = rbtree.size;
}


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













template <class T>
bool RedBlackTree<T>::Insert(T item)
{
	
	if (Search(item)) 
	{
		return false;
	}

	
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

	
	while (x != root && !x->p->is_black ) 
	{
		
		if (x->p == x->p->p->left) 
		{
			Node<T>* y = x->p->p->right;
			
			if (y!=NULL && !y->is_black ) 
			{
				
				x->p->is_black = true;
				y->is_black = true;
				x->p->p->is_black = false;
				x = x->p->p;
			}
			
			else {
				
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
			
			if (y!=NULL && !y->is_black ) 
			{
				
				x->p->is_black = true;
				y->is_black = true;
				x->p->p->is_black = false;
				x = x->p->p;
			}
			
			else 
			{
				
				if (x == x->p->left) 
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
	return true;
}


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


	Node<T>* y;
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


template <class T>
unsigned int RedBlackTree<T>::Size() const
{
	return size;
}



template <class T>
unsigned int RedBlackTree<T>::Height() const
{
	unsigned int result = CalculateHeight(root);
	return result;
}

#endif

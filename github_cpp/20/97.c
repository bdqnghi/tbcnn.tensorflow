




#ifdef _REDBLACKTREE_H_



    
    
    

    template<class T>
    Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode)
    {
			if(sourcenode==NULL)
			{
				return NULL;
			}
			
			Node<T>* thisnode=new Node<T>(sourcenode->data);

			thisnode->p=parentnode;
            
            
			thisnode->is_black=sourcenode->is_black;

			thisnode->left=CopyTree( sourcenode->left,thisnode);

            thisnode->right=CopyTree( sourcenode->right,thisnode);

        return thisnode;

    }

    
    
    template<class T>
    void RedBlackTree<T>::RemoveAll(Node<T>* node)
    {
			if(node!=NULL)
			{
            RemoveAll(node->left);
            RemoveAll(node->right);
			
			node->left=NULL;
			node->right=NULL;
			node->p=NULL;
			
			node=NULL;
			delete node;
			size--;   
			}
    }


    
    
    template<class T>
    void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
    {
        Node<T>* y;
        while(x != root && ( x==NULL || x->is_black == true))
        {
           if(xparent->left!=x){
			   xisleftchild=false;}
		   else{
			   xisleftchild=true;}
			
			if(xisleftchild)
            {
                y=xparent->right;
                if(y->is_black == false)
                {
                    y->is_black = true;
                    
                    xparent->is_black = false;
                    LeftRotate(xparent);
                    y=xparent->right;
                }
				if((y->left==NULL|| y->left->is_black == true) && (y->right==NULL || y->right->is_black == true))
                {
                    y->is_black = false;
					x = xparent; 
                }
                else
                {
                    if(y->right->is_black == true)
                    {
                        y->left->is_black= true;
                        y->is_black= false;
                        RightRotate(y);
                        y = xparent->right;
                    }
                        
                    y->is_black=xparent->is_black;
                    xparent->is_black= true;
                    y->right->is_black=true;
                    LeftRotate(xparent);
                    x=root;
					return;
                }
            }
            
            else
            {
                y=xparent->left;
                if(y->is_black == false)
                {
                    y->is_black = true;
                    
                    xparent->is_black = false;
                    RightRotate(xparent);
                    y=xparent->left;
                }
				if((y->right==NULL || y->right->is_black == true) && (y->left==NULL || y->left->is_black == true))
                {
                    y->is_black = false;
                    x=xparent;
                }
                else
                {
					if(y->left==NULL || y->left->is_black == true)
                    {
                        y->right->is_black= true;
                        y->is_black=false;
                        LeftRotate(y);
                        y=xparent->left;
                    }
                    y->is_black=xparent->is_black;
                    xparent->is_black=true;
                    y->left->is_black=true;
                    RightRotate(xparent);
                    x=root;
					return;
                }
				
            }
			

        } 
		if(x==root && x==NULL)
		{
			return;
		}
		else
		{
			x->is_black=true;
		}
    }

    
    
    
    template<class T>
    int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
    {
        if(node==NULL)
        {
            return 0;
        }
        else
        {
            int left_height = CalculateHeight(node->left);
            int right_height = CalculateHeight(node->right);
            return(left_height > right_height) ? left_height + 1 : right_height +1;
        }
    }

    
    template<class T>
    RedBlackTree<T>::RedBlackTree()
    {
           root = NULL;
           size=0;
    }

    
    template<class T>
    RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
    {
        if(rbtree.root!=NULL)
        {
            root=NULL;
			size=0;
			root=CopyTree(rbtree.root, NULL);
            size=rbtree.size;
        }
        else
        {
            root=NULL;
            size=0;
        }

    }

    
    
    template<class T>
    RedBlackTree<T>::~RedBlackTree()
    {
        RemoveAll();
		root=NULL;
		size=0;
    }

    
    template<class T>
    RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
    {
        	
        if(this != &rbtree)
        {
            
            
            if(size!=0)
            {

                this->RemoveAll(root);

            }
            
            root=CopyTree(rbtree.root, NULL);
            
            size = rbtree.size;
        }
        return *this;

    }

    

    
    
    
    
	
	
    template<class T>
    bool RedBlackTree<T>::Insert(T item)
    {
		Node<T>* x=new Node<T>(item);
		if(root==NULL)
		{
			root=x;
			root->is_black= true;
			size++;
			return true;
		}
		else
		{
			Node<T>* curr;
			curr=root;
			while(curr)
			{
				x->p=curr;
				if(x->data==curr->data)
				{
					return false;
				}
				else if(x->data > curr->data)
				{
					curr=curr->right;
				}
				else
				{
					curr = curr->left;
				}

			}
			if(x->data < x->p->data)
			{
				x->p->left=x;
			}
			else
			{
				x->p->right=x;
			}
		
            
			
            size++;
			

			x->is_black=false;

			while(x != root && x->p->is_black == false)
			{
				if(x->p == x->p->p->left)
				{ 
					Node<T>* y=x->p->p->right;
					if(y==NULL) 
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
					else if (y->is_black == false) 
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
					Node<T>* y=x->p->p->left;
					if(y==NULL) 
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
					else if (y->is_black == false) 
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

    }

    
    
    
	template<class T>
    bool RedBlackTree<T>::Remove(T item)
    {
		if(Search(item)==true)
		{
	
			size--;
			Node<T> * x;
			Node<T> * y;
			Node<T> * z=new Node<T>(item);
			z=root;
			while(z->data!=item)
			{
				if(item>z->data)
                {
                    z=z->right;
                }
                else
                {
                    z=z->left;
                }
            }
			if(z->left!=NULL)
			{
				y = Predecessor(z);
				
			}
			else 
			{
				y=z;
				
			}

			if(y->left !=NULL)
			{
				x=y->left;
			}
			else
			{
				if(y->right==NULL)
				{
					x=NULL;
				}
				else if(y->right!=NULL)
				{
					x=y->right;

				}
				else
				{
					x=NULL;
				}

				
			}
			if(x!=NULL)
			{
				x->p=y->p;
			}
			if(y->p == NULL) 
			{
				root = x;
			}
			else
			{
				if(y == y->p->left)
				{
					y->p->left=x;
				}
				else
				{
					y->p->right = x;
				}
			}
			if(y != z)
			{
				z->data=y->data;
			}
			if(y->is_black == true)
			{
				
				if(y->p!=NULL)
				{
					if(x==y->p->left)
					{
						RBDeleteFixUp(x, y->p, true);
					}
					else
					{
						RBDeleteFixUp(x, y->p, false);
					}
				}
				
				else if(y->p==NULL)
				{
					if(x==y->left)
					{
						RBDeleteFixUp(x, y, true);
					}
					else
					{
						RBDeleteFixUp(x, y, false);
					}
				}
			}
			
			return true;
		}
		return false;
	}

    
    
    template<class T>
    void RedBlackTree<T>::RemoveAll()
    {
        if(root!=NULL)
		{
			
			
			
			RemoveAll(root);
			root=NULL;
			
		}
    }


    
    template<class T>
    int RedBlackTree<T>::Size() const
    {
        return size;
    }

    
    
    template<class T>
    int RedBlackTree<T>::Height() const
    {
        int height= CalculateHeight(root);
        return height;
    }


#endif

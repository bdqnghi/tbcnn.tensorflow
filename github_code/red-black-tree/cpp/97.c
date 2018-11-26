// File:        redblacktree.cpp
// Author:      Dallan Bhatti
// Date:        2016-02-27
// Description: Implementation of a Red Black Tree for use with CMPT 225 assignment #4

#ifdef _REDBLACKTREE_H_
//#include "redblacktree.h"


    // recursive helper function for deep copy
    // creates a new node "thisnode" based on sourcenode's contents, links back to parentnode,
    //   and recurses to create left and right children
// get rid of thisnode!!!
    template<class T>
    Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode)
    {
			if(sourcenode==NULL)
			{
				return NULL;
			}
			
			Node<T>* thisnode=new Node<T>(sourcenode->data);

			thisnode->p=parentnode;
            //thisnode->left=sourcenode->left;
            //thisnode->right=sourcenode->right;
			thisnode->is_black=sourcenode->is_black;

			thisnode->left=CopyTree( sourcenode->left,thisnode);

            thisnode->right=CopyTree( sourcenode->right,thisnode);

        return thisnode;

    }

    // recursive helper function for tree deletion
    // deallocates nodes in post-order
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


    // Tree fix, performed after removal of a black node
    // Note that the parameter x may be NULL
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
			//checking if x is a left child
			if(xisleftchild)
            {
                y=xparent->right;
                if(y->is_black == false)
                {
                    y->is_black = true;
                    //the parent was red
                    xparent->is_black = false;
                    LeftRotate(xparent);
                    y=xparent->right;
                }
				if((y->left==NULL|| y->left->is_black == true) && (y->right==NULL || y->right->is_black == true))
                {
                    y->is_black = false;
					x = xparent; //and then back into the while loop
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
                        //the code following this marker may cause problems
                    y->is_black=xparent->is_black;
                    xparent->is_black= true;
                    y->right->is_black=true;
                    LeftRotate(xparent);
                    x=root;
					return;
                }
            }
            //this is if x is the right child
            else
            {
                y=xparent->left;
                if(y->is_black == false)
                {
                    y->is_black = true;
                    //the parent was red
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
			//return true;

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

    // Calculates the height of the tree
    // Requires a traversal of the tree, O(n)
    // used the help of http://articles.leetcode.com/maximum-height-of-binary-tree/
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

    // default constructor
    template<class T>
    RedBlackTree<T>::RedBlackTree()
    {
           root = NULL;
           size=0;
    }

    // copy constructor, performs deep copy of parameter
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

    // destructor
    // Must deallocate memory associated with all nodes in tree
    template<class T>
    RedBlackTree<T>::~RedBlackTree()
    {
        RemoveAll();
		root=NULL;
		size=0;
    }

    // overloaded assignment operator   
    template<class T>
    RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
    {
        	//this doesn't equal ll or list2 != list1
        if(this != &rbtree)
        {
            //the only time we want to delete is if the size of the list is greater than zero
            //we are going to delete all the elements of list2
            if(size!=0)
            {

                this->RemoveAll(root);

            }
            //copy over all the elements from rb to this so they both have the same data values
            root=CopyTree(rbtree.root, NULL);
            //make sure the size is right
            size = rbtree.size;
        }
        return *this;

    }

    // Accessor functions

    // Calls BSTInsert and then performs any necessary tree fixing.
    // If item already exists, do not insert and return false.
    // Otherwise, insert, increment size, and return true.
    //CHECK THE SIZE STUFF
	//CHECK THE COLOR STUFF!!!
	//CHECK FOR REPEATS
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
		
            //my code consider using geoffreys if this doesnt work!
			//NOW TIME FOR SETTING THE COLOR
            size++;
			

			x->is_black=false;

			while(x != root && x->p->is_black == false)
			{
				if(x->p == x->p->p->left)
				{ 
					Node<T>* y=x->p->p->right;
					if(y==NULL) // y is null uncle == black
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
					else if (y->is_black == false) // y is red uncle
					{
						x->p->is_black = true;
						y->is_black = true;
						x->p->p->is_black = false;
						x = x->p->p;
					}
					else // y.colour == black
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
				// x.p == x.p.p.right
					 // symmetric to left child case above
					 // ...
				else
				{
					Node<T>* y=x->p->p->left;
					if(y==NULL) // y is a null black uncle
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
					else if (y->is_black == false) //y is red uncle
					{
						x->p->is_black = true;
						y->is_black = true;
						x->p->p->is_black = false;
						x = x->p->p;
					}
					 else // y is black non null uncle
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

    // Removal of an item from the tree.
    // Must deallocate deleted node after RBDeleteFixUp returns
    //I GOTTA WORK ON DEALLOCATION!!!!
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
			if(z->left!=NULL)//either yes it has a left child for this if statement or it has no left child aka no predecessor so we call the else
			{
				y = Predecessor(z);
				
			}
			else //if(z->left == NULL || z->right == NULL)
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
			if(y->p == NULL) // y is the root
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
				//y is not the root
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
				//y is the root
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
			//cout << "this is returned in the 80 case pretty please" << z->data <<endl;
			return true;
		}
		return false;
	}

    
    // deletes all nodes in the tree. Calls recursive helper function.
    template<class T>
    void RedBlackTree<T>::RemoveAll()
    {
        if(root!=NULL)
		{
			//cout<<"this is our root when we call this function " << root->data << " " << root << endl;
			//cout<<"this is our root->left when we call this function " << root->left->data << " " << root->left << endl;
			//cout<<"this is our root->roght when we call this function " << root->right->data << " " << root->right << endl;
			RemoveAll(root);
			root=NULL;
			
		}
    }


    // returns the number of items in the tree
    template<class T>
    int RedBlackTree<T>::Size() const
    {
        return size;
    }

    // returns the height of the tree, from root to deepest null child. Calls recursive helper function.
    // Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
    template<class T>
    int RedBlackTree<T>::Height() const
    {
        int height= CalculateHeight(root);
        return height;
    }


#endif

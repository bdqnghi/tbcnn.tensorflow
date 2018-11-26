//
//  redblacktree.cpp
//  Assign 4
//
//  Created by Mackenzie Higa on 2016-02-29.
//  Copyright © 2016 Mackenzie Higa. All rights reserved.
//

#ifdef _REDBLACKTREE_H_
#include <iostream>
#include <algorithm>
#include <math.h>

template <class T>
RedBlackTree<T>::RedBlackTree()
{
    root = NULL;
    size = 0;
}



// copy constructor, performs deep copy of parameter
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
{
    RedBlackTree<T>* newtree = new RedBlackTree<T>();
    newtree->CopyTree(rbtree.GetRoot(), rbtree.GetRoot()->p);
    root = newtree->GetRoot();
    size = rbtree.Size();
}

// destructor
// Must deallocate memory associated with all nodes in tree
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
    this->RemoveAll();
    delete root;
}

// overloaded assignment operator
template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
{
    RedBlackTree<T>* newtree = new RedBlackTree(rbtree);
    this->RemoveAll();
    root = newtree->GetRoot();
    
    size = newtree->Size();
    return *newtree;
}



// recursive helper function for deep copy
// creates a new node "thisnode" based on sourcenode's contents, links back to parentnode,
//   and recurses to create left and right children
template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode)
{
    
    
    if(!sourcenode)
        return sourcenode;
    
    Node<T>* thisnode = this->BSTInsert(sourcenode->data);
    thisnode->is_black = sourcenode->is_black;
    size++;
    thisnode->p = parentnode;
    CopyTree(sourcenode->left, thisnode);
    CopyTree(sourcenode->right, thisnode);
    
    return thisnode;
    

}



template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
    if(!node)           //basecase
        return;
    
    RemoveAll(node->left);
    RemoveAll(node->right);
    node = NULL;
    delete node;

}



template <class T>
bool RedBlackTree<T>::Insert(T item)
{
    if(this->Search(item)) //searches to see if item already exists in RBT
        return false;
    
    Node<T>* newnode = this->BSTInsert(item); //inserts node into tree
    size++; //increase size of BST
    
    if(size==1) //when root is inserted, changes colour of root to black
        root->is_black = true;
    
    
    while(newnode!=root && newnode->p->p && !newnode->p->is_black)
    {
        Node<T>* grand_parent = newnode->p->p;
        
        if(grand_parent->left == newnode->p) //checks to see if parent node is left of grandparent
        {
            Node<T>* uncle = grand_parent->right;
            
            if( (uncle) && uncle->is_black==false) //checks if uncle is not and if it's colour is red
            {
                newnode->p->is_black = true;
                uncle->is_black = true;
                grand_parent->is_black = false;
                newnode = grand_parent; //parent and uncle are now black, g-parent becomes red
            }
            
            
            else{
                
                if(newnode == newnode->p->right) //rotates items if newnode is on the right of parent
                {
                    newnode = newnode->p;
                    this->LeftRotate(newnode);
                }
                
                newnode->p->is_black = true;
                newnode->p->p->is_black = false;
                this->RightRotate(grand_parent); //rotates grandparent with parent
            }
            
        }
        else //checks to see if parent node is left of grandparent
        {
            Node<T>* uncle = grand_parent->left;
            
            if( (uncle) && uncle->is_black==false)
            {
                newnode->p->is_black = true;
                uncle->is_black = true;
                grand_parent->is_black = false;
                newnode = grand_parent;
            }
            
            
            else{
                
                if(newnode == newnode->p->left)
                {
                    newnode = newnode->p;
                    this->RightRotate(newnode);
                }
                
                newnode->p->is_black = true;
                newnode->p->p->is_black = false;
                this->LeftRotate(grand_parent);
            }
        }
        
    }
    root->is_black = true;
    return true;
    
}






template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
    Node<T>*y;
    while (x!= root && x->is_black == true){
        if(x==x->p->left){        //x is a left child
            y=xparent->right;         //x's sibling
            if (y != NULL) {
                if (y->is_black == false) {
                    y->is_black = true;
                    xparent->is_black = false; //x's parent must have been black since y is red
                    LeftRotate(x->p);
                    y = xparent->right;
                }
                if ((y->left->is_black == true ||y->left == NULL) && (y->right->is_black == true || y->right == NULL)) {
                    y->is_black = false;
                    x = x->p;
                    xparent = x->p;
                }  //and into while again
            }
            else{
                if(y->right->is_black==true || y->right ==NULL){     //makes x's sibling's right child red
                    if (y->left != NULL) {
                        y->left->is_black = true;
                    }
                    y->is_black = false;
                    RightRotate(y);
                    y=xparent->right;
                }
                y->is_black = xparent->is_black;
                xparent->is_black = true;
                if (y->right != NULL) {
                    y->right->is_black = true;
                }
                LeftRotate(x->p);
                x = root; }
        }
        else {                   //symmetric to if
            if (x == x->p->right) {        //x is a left child
                y = xparent->left;         //x's sibling
                if (y != NULL) {
                    if (y->is_black == false) {
                        y->is_black = true;
                        xparent->is_black = false; //x's parent must have been black since y is red
                        RightRotate(xparent);
                        y = xparent->left;
                    }
                    if ((y->right->is_black == true || y->right == NULL) && (y->left->is_black == true || y->left == NULL)) {
                        y->is_black = false;
                        x = x->p;
                        xparent = x->p;
                    }  //and into while again
                }
                else {
                    if (y->left->is_black == true ||y->left == NULL) {     //makes x's sibling's right child red
                        if (y->right != NULL) {
                            y->right->is_black = true;
                        }
                        y->is_black = false;
                        LeftRotate(y);
                        y = xparent->left;
                    }
                    y->is_black = xparent->is_black;
                    xparent->is_black = true;
                    if (y->left != NULL) {
                        y->left->is_black = true;
                    }
                    RightRotate(x->p);
                    x = root;
                }
            }
        }
    }
}


// Removal of an item from the tree.
// Must deallocate deleted node after RBDeleteFixUp returns
template <class T>
bool RedBlackTree<T>::Remove(T item)
{

    if ( !this->Search(item) ) //searches for item, if false returns false
        return false;
    
    

    Node<T>* newnode = root;
    while (newnode)
    {
        if (item == newnode->data)
            break;
        
        if (item < newnode->data)
            newnode = newnode->left;
        else
            newnode = newnode->right;
    }
    
    Node<T>* x;
    bool xisleftchild;
    Node<T>* y = Predecessor(newnode);
    bool isTruePrev = true;
    if (!y) //predecessor is null
    {
        y = newnode;
        isTruePrev = false;
    }
    if (y->left != NULL)
    {
        x = y->left; // x is y's left child
        xisleftchild = true;
    }
    else
    {
        x = y->right; // x is y's right child
        xisleftchild = false;
    }
    if (x != NULL)
    {
        x->p = y->p;
    }
    if (root == y) //checking if y is root
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
    if (isTruePrev == true) //if y is pre
    {
        newnode->data = y->data;
    }
    if (y->is_black == true && x !=NULL)
    {
        RBDeleteFixUp(x, x->p, xisleftchild);
    }
    delete newnode;
    size--;
    return true;
}


template <class T>
void RedBlackTree<T>::RemoveAll()
{
    RemoveAll(root);
    root=NULL;
    size = 0;
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
int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
    if (!node)
        return 0;
    
    
    int leftheight = CalculateHeight(node->left);
    int rightheight = CalculateHeight(node->right);
        
    if(leftheight > rightheight)
        return leftheight+1;
    else
    {
        return rightheight+1;
    }

    
}


template <class T>
int RedBlackTree<T>::Height() const
{
    return CalculateHeight(root);
    
}







#endif
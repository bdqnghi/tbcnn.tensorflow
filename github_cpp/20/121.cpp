#ifdef _REDBLACKTREE_

#include "redblacktree.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
using namespace std;






template <class T>
RedBlackTree<T>::RedBlackTree()
{
    root = NULL;
    rbt_size = 0;
}






template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbt)
{
    root = NULL;
    rbt_size = 0;
    root = deepCopy(rbt.root);
}







template <class T>
Node<T>* RedBlackTree<T>::deepCopy(Node<T>* source)
{
    if (source != NULL)
    {
        Node<T>* newNode = new Node<T>(source->data);
        newNode->is_black = source->is_black;
        if(source->right != NULL)
        {
            Node<T>* right = deepCopy(source->right);
            right->parent = newNode;
            newNode->right = right;
        }
        if(source->left != NULL)
        {
            Node<T>* left = deepCopy(source->left);
            left->parent = newNode;
            newNode->left = left;
        }
        rbt_size++;
        return newNode;
    }
    else
    {
        return NULL;
    }
}









template <class T>
RedBlackTree<T> & RedBlackTree<T>::operator = (const RedBlackTree<T> & rbt)
{
    if(this != & rbt)
    {
        RemoveAll();
        root = deepCopy(rbt.root);
    }
    
    return *this;
}






template <class T>
RedBlackTree<T>::~RedBlackTree()
{
    RemoveAll();
}






template <class T>
void RedBlackTree<T>::RemoveAll()
{
    RemoveAll_Helper(root);
    root = NULL;
    rbt_size = 0;
}






template <class T>
void RedBlackTree<T>::RemoveAll_Helper(Node<T>* nd)
{
    if(nd != NULL)
    {
        if(nd->left != NULL)
        {
            RemoveAll_Helper(nd->left);
        }
        if(nd->right != NULL)
        {
            RemoveAll_Helper(nd->right);
        }
        delete nd;
    }
}







template <class T>
bool RedBlackTree<T>::Insert(T item)
{
    if(Search(item) == true ) 
    {
        return false;
    }
    else 
    {
        Node<T>* newNode = new Node<T>(item);
        bstInsert(newNode); 
        newNode->is_black = false;
        
        while (newNode != root && newNode->parent->is_black == false)
        {
            if (newNode->parent == newNode->parent->parent->left)
            {
                Node<T>* uncle = newNode->parent->parent->right; 
                if (uncle != NULL && uncle->is_black == false) 
                {
                    newNode->parent->is_black = true;
                    uncle->is_black = true;
                    newNode->parent->parent->is_black = false;
                    newNode = newNode->parent->parent;
                }
                else
                {
                    if (newNode == newNode->parent->right)
                    {
                        newNode = newNode->parent;
                        Left_Rotate(newNode);
                    }
                    newNode->parent->is_black = true;
                    newNode->parent->parent->is_black = false;
                    Right_Rotate(newNode->parent->parent);
                }
            }
            else 
            {
                Node<T>* uncle = newNode->parent->parent->left; 
                if (uncle != NULL && uncle->is_black == false) 
                {
                    newNode->parent->is_black = true;
                    uncle->is_black = true;
                    newNode->parent->parent->is_black = false;
                    newNode = newNode->parent->parent;
                }
                else
                {
                    if (newNode == newNode->parent->left)
                    {
                        newNode = newNode->parent;
                        Right_Rotate(newNode);
                    }
                    newNode->parent->is_black = true;
                    newNode->parent->parent->is_black = false;
                    Left_Rotate(newNode->parent->parent);
                }
            }
        }
        root->is_black = true;
        return true;
    }
}






template <class T>
void RedBlackTree<T>::Left_Rotate(Node<T>* newNode)
{
    Node<T>* brother = newNode->right;
    newNode->right = brother->left;
    
    if (brother->left != NULL)
    {
        brother->left->parent = newNode;
    }
    
    brother->parent = newNode->parent;
    
    if (newNode->parent == NULL)
    {
        root = brother;
    }
    else if (newNode == newNode->parent->left)
    { 
        newNode->parent->left = brother;
    }
    else
    { 
        newNode->parent->right = brother;
    }
    brother->left = newNode;
    newNode->parent = brother;
}






template <class T>
void RedBlackTree<T>::Right_Rotate(Node<T>* newNode)
{
    Node<T>* brother = newNode->left;
    newNode->left = brother->right;
    
    if (brother->right != NULL)
    {
        brother->right->parent = newNode;
    }
    
    brother->parent = newNode->parent;
    
    if (newNode->parent == NULL)
    {
        root = brother;
    }
    else if (newNode == newNode->parent->right)
    { 
        newNode->parent->right = brother;
    }
    else
    { 
        newNode->parent->left = brother;
    }
    
    brother->right = newNode;
    newNode->parent = brother;
}






template <class T>
void RedBlackTree<T>::bstInsert(Node<T>* newNode)
{
    rbt_size++;
    
    if(root == NULL)
    {
        root = newNode; 
    }
    else
    { 
        Node<T>* parent = root;
        bool inserted = false;
        
        while(!inserted)
        {
            if(newNode->data < parent->data)
            { 
                if(parent->left == NULL)
                { 
                    parent->left = newNode;
                    newNode->parent = parent;
                    inserted = true;
                }
                else
                {
                    parent = parent->left; 
                }
            }
            else
            {
                if(parent->right == NULL)
                { 
                    parent->right = newNode;
                    newNode->parent = parent;
                    inserted = true;
                }
                else
                {
                    parent = parent->right; 
                }
            }
        }
    }
}







template <class T>
bool RedBlackTree<T>::Remove(T target)
{
    Node<T>* nd = SearchForNode(target);
    if(nd != NULL)
    {
        if(rbt_size == 1) 
        {
            delete root;
            root = NULL;
        }
        else
        {
            Remove_CleanUp(nd);
        }
        rbt_size--;
        return true;
    }
    else
    {
        return false;
    }
}







template <class T>
Node<T>* RedBlackTree<T>::SearchForNode(T target) const
{
    Node<T>* temp = root;
    
    while( temp != NULL && temp->data != target)
    {
        if(target > temp->data)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    return temp;
}







template <class T>
void RedBlackTree<T>::Remove_CleanUp(Node<T>* target)
{
    Node<T>* replacement;
    Node<T>* child;
    Node<T>* parent = NULL;
    
    if(target->left == NULL || target->right == NULL)
    { 
        replacement = target;
        parent = target->parent;
    }
    else
    {	
        replacement = Predecessor(target);
        parent = replacement->parent;
    }
    
    
    if (replacement->left != NULL)
    {
        child = replacement->left;
    }
    else
    {
        child = replacement->right;
    }
    
    if (child != NULL) 
        child->parent = replacement->parent; 
    
    if (replacement->parent == NULL)
    {	
        root = child;
    }
    else
    {
        
        if (replacement == replacement->parent->left) 
            replacement->parent->left = child;
        else
            replacement->parent->right = child;
    }
    
    if(replacement != target) 
        target->data = replacement->data;

    
    if (replacement->is_black == true)
    {
        if(child != NULL && child->is_black)
        {
            rbtDeleteFixUp(child, parent);
        }
        else
        {
            rbtDeleteFixUp(child, replacement->parent);
        }
    }
    delete replacement;
}






template <class T>
void RedBlackTree<T>::rbtDeleteFixUp(Node<T>* child, Node<T>* parent)
{
    Node<T>* target;
    if (child != NULL)
    {
        target = child;
    }
    else
    {
        target = parent;
    }
    while (target != NULL && target->parent != NULL && target != root && target->is_black == true)
    {
        if (target == target->parent->left){ 
            Node<T>* sibling = target->parent->right; 
            if (sibling != NULL && sibling->left != NULL && sibling->right != NULL)
            {
                if (sibling->is_black == false){ 
                    
                    sibling->is_black = true;
                    target->parent->is_black = false; 
                    Left_Rotate(target->parent);
                    sibling = target->parent->right;
                }
                if (sibling->left->is_black == true && sibling->right->is_black == true)
                { 
                    sibling->is_black = false;
                    target = target->parent; 
                }
                else
                {
                    if (sibling->right->is_black == true)
                    {
                        
                        sibling->left->is_black = true;
                        sibling->is_black = false;
                        Right_Rotate(sibling);
                        sibling = target->parent->right;
                    }
                    sibling->is_black = target->parent->is_black;
                    target->parent->is_black = true;
                    sibling->right->is_black = true;
                    Left_Rotate(target->parent);
                    target = root;
                }
            }
        }
        else
        {
            Node<T>* sibling = target->parent->left; 
            if (sibling != NULL && sibling->left != NULL && sibling->right != NULL)
            {
                if (sibling->is_black == false){ 
                    sibling->is_black = true;
                    target->parent->is_black = false;
                    Right_Rotate(target->parent);
                    sibling = target->parent->left;
                }
                if (sibling->left != NULL && sibling->left->is_black == true && sibling->right->is_black == true)
                {
                    sibling->is_black = false;
                    target = target->parent; 
                }
                else
                {
                    if (sibling->right != NULL && sibling->right->is_black == true)
                    {
                        sibling->left->is_black = true;
                        sibling->is_black = false;
                        Left_Rotate(sibling);
                        sibling = target->parent->right;
                    }
                    sibling->is_black = target->parent->is_black;
                    target->parent->is_black = true;
                    sibling->right->is_black = true;
                    Right_Rotate(target->parent);
                    target = root;
                }
            }
        }
    }
    target->is_black = true;
}







template <class T>
Node<T>* RedBlackTree<T>::Predecessor(Node<T>* nd)

{
    
    Node<T>* pre = nd->left; 
    Node<T>* pre_parent = nd->left;
    
    
    while(pre->right != NULL)
    {
        pre_parent = pre;
        pre = pre->right;
    }
    
    if (pre != pre_parent)
    {
        pre_parent->right = pre->left;
    }
    return pre;
}







template <class T>
T* RedBlackTree<T>::Dump(int& size)const
{
    if(root == NULL)
    {
        return NULL;
    }
    else
    {
        size = 0;
        T* arr = new T[rbt_size];
        InOrder_Dump(arr, size, root);
        return arr;
    }
}








template <class T>
T* RedBlackTree<T>::Between(T min, T max, int& size)const
{
    if(Search(min) == false || Search(max) == false ) 
    {
        return NULL;
    }
    else
    {
        size = 0;
        T* arr = new T[rbt_size];
        InOrder_Between(arr, size, root, min, max);
        return arr;
    }
}






template <class T>
void RedBlackTree<T>::InOrder_Dump(T arr[], int& size, Node<T>* nd) const
{
    if(nd != NULL)
    {
        InOrder_Dump(arr,size,nd->left);
        arr[size] = nd->data;
        size++;
        InOrder_Dump(arr,size,nd->right);
    }
}






template <class T>
void RedBlackTree<T>::InOrder_Between(T arr[], int& size, Node<T>* nd, T min, T max) const
{
    if(nd != NULL)
    {
        InOrder_Between(arr,size,nd->left,min,max);
        if(nd->data >= min && nd->data <= max)
        {
            arr[size] = nd->data;
            size++;
        }
        InOrder_Between(arr,size,nd->right,min,max);
    }
}







template <class T>
bool RedBlackTree<T>::Search(T item) const
{
    Node<T>* nd = root;
    while(nd != NULL)
    {
        if(item < nd->data)
        {
            nd=nd->left;
        }
        else if(item > nd->data)
        {
            nd = nd->right;
        }
        else
        {
            return true;
        }
    }
    return false;
}






template <class T>
int RedBlackTree<T>::Size() const
{
    return rbt_size;
}








template <class T>
int RedBlackTree<T>::Height() const
{
    return Height_Helper(root);
}






template <class T>
int RedBlackTree<T>::Height_Helper(Node<T>* nd)const
{
    if(nd == NULL)
    {
        return 0;
    }
    else
    {
        int maxLeft = Height_Helper(nd->left);
        int maxRight = Height_Helper(nd->right);
        return 1 + (maxLeft > maxRight ? maxLeft : maxRight);
    }
}






template <class T>
Node<T>* RedBlackTree<T>::GetRoot() const
{
    return root;
}



#endif

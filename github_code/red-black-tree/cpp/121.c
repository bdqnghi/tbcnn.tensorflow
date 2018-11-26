#ifdef _REDBLACKTREE_

#include "redblacktree.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
using namespace std;

// Constructor
// PUROSE: creates an empty tree whose root is NULL
// PARAM:
// PRE:
// POST: an empty red-black tree
template <class T>
RedBlackTree<T>::RedBlackTree()
{
    root = NULL;
    rbt_size = 0;
}

// Copy Constructor
// PUROSE: creates a deep copy of its RedBlackTree reference parameter
// PARAM: the tree to be copied
// PRE: calling helper function - deepCopy()
// POST: a copied ren-black tree
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbt)
{
    root = NULL;
    rbt_size = 0;
    root = deepCopy(rbt.root);
}

// DeepCopy and overloaded = Helper Function
// PUROSE: this function is the helper method for both Copy Constructor,
//          and Overloaded Assignment Operator =
// PARAM: the object to be copied
// PRE: must be non-empty
// POST: creates a deep copy of the imput object
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

// Overloaded Assignment Operator =
// PUROSE: deep copies its RBT reference parameter into the calling object and returns
//         a reference to the calling object after de-allocating any dynamic memory
//         associated with the original contents of the calling objects; if the calling
//         object is the same as the parameter, the operator should not copy it
// PARAM: the object to be deep copied
// PRE: calling Helper Function - RemoveAll(), deepCopy();
// POST: a new deep copied Red-Black Tree
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

// Deconstructor
// PUROSE: deletes dynamic memory allocated by the tree
// PARAM:
// PRE: calling Helper Function - RemoveAll()
// POST: a empty tree
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
    RemoveAll();
}

// RemoveAll
// PUROSE: empties the tree, de-allocating dynamic memory allocated by the tree
// PARAM:
// PRE: calling Helper Function - RemoveAll_Helper()
// POST: a empty tree
template <class T>
void RedBlackTree<T>::RemoveAll()
{
    RemoveAll_Helper(root);
    root = NULL;
    rbt_size = 0;
}

// RemoveAll Helper
// PUROSE: the Helper Function for RemoveAll
// PARAM: the parameter it the root of the tree to be removed
// PRE:
// POST: a empty tree
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

// Insert Function
// PUROSE: if the tree does not contain the method’s single parameter, inserts the parameter
//         and returns true; otherwise does not insert the parameter and returns false
// PARAM: the item to be inserted
// PRE: Calling helper function - bstInsert(), Left_Rotate(), Right_Rotate()
// POST: inserted the item and return true, otherwise return false
template <class T>
bool RedBlackTree<T>::Insert(T item)
{
    if(Search(item) == true ) //case for word already found in tree
    {
        return false;
    }
    else //create and insert new node
    {
        Node<T>* newNode = new Node<T>(item);
        bstInsert(newNode); //insert into tree
        newNode->is_black = false;
        
        while (newNode != root && newNode->parent->is_black == false)
        {
            if (newNode->parent == newNode->parent->parent->left)
            {
                Node<T>* uncle = newNode->parent->parent->right; //uncle of newNode
                if (uncle != NULL && uncle->is_black == false) //make sure uncle != NULL
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
            else // (newNode->parent == newNode->parent->parent->right)
            {
                Node<T>* uncle = newNode->parent->parent->left; //uncle of newNode
                if (uncle != NULL && uncle->is_black == false) //make sure uncle != NULL
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

// Left Rotate
// PUROSE: rotate around a node to the left
// PARAM: the node to be rotated
// PRE:
// POST: the node is left rotated
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
    { //left child
        newNode->parent->left = brother;
    }
    else
    { //right child
        newNode->parent->right = brother;
    }
    brother->left = newNode;
    newNode->parent = brother;
}

// Right Rotate
// PUROSE: rotate around a node to the right
// PARAM: the node to be rotated
// PRE:
// POST: the node is right rotated
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
    { //right child
        newNode->parent->right = brother;
    }
    else
    { //left child
        newNode->parent->left = brother;
    }
    
    brother->right = newNode;
    newNode->parent = brother;
}

// BstInsert
// PUROSE: Insert helper function, insert a new item into the tree
// PARAM: the node to be inserted to the tree
// PRE:
// POST: a node inserted to the Red-Black Tree
template <class T>
void RedBlackTree<T>::bstInsert(Node<T>* newNode)
{
    rbt_size++;
    // Tree is empty
    if(root == NULL)
    {
        root = newNode; //insert complete
    }
    else
    { //tree not empty
        Node<T>* parent = root;
        bool inserted = false;
        
        while(!inserted)
        {
            if(newNode->data < parent->data)
            { //go left
                if(parent->left == NULL)
                { //found a leaf
                    parent->left = newNode;
                    newNode->parent = parent;
                    inserted = true;
                }
                else
                {
                    parent = parent->left; //progress down tree
                }
            }
            else
            {
                if(parent->right == NULL)
                { //found a leaf
                    parent->right = newNode;
                    newNode->parent = parent;
                    inserted = true;
                }
                else
                {
                    parent = parent->right; //progress down tree
                }
            }
        }
    }
}

// Remove Function
// PUROSE: removes the method’s single parameter from the tree and returns true;
//         if the tree does not contain the parameter, returns false
// PARAM: target is the value to be removed
// PRE: Calling helper function - SearchForNode(), Remove_CleanUp()
// POST: the Node removed from the tree and return true, or not in the tree and return false
template <class T>
bool RedBlackTree<T>::Remove(T target)
{
    Node<T>* nd = SearchForNode(target);
    if(nd != NULL)
    {
        if(rbt_size == 1) // special case
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


// SearchForNode
// PUPOSE: find the node in the Red-Black Tree that to be removed
// PARAM: the value to be searched in the tree
// PRE:
// POST: Return the node that contains the value same as  parameter
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

// Remove Helper Function
// PUROSE: the remove helper function, if a node to be removed has two children, its data should be
//         replaced by its predecessor’s data and the predecessor node should be removed from the tree
// PARAM: target is the value to be removed
// PRE: Calling helper function - rbtDeleteFixUp()
// POST: the Node removed from the tree and return true, or not in the tree and return false
template <class T>
void RedBlackTree<T>::Remove_CleanUp(Node<T>* target)
{
    Node<T>* replacement;
    Node<T>* child;
    Node<T>* parent = NULL;
    
    if(target->left == NULL || target->right == NULL)
    { // if target has one or no children
        replacement = target;
        parent = target->parent;
    }
    else
    {	// target has two children
        replacement = Predecessor(target);
        parent = replacement->parent;
    }
    
    // identify if y's only child is right or left
    if (replacement->left != NULL)
    {
        child = replacement->left;
    }
    else
    {// if (replacement->right)	//x is either y->right
        child = replacement->right;
    }
    
    if (child != NULL) // NULL check
        child->parent = replacement->parent; //detach x from y
    
    if (replacement->parent == NULL)
    {	//y is the root
        root = child;
    }
    else
    {
        //attach x to y's parent
        if (replacement == replacement->parent->left) //left child
            replacement->parent->left = child;
        else
            replacement->parent->right = child;
    }
    
    if(replacement != target) //has moved up the root
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

// rbtDeleteFixUp
// PUROSE: Fix the tree after deletion
// PARAM: the target's child, the target's parent, and a bool value whether is left
// PRE: Calling helper function - Left_Rotate(), Right_Rotate()
// POST: after fix the Red-Black Tree, the tree hold the RBT properties
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
        if (target == target->parent->left){ //target is left target
            Node<T>* sibling = target->parent->right; //target's sibling
            if (sibling != NULL && sibling->left != NULL && sibling->right != NULL)
            {
                if (sibling->is_black == false){ //sibling is red
                    // make target's sibling black
                    sibling->is_black = true;
                    target->parent->is_black = false; //p was black
                    Left_Rotate(target->parent);
                    sibling = target->parent->right;
                }
                if (sibling->left->is_black == true && sibling->right->is_black == true)
                { // push the problem up tree
                    sibling->is_black = false;
                    target = target->parent; //loop back to while...
                }
                else
                {
                    if (sibling->right->is_black == true)
                    {
                        // make target's sibling's right target red
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
            Node<T>* sibling = target->parent->left; //target's sibling
            if (sibling != NULL && sibling->left != NULL && sibling->right != NULL)
            {
                if (sibling->is_black == false){ //sibling is red
                    sibling->is_black = true;
                    target->parent->is_black = false;
                    Right_Rotate(target->parent);
                    sibling = target->parent->left;
                }
                if (sibling->left != NULL && sibling->left->is_black == true && sibling->right->is_black == true)
                {
                    sibling->is_black = false;
                    target = target->parent; //loop back to while...
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
                }// end if (sibling->left && sibling->right)
            }
        }
    }
    target->is_black = true;
}

// Predecessor
// PUROSE: Finds and returns the predecessor node and attaches the predecessor's child to predecessor's parent
//         if the parent is not the parameter
// PARAM: nd is node whose predecessor is to be returned
// PRE:
// POST: return the predecessor
template <class T>
Node<T>* RedBlackTree<T>::Predecessor(Node<T>* nd)

{
    // The predecessor is R most node of LEFT subtree
    Node<T>* pre = nd->left; //start with left child
    Node<T>* pre_parent = nd->left;
    
    // Find predecessor - the R most node of the L subtree
    while(pre->right != NULL)
    {
        pre_parent = pre;
        pre = pre->right;
    }
    // Replace the predecessor with its left child
    if (pre != pre_parent)
    {
        pre_parent->right = pre->left;
    }
    return pre;
}

// Dump
// PUROSE: returns a pointer to an array in dynamic memory that contains all of the values in the tree
//         the contents of the array are in ascending order
// PARAM: the size of the tree
// PRE: calling Helper Function - InOrder_Dump()
// POST: returns a pointer to an array contains all value in the tree in ascending order
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

// Between
// PUROSE: returns a pointer to an array in dynamic memory that contains all of the values between
//         the method’s first and second parameters or NULL if there are no such values
// PARAM: two value to be searched in the tree, and the size of the tree
// PRE: calling Helper Function - InOrder_Between()
// POST: returns a pointer to an array contains the value between 1st and 2nd parameter
//       in the tree in ascending order or NULL
template <class T>
T* RedBlackTree<T>::Between(T min, T max, int& size)const
{
    if(Search(min) == false || Search(max) == false ) //case for word already found in tree
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

// Dump Helper Funciton
// PUROSE: doing in-order traversal for the Dump Function
// PARAM: the array to be returned, the size of the array, the root of the tree
// PRE:
// POST: write the value in the tree into array in ascending order
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

// Between Helper Function
// PUROSE: doing in-order traversal for the Between Function
// PARAM: the array to be returned, the size of the array, the root of the tree, two value to be searched
// PRE:
// POST: write the value in the tree into array in ascending order
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

// Search
// PUROSE: searches the tree for the method's single parameter and returns TRUE if it is found
//         and FALSE otherwise
// PARAM: the item to be searched
// PRE:
// POST: a bool value, true or false
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

// Size
// PUROSE: returns the number of items stored in the tree
// PARAM:
// PRE:
// POST: the number of node in the Red-Black Tree
template <class T>
int RedBlackTree<T>::Size() const
{
    return rbt_size;
}

// Height
// PUROSE: returns the height of the tree, the length of the longest path from the root to a leaf,
//         where the leaves are null children; the height of the tree should equal the number of
//         levels of internal(real) nodes including the root
// PARAM:
// PRE: Should be a non-empty Red-Black Tree, calling Height_Helper Function
// POST: the height of the tree
template <class T>
int RedBlackTree<T>::Height() const
{
    return Height_Helper(root);
}

// Height_Helper
// PUROSE: the Helper Function of Height
// PARAM: the root of the tree
// PRE: should be a non-empty tree
// POST: the length of the longest path from the root to a leaf
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

// GetRoot
// PUROSE: returns a pointer to the tree's root node
// PARAM:
// PRE: Should be a non-empty Red-Black Tree
// POST: the pointer to the root node of the tree
template <class T>
Node<T>* RedBlackTree<T>::GetRoot() const
{
    return root;
}



#endif

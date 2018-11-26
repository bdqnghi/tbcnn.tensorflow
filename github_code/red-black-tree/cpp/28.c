// File:        rbtreepartial.cpp
// Author:      Geoffrey Tien
// Date:        2016-02-27
// Description: Contains implementation of some RedBlackTree functions.
//              This file does not require modification.

#ifdef _REDBLACKTREE_H_



// default constructor
template <class T>
RedBlackTree<T>::RedBlackTree()
{
    root = NULL;
    size=0;
}

//copy constructor(deep copy)
template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree& rbtree)
{
    size = rbtree.Size(); // copy size
    CopyTree(rbtree.root,NULL);
}

//destructor
template <class T>
RedBlackTree<T>::~RedBlackTree()
{
    RemoveAll();
}

// = operator
template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree<T>& rbtree)
{
    if (this != &rbtree)
    {
        RemoveAll();
        size = rbtree.Size();
        CopyTree(rbtree.root,NULL);
    }
    return *this;
}

// copytree

template <class T>
Node<T>* RedBlackTree<T>:: CopyTree( Node<T>* sourcenode, Node<T>* parentnode)
{
    Node<T>* somenode= NULL;
    if ( sourcenode != NULL)
    {
        Node<T>* thisnode = new Node<T>(sourcenode->data);
        

        thisnode->is_black = sourcenode->is_black;
        if (parentnode != NULL)
        {
            thisnode->p = parentnode;
        }
        else
        {
            root = thisnode;
        }
        
        if (sourcenode->left != NULL)
        {
            
            thisnode->left=CopyTree(sourcenode->left,thisnode);
        }
        if (sourcenode->right != NULL)
        {
            thisnode->right = CopyTree(sourcenode->right,thisnode);
            
        }
        return thisnode;
    }
    return somenode;
}


template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node)
{
    if(size != 0)
    {
        if (node->left != NULL)
        {
            RemoveAll(node->left);
        }
        if (node->right != NULL)
        {
            RemoveAll(node->right);
        }
        delete node;
    }
    node = NULL;
}


//remove all
template <class T>
void RedBlackTree<T>::RemoveAll()
{
    RemoveAll(root);
    size=0;
}


template <class T>
bool RedBlackTree<T>::Insert(T item)
{
    if (Search(item)==false)
    {Node<T>* newnode = BSTInsert(item); 
        size++;
        // Fix tree now
        while (newnode != root && newnode->p->is_black==false)
        {
            if (newnode->p == newnode->p->p->left)
            {
                Node<T>* uncle=newnode->p->p->right;
                if (uncle!=NULL && uncle->is_black == false )
                {
                    newnode->p->is_black=true;
                    uncle->is_black=true;
                    newnode->p->p->is_black=false;
                    newnode=newnode->p->p;
                }
                else
                {
                    if(newnode == newnode->p->right)
                    {
                        newnode = newnode->p;
                        LeftRotate(newnode);
                    }
                    newnode->p->is_black = true;
                    newnode->p->p->is_black = false;
                    RightRotate(newnode->p->p);
                }
            }
            
            else
            {
                Node<T>* uncle=newnode->p->p->left;
                if (uncle!=NULL && uncle->is_black==false)
                {
                    newnode->p->is_black=true;
                    uncle->is_black=true;
                    newnode->p->p->is_black=false;
                    newnode=newnode->p->p;
                }
                else
                {
                    if(newnode == newnode->p->left)
                    {
                        newnode = newnode->p;
                        RightRotate(newnode);
                    }
                    newnode->p->is_black=true;
                    newnode->p->p->is_black = false;
                    LeftRotate(newnode->p->p);
                }
            }
        }
        
      // tree fixed
        root->is_black=true;
        return true;
    }	
    else
    {
        return false;
    }
    
}
template <class T>
bool RedBlackTree<T>::Remove(T item)
{
    if (Search(item) == true)
    {Node<T>* newnode = root;
    while (newnode->data != item)
    {
            if (item < newnode->data)
            {
                newnode = newnode->left;
            }
            else if (item > newnode->data)
            {
                newnode = newnode->right;
            }
    }
        Node<T>* y = nullptr;
        Node<T>* x = nullptr;
        bool xIsLeftChild = false;
        
 
        if (newnode->left == NULL || newnode->right == NULL)
        {
            y = newnode;         }
        else
        {
            y = Predecessor(newnode);
        }
        if (y->left != NULL)
        {
            x = y->left;
        }
        else
        {
            x = y->right;
        }
        if (x != NULL)
        {
            x->p = y->p;
        
        
        if (y->p == NULL)
            root = x;
        }
        else
        {
            if (y == y->p->left)
            {
                y->p->left = x;
                xIsLeftChild = true;
            }
            else
            {
                y->p->right = x;
                xIsLeftChild = false;
            }
        }
        if (y != newnode)
        {
            newnode->data = y->data;
        }
        if (y->is_black==true)
        {
            RBDeleteFixUp(x,y->p,xIsLeftChild);
        }
        
        delete y;
        return true;
    }
    return false;
}

template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{
    bool xIsBlack = false;
    if (x == NULL)
    {
        xIsBlack=true;
    }
    else
    {
        xIsBlack=x->is_black;
    }
    
    while (x!=root && xIsBlack==true)
    {
        Node<T>* newnode = nullptr;
        bool yisBlack=true;
        if (xisleftchild)
        {
            newnode = xparent->right;
            // Get y's Color
            if (newnode==NULL)
            {
                yisBlack=true;
            }
            else
            {
                yisBlack=newnode->is_black;
            }
            
            if (yisBlack==false)
            {
                if (newnode!=NULL)
                {
                    newnode->is_black=true;
                }
                xparent->is_black=false;
                LeftRotate(xparent);
                newnode = xparent->right;
            }
            
            // Check y->left color
            bool yleftBlack = false;
            // Check y's Color...
            if (newnode->left==NULL)
            {
                yleftBlack=true;
            }
            else
            {
                yleftBlack=newnode->left->is_black;
            }
            // Check y->right color
            bool yrightBlack = false;
            // Check y's Color...
            if (newnode->right==NULL)
            {
                yrightBlack=true;
            }
            else
            {
                yrightBlack=newnode->right->is_black;
            }
            if (yleftBlack == true && yrightBlack == true)
            {
                newnode->is_black=false;
                x=xparent;
            }
            else if (yrightBlack==true)
            {
                if (newnode->left != NULL)
                {
                    newnode->left->is_black=true;
                }
                newnode->is_black=false;
                RightRotate(newnode);
                newnode = xparent->right;
            }
            newnode->is_black = xparent->is_black;
            xparent->is_black=true;
            if (newnode->right!=NULL)
            {
                newnode->right->is_black=true;
            }
            LeftRotate(xparent);
            x=root;
        }
        else
        {
            newnode = xparent->left;
            if (newnode==NULL)
            {
                yisBlack=true;
            }
            else
            {
                yisBlack=newnode->is_black;
            }
            
            if (yisBlack == false)
            {
                if (newnode!=NULL)
                {
                    newnode->is_black = true;
                }
                xparent->is_black = false;
                RightRotate(xparent);
                newnode = xparent->left;
            }
            bool yleftBlack = false;
            if (newnode->left==NULL)
            {
                yleftBlack=true;
            }
            else
            {
                yleftBlack=newnode->left->is_black;
            }
            
            
            // Check y->right color
            bool yrightBlack = false;
            // Check y's Color...
            if (newnode->right==NULL)
            {
                yrightBlack=true;
            }
            else
            {
                yrightBlack=newnode->right->is_black;
            }
            
            if (yrightBlack == true && yleftBlack == true)
            {
                newnode->is_black = false;
                x = xparent;
            }
            else if(yleftBlack == true)
            {
                if (newnode->right!=NULL)
                {
                    newnode->right->is_black= true;
                }
                newnode->is_black = false;
                LeftRotate(newnode);
                newnode = xparent->left;
            }
            newnode->is_black = xparent->is_black;
            xparent->is_black = true;
            if (newnode->left!=NULL)
            {
                newnode->left->is_black = true;
            }
            RightRotate(xparent);
            x =root ;
        }
        
    }	
    x->is_black=true;
}

template <class T>
int RedBlackTree<T>::Size() const
{
    return size;
}

// Finding height of the tree
template <class T>
int RedBlackTree<T>::Height() const
{
    if (size != 0)
    {
        return CalculateHeight(root);
    }
    else
    {
        return 0;
    }
}

// Calculate height
template <class T>
int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
{
    int left = 0;
    int right = 0;
    if (node != NULL)
    {
        if(node->left != 0)
            left = CalculateHeight(node->left);
        if(node->right != 0)
            right = CalculateHeight(node->right);
        
        if( left >= right)
            return left+1;
        else
            return right+1;
    }
    return false;
}
template <class T>
Node<T>* RedBlackTree<T>::BSTInsert(T item)
{
    Node<T>* newnode1; 
    Node<T>* newnode2;
    // if empty tree
    if (size <= 0)
    {
        root = new Node<T>(item);
        newnode2 = root;
    }
    else // if not empty then
    {
        newnode1 = root;
        while ((item < newnode1->data && newnode1->left != NULL) || (item > newnode1->data && newnode1->right != NULL))
        {
            if (item < newnode1->data)
                newnode1 = newnode1->left;
            else if (item > newnode1->data)
                newnode1 = newnode1->right;
        }
        newnode2 = new Node<T>(item);
        newnode2->p = newnode1;
        if (item < newnode1->data)
            newnode1->left = newnode2;
        else
            newnode1->right = newnode2;
    }
    
    return newnode2;
}

template <class T>
bool RedBlackTree<T>::Search(T item) const
{
    Node<T>* newnode = root;
    
    while (newnode != NULL)
    {
        if (item == newnode->data)
            return true;
        else if (item < newnode->data)
            newnode = newnode->left;
        else
            newnode = newnode->right;
    }
    return false;
}
template <class T>
T* RedBlackTree<T>::Retrieve(T item)
{
    T* somevalue = NULL;
    Node<T>* newnode = root;
    while (newnode != NULL)
    {
        if (item == newnode->data)
        {
            somevalue = &(newnode->data);
            break;
            
            // found item so break
        }
        else if (item < newnode->data)
            newnode = newnode->left;
        else
            newnode = newnode->right;
    }
    // if not found just exit
    return somevalue;
}

// Inorder
template <class T>
void RedBlackTree<T>::InOrder(const Node<T>* node, T* arr, int arrsize, int& index) const
{
    if (node != NULL)
    {   // recursion on the left child of the node
        if (node->left != NULL)
            InOrder(node->left, arr, arrsize, index);
        // visits the node
        arr[index] = node->data;
        index++;
        // resursion on the right child
        if (node->right != NULL)
            InOrder(node->right, arr, arrsize, index);
    }
}
template <class T>
void RedBlackTree<T>::LeftRotate(Node<T>* node)
{
    if (node != NULL)
    {
        // if root
        if (node == root)
        {
            // case: no right child (no child or left child only)
            if (node->right == NULL)
            {
                // do nothing, do not allow the rotation
            }
            else
            {
                Node<T>* rc = node->right; // right child
                Node<T>* rclc = node->right->left; // right child's left child
                rc->p = NULL;
                rc->left = node;
                node->p = rc;
                node->right = rclc;
                if (rclc != NULL)
                    rclc->p = node;
                
                root = rc;
            }
        }
        // if elsewhere
        else
        {
            // case: no right child (no child or left child only)
            if (node->right == NULL)
            {
                // do nothing, do not allow the rotation
            }
            else
            {
                Node<T>* parent = node->p; // parent
                Node<T>* rc = node->right; // right child
                Node<T>* rclc = node->right->left; // right child's left child
                
                if (node == node->p->left)
                    node->p->left = rc;
                else
                    node->p->right = rc;
                
                rc->p = parent;
                rc->left = node;
                node->p = rc;
                node->right = rclc;
                if (rclc != NULL)
                    rclc->p = node;
            }
        }
    }
}

// remove item




template <class T>
void RedBlackTree<T>::RightRotate(Node<T>* node)
{
    if (node != NULL)
    {
        // if root
        if (node == root)
        {
            // case: no left child (no child or right child only)
            if (node->left == NULL)
            {
                // do nothing, do not allow the rotation
            }
            else
            {
                Node<T>* lc = node->left; // left child
                Node<T>* lcrc = node->left->right; // left child's right child
                lc->p = NULL;
                lc->right = node;
                node->p = lc;
                node->left = lcrc;
                if (lcrc != NULL)
                    lcrc->p = node;
                
                root = lc;
            }
        }
        // if elsewhere
        else
        {
            // case: no left child (no child or right child only)
            if (node->left == NULL)
            {
                // do nothing, do not allow the rotation
            }
            else
            {
                Node<T>* parent = node->p; // parent
                Node<T>* lc = node->left; // left child
                Node<T>* lcrc = node->left->right; // left child's right child
                
                if (node == node->p->left)
                    node->p->left = lc;
                else
                    node->p->right = lc;
                
                lc->p = parent;
                lc->right = node;
                node->p = lc;
                node->left = lcrc;
                if (lcrc != NULL)
                    lcrc->p = node;
            }
        }
    }
}

// get the predecessor of a node
template <class T>
Node<T>* RedBlackTree<T>::Predecessor(Node<T>* node)
{
    Node<T>* pre = NULL;
    // do not allow operation on a null node
    if (node != NULL)
    {
        // case: node has no left child
        if (node->left == NULL)
            pre = NULL;
        else
        {
            // go left once, then follow right pointers until no more right pointers found
            pre = node->left;
            while (pre->right != NULL)
            {
                pre = pre->right;
            }
            //while loop exi3ted, pre contains the predecessor or NULL
        }
    }
    return pre;
}

// performs an in-order traversal of the tree
// arrsize is the size of the returned array (equal to tree size attribute)
template <class T>
T* RedBlackTree<T>::Dump(int& arrsize) const
{
    int index = 0;
    arrsize = size;
    T* contents = new T[size];
    InOrder(this->root, contents, size, index);
    
    return contents;
}

#endif
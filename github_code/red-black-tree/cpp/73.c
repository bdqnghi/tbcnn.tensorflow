// Names and student ID #'s: - Faisal Al-Humaimidi (301254171).
//                           - Peter Kvac (301155934).
// Course:                   CMPT 225.
// Assignment #:             4.
// Semester:                 Summer 2015.

//#ifdef _REDBLACKTREE_H_

//************************************
// Method:    getNodeFromTree.
// FullName:  getNodeFromTree.
// Access:    public.
// Returns:   Node<T>*.
// Desk:      Search for a node with a T value (parameter),
//            and return a pointer to that node. It will
//            return a NULL as an indication of the non-
//            existence of the node.
// Parameter: Node<T>* nd (the current node of the recursive search
//            - it should begin with the root of the tree).
// Parameter: T value (the value for searching).
//************************************

template<class T>
Node<T>* getNodeFromTree(Node<T>* nd, T value) {
    if (nd != NULL) { // Making sure that no access violation will occur.
        if (nd->data == value) { // Data was found.
            return nd;
        } else {
            if (value < nd->data) { // Go left if the value is less than the current node's value.
                return getNodeFromTree(nd->left, value);
            } else { // Go right if the value is greater than or equal to the current node's value.
                return getNodeFromTree(nd->right, value);
            }
        }
    } else { // If none of the conditions was valid, return NULL as an indication of the non-existence of that item
        //   in the tree.
        return NULL;
    }
}


//************************************
// Method:    Height.
// FullName:  RedBlackTree<T>::Height.
// Access:    public.
// Returns:   unsigned int.
// Qualifier: const (it does not modify the tree).
// Desc:      Returns the longest path (number of nodes),
//            from the root (without the root itself) to a
//            certain leaf node.
//************************************

template <class T>
unsigned int RedBlackTree<T>::Height() const {
    int HeightOfTree = CalculateHeight(root); // Calls a helper method to calculate the height.
    if (HeightOfTree > 0) { // This will make sure that an empty tree or a tree with root node only
        //   will have same height of 0. Otherwise, it will decrement the hight by 1
        //   to disregard the root's node from the height.
        --HeightOfTree;
    }
    return HeightOfTree;
}



//************************************
// Method:    Size.
// FullName:  RedBlackTree<T>::Size.
// Access:    public.
// Returns:   unsigned int.
// Qualifier: const (it does not modify the tree).
// Desc:      Returns the size of the tree.
//************************************

template <class T>
unsigned int RedBlackTree<T>::Size() const {
    return size;
}



//************************************
// Method:    RemoveAll.
// FullName:  RedBlackTree<T>::RemoveAll.
// Access:    public.
// Returns:   void.
// Desc:      Calls the helper method of this method,
//            which will eventually delete every node
//            in the tree using the post-order deletion
//            method.
//************************************

template <class T>
void RedBlackTree<T>::RemoveAll() {
    RemoveAll(root);
    size = 0; // This is to explicitly returning the size counter to 0, so when
    //   we insert a first item again, it will count that item as a root
    //   (i.e. the condition size <= 0 in BSTInsert method in rbtreepartial.cpp 
    //   will be valid).
}



//************************************
// Method:    Remove.
// FullName:  RedBlackTree<T>::Remove.
// Access:    public.
// Returns:   bool (to make sure that the deletion of a node from
//            the tree was successful - it will return false if
//            no item was found in the tree that matches the passed
//            in item parameter).
// Desc:      Removes a Node from the tree with with a certain item.
// Parameter: T item (item that is meant to be removed).
//************************************

template <class T>
bool RedBlackTree<T>::Remove(T item) {
    Node<T>* x = NULL;
    Node<T>* y = NULL;
    Node<T>* z = getNodeFromTree(root, item); // The node to be removed (it's value
    //   will be gone, and it is going to be replaced
    //   by the predecessor's value if a predecessor exists
    //   for this node, and the predecessor's node will be
    //   deleted, or delete this node if no predecessor exists).


    if (z == NULL) { // If no such item was found in the tree, then return false.
        return false;
    }


    if (z->left == NULL || z->right == NULL) { // If z has at most one child.
        y = z;
    } else { // z has two children.
        y = Predecessor(z);
    }

    if (y != NULL && y->left != NULL) { // The two conditions below are to
        //   find whether is y's only child
        //   is left or right.
        x = y->left;
    } else {
        if (y != NULL) {
            x = y->right;
        }
    }

    bool xIsLeft = false;
    Node<T>* xParent = NULL;
    if (x != NULL && y != NULL) { // If x is not NULL, detach x from y.
        x->p = y->p;
        xParent = y->p;
    }

    if (y != NULL && y->p == NULL) { // Check if y is root (i.e. it has no parent).
        root = x;
    } else {
        // Attach x to y's parent.
        if (y == y->p->left) { // y is a left child.
            y->p->left = x;
            xIsLeft = true;
        } else { // y is a right child.
            y->p->right = x;
            xIsLeft = false;
        }
    }

    if (y != NULL && z != NULL && y != z) { // Check to see if y has been moved up.
        z->data = y->data;
    }

    if (y != NULL && y->is_black == true) {
        if (x == NULL) {
            if (xParent == NULL) {
                if (root != NULL && root->right != NULL && root->left != NULL && CalculateHeight(root->right) > CalculateHeight(root->left)) {
                    x = root->right;
                    xParent = root;
                    xIsLeft = false;
                } else if (root != NULL && root->right != NULL && root->left != NULL && CalculateHeight(root->left) > CalculateHeight(root->right)) {
                    x = root->left;
                    xParent = root;
                    xIsLeft = true;
                } else if (root != NULL && root->left == NULL) {
                    x = root->right;
                    xParent = root;
                    xIsLeft = false;
                } else if (root != NULL && root->right == NULL) {
                    x = root->left;
                    xParent = root;
                    xIsLeft = true;
                }
            }
        }
        RBDeleteFixUp(x, xParent, xIsLeft);
    }
    delete y; // It can be the original predecessor's node, since its
    //   value has been moved up, or it can be z itself.
    --size; // Decrement the size counter.

    if (root != NULL && root->left != NULL && root->right == NULL) {
        if (root->left->left == NULL && root->left->right == NULL) {
            root->is_black = true;
            root->left->is_black = false;
        }
    } else if (root != NULL && root->right != NULL && root->left == NULL) {
        if (root->right->left == NULL && root->right->right == NULL) {
            root->is_black = true;
            root->right->is_black = false;
        }
    }

    return true;
}

//************************************
// Method:    RBDeleteFixUp.
// FullName:  RedBlackTree<T>::RBDeleteFixUp.
// Access:    private.
// Returns:   void.
// Desc:      Fixing the tree after deletion
//            of an item to make sure it still
//            satisfies the red-black tree properties.
// Parameter: Node<T>* x (the predecessor).
// Parameter: Node<T>* xparent (the predecessor's parent).
// Parameter: bool xisleftchild (whether the predecessor is a
//            left child or not).
//************************************

template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild) {
    Node<T>* y = NULL;

    while (x != root && x != NULL && x->is_black == true) {
        if (xisleftchild == true) {
            if (xparent != NULL) {
                y = xparent->right; // y is x's sibling.
            }

            if (y != NULL && y->is_black == false) {
                y->is_black = true;
                if (xparent != NULL) {
                    xparent->is_black = false; // x's parent must have been black since y is red.
                }
                LeftRotate(xparent);
                if (xparent != NULL) {
                    y = xparent->right;
                }
            }

            if (y != NULL && y->left != NULL && y->right != NULL && y->left->is_black == true && y->right->is_black == true) {
                y->is_black = false;
                x = xparent; // Back to the loop again. 
                if (x != NULL) {
                    xparent = x->p; // Set the new xparent after x being modified.
                }
                xisleftchild = (xparent != NULL && x == xparent->left);
            } else {
                if (y != NULL && y->right != NULL && y->right->is_black == true) {
                    if (y->left != NULL) {
                        y->left->is_black = true;
                    }
                    y->is_black = false;
                    RightRotate(y);
                    if (xparent != NULL) {
                        y = xparent->right;
                    }
                }
                if (y != NULL && xparent != NULL) {
                    y->is_black = xparent->is_black;
                    xparent->is_black = true;
                }

                if (y != NULL && y->right != NULL) {
                    y->right->is_black = true;
                }

                LeftRotate(xparent);
                x = root;
                xparent = NULL;
            }
        } else { // This part is symmetric to the if part.
            if (xparent != NULL) {
                y = xparent->left; // y is x's sibling.
            }

            if (y != NULL && y->is_black == false) {
                y->is_black = true;
                if (xparent != NULL) {
                    xparent->is_black = false; // x's parent must have been black since y is red.
                }
                RightRotate(xparent);
                if (xparent != NULL) {
                    y = xparent->left;
                }
            }

            if (y != NULL && y->right != NULL && y->left != NULL && y->right->is_black == true && y->left->is_black == true) {
                y->is_black = false;
                x = xparent; // Back to the loop again. 
                if (x != NULL) {
                    xparent = x->p; // Set the new xparent after x being modified.
                }
                xisleftchild = (xparent != NULL && x == xparent->left);
            } else {
                if (y != NULL && y->left != NULL && y->left->is_black == true) {
                    if (y->right != NULL) {
                        y->right->is_black = true;
                    }
                    y->is_black = false;
                    LeftRotate(y);
                    if (xparent != NULL) {
                        y = xparent->left;
                    }
                }
                if (y != NULL && xparent != NULL) {
                    y->is_black = xparent->is_black;
                    xparent->is_black = true;
                }

                if (y != NULL && y->left != NULL) {
                    y->left->is_black = true;
                }

                RightRotate(xparent);
                x = root;
                xparent = NULL;
            }
        }
    }
    if (x != NULL) {
        x->is_black = true;
    }
}

//************************************
// Method:    Insert.
// FullName:  RedBlackTree<T>::Insert.
// Access:    public.
// Returns:   bool (to make sure that the insertion of a node to
//            the tree was successful - it will return false if
//            an item was found in the tree that matches the passed
//            in item parameter (this tree does not allow duplicates in it)).
// Desc:      Inserts a node with T item in the tree using a binary
//            tree insertion method, and fix the tree after insertion
//            to satisfy the red-black tree property.
// Parameter: T item (value for the node to insert).
//************************************

template <class T>
bool RedBlackTree<T>::Insert(T item) {
    if (Search(item) == true) { // Make sure no similar item to the passed in one exists in the tree. 
        return false;
    }

    Node<T>* x = BSTInsert(item); // Normal binary tree insertion.
    ++size; // Mainly used to make sure that root assignment in the BSTInsert only done once if there are more than
    //   one item in the tree.



    // Everything below is just to fix the tree after binary insertion.



    if (x != NULL) { // This condition might not be necessary but just to make
        //   sure that there is an item that was inserted (i.e. BSTInsert did not return NULL).
        x->is_black = false;
        Node<T>* y = NULL;
        while (x != root && x->p != NULL && x->p->is_black == false) { // Iterate until root or parent is reached.
            if (x->p->p != NULL && x->p == x->p->p->left) {
                if (x->p != NULL && x->p->p != NULL) {
                    y = x->p->p->right; // "Uncle" of x.
                }

                if (y != NULL && y->is_black == false) { // Same as x->p.
                    x->p->is_black = true;
                    y->is_black = true;
                    x->p->p->is_black = false;
                    x = x->p->p;
                } else { // y->is_black = true.
                    if (x->p != NULL && x == x->p->right) {
                        x = x->p;
                        LeftRotate(x);
                    }
                    if (x->p != NULL && x->p->p != NULL) {
                        x->p->is_black = true;
                        x->p->p->is_black = false;
                        RightRotate(x->p->p);
                    }
                }
            } else { // Symmetric to the case above, by changing every left word with right,
                //   and every left rotation with right rotation.
                if (x->p != NULL && x->p->p != NULL) {
                    y = x->p->p->left;
                }

                if (y != NULL && y->is_black == false) {
                    x->p->is_black = true;
                    y->is_black = true;
                    x->p->p->is_black = false;
                    x = x->p->p;
                } else {
                    if (x->p != NULL && x == x->p->left) {
                        x = x->p;
                        RightRotate(x);
                    }
                    if (x->p != NULL && x->p->p != NULL) {
                        x->p->is_black = true;
                        x->p->p->is_black = false;
                        LeftRotate(x->p->p);
                    }
                }
            }
        }
    }

    root->is_black = true;
    return true;
}



//************************************
// Method:    operator=.
// FullName:  RedBlackTree<T>::operator=.
// Access:    public.
// Returns:   RedBlackTree<T>&.
// Desc:      Assignment overloading for this class.
//            It will perform a deep copy of the passed in
//            RedBlackTree<T> class object, but it will first check
//            to avoid self assignment (for speed).
// Parameter: const RedBlackTree & rbtree.
//************************************

template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree& rbtree) {
    if (this != &rbtree) { // Check to see that there is no self assignment.
        RemoveAll(); // Clean the entire tree.
        CopyTree(GetRoot(), rbtree.GetRoot(), rbtree.GetRoot()); // Copy everything from rbtree to this tree.
    }
    size = rbtree.Size(); // Explicitly changing this->size to be exactely like rbtree.Size() (Size is a getter method for size counter).
    return *this;
}



//************************************
// Method:    ~RedBlackTree.
// FullName:  RedBlackTree<T>::~RedBlackTree.
// Access:    public.   
// Desc:      Class destructor. Calls RemoveAll
//            method to delete all nodes in the tree.
//************************************

template <class T>
RedBlackTree<T>::~RedBlackTree() {
    RemoveAll();
}



//************************************
// Method:    RedBlackTree.
// FullName:  RedBlackTree<T>::RedBlackTree.
// Access:    public.
// Qualifier: : root(NULL), size(0) (initializing the variables
//            of the class).
// Desc:      Copy constructor for the class.
// Parameter: const RedBlackTree& rbtree (the class's
//            object to copy from).
//************************************

template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree& rbtree) : root(NULL), size(0) {
    CopyTree(GetRoot(), rbtree.GetRoot(), rbtree.GetRoot());
    size = rbtree.Size();
}


//************************************
// Method:    RedBlackTree.
// FullName:  RedBlackTree<T>::RedBlackTree
// Access:    public.
// Qualifier: : root(NULL), size(0) (initializing the variables
//            of the class).
// Desc:      Default constructor for the class.
//************************************

template <class T>
RedBlackTree<T>::RedBlackTree() : root(NULL), size(0) {
}



//************************************
// Method:    CalculateHeight.
// FullName:  RedBlackTree<T>::CalculateHeight.
// Access:    private.
// Returns:   unsigned int.
// Qualifier: const (getter method - I.e. it should
//            not modify anything).
// Parameter: Node<T>* node (current node for recursive calls
//            to the method).
//************************************

template <class T>
unsigned int RedBlackTree<T>::CalculateHeight(Node<T>* node) const {
    if (node != NULL) {
        // Calculate the left and right height of every node recursively,
        //   and then take the largest one of them and return it.
        int leftHeight = 1 + CalculateHeight(node->left);
        int rightHeight = 1 + CalculateHeight(node->right);
        if (leftHeight > rightHeight) {
            return leftHeight;
        } else {
            return rightHeight;
        }
    } else { // Add 0 to the total height once we reach the NULL pointer.
        return 0;
    }
}







//************************************
// Method:    RemoveAll.
// FullName:  RedBlackTree<T>::RemoveAll.
// Access:    public.
// Returns:   void.
// Desc:      Helper function that recursively
//            removes every node from the tree
//            using post order traversal.
// Parameter: Node<T>* node (current recursion node).
//************************************

template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node) {
    if (node != NULL) {
        // Post-order recursive deletion of the tree so no
        //   access violation is made.
        RemoveAll(node->left);
        RemoveAll(node->right);
        delete node;
    }
    size = 0; // Explicitly returning the size to 0.
}



//************************************
// Method:    CopyTree.
// FullName:  RedBlackTree<T>::CopyTree.
// Access:    private.
// Returns:   Node<T>*.
// Parameter: Node<T>* thisnode (current node for this class - 
//            I did not use it here).
// Parameter: Node<T>* sourcenode (current node of the copying from class).
// Parameter: Node<T>* parentnode (I used this one to find the root of the
//            copying from class).
//************************************

template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode) {
    Node<T>* nd = NULL;
    if (sourcenode != NULL) {
        // Do normal pre-order binary search tree insertion to make sure that I have the same
        //    structure as the passed in tree, with a little addition of copying the passed in tree colors
        //    to make an identical red-black tree copy. 
        nd = BSTInsert(sourcenode->data);
        ++size;
        nd->is_black = sourcenode->is_black;
        CopyTree(NULL, sourcenode->left, parentnode); // I did not use thisnode argument for this function,
        CopyTree(NULL, sourcenode->right, parentnode); //    so I call the next recursive function with NULL
    } //    for thisnode argument.
    // I used parentnode as an indicator of the root for of rbtree so to make sure I set
    //   the right root for this tree.
    if (sourcenode == parentnode) {
        root = nd;
    }
    return NULL;
}


//#endif
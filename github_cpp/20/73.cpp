





















template<class T>
Node<T>* getNodeFromTree(Node<T>* nd, T value) {
    if (nd != NULL) { 
        if (nd->data == value) { 
            return nd;
        } else {
            if (value < nd->data) { 
                return getNodeFromTree(nd->left, value);
            } else { 
                return getNodeFromTree(nd->right, value);
            }
        }
    } else { 
        
        return NULL;
    }
}













template <class T>
unsigned int RedBlackTree<T>::Height() const {
    int HeightOfTree = CalculateHeight(root); 
    if (HeightOfTree > 0) { 
        
        
        --HeightOfTree;
    }
    return HeightOfTree;
}












template <class T>
unsigned int RedBlackTree<T>::Size() const {
    return size;
}














template <class T>
void RedBlackTree<T>::RemoveAll() {
    RemoveAll(root);
    size = 0; 
    
    
    
}















template <class T>
bool RedBlackTree<T>::Remove(T item) {
    Node<T>* x = NULL;
    Node<T>* y = NULL;
    Node<T>* z = getNodeFromTree(root, item); 
    
    
    
    


    if (z == NULL) { 
        return false;
    }


    if (z->left == NULL || z->right == NULL) { 
        y = z;
    } else { 
        y = Predecessor(z);
    }

    if (y != NULL && y->left != NULL) { 
        
        
        x = y->left;
    } else {
        if (y != NULL) {
            x = y->right;
        }
    }

    bool xIsLeft = false;
    Node<T>* xParent = NULL;
    if (x != NULL && y != NULL) { 
        x->p = y->p;
        xParent = y->p;
    }

    if (y != NULL && y->p == NULL) { 
        root = x;
    } else {
        
        if (y == y->p->left) { 
            y->p->left = x;
            xIsLeft = true;
        } else { 
            y->p->right = x;
            xIsLeft = false;
        }
    }

    if (y != NULL && z != NULL && y != z) { 
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
    delete y; 
    
    --size; 

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















template <class T>
void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild) {
    Node<T>* y = NULL;

    while (x != root && x != NULL && x->is_black == true) {
        if (xisleftchild == true) {
            if (xparent != NULL) {
                y = xparent->right; 
            }

            if (y != NULL && y->is_black == false) {
                y->is_black = true;
                if (xparent != NULL) {
                    xparent->is_black = false; 
                }
                LeftRotate(xparent);
                if (xparent != NULL) {
                    y = xparent->right;
                }
            }

            if (y != NULL && y->left != NULL && y->right != NULL && y->left->is_black == true && y->right->is_black == true) {
                y->is_black = false;
                x = xparent; 
                if (x != NULL) {
                    xparent = x->p; 
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
        } else { 
            if (xparent != NULL) {
                y = xparent->left; 
            }

            if (y != NULL && y->is_black == false) {
                y->is_black = true;
                if (xparent != NULL) {
                    xparent->is_black = false; 
                }
                RightRotate(xparent);
                if (xparent != NULL) {
                    y = xparent->left;
                }
            }

            if (y != NULL && y->right != NULL && y->left != NULL && y->right->is_black == true && y->left->is_black == true) {
                y->is_black = false;
                x = xparent; 
                if (x != NULL) {
                    xparent = x->p; 
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















template <class T>
bool RedBlackTree<T>::Insert(T item) {
    if (Search(item) == true) { 
        return false;
    }

    Node<T>* x = BSTInsert(item); 
    ++size; 
    



    



    if (x != NULL) { 
        
        x->is_black = false;
        Node<T>* y = NULL;
        while (x != root && x->p != NULL && x->p->is_black == false) { 
            if (x->p->p != NULL && x->p == x->p->p->left) {
                if (x->p != NULL && x->p->p != NULL) {
                    y = x->p->p->right; 
                }

                if (y != NULL && y->is_black == false) { 
                    x->p->is_black = true;
                    y->is_black = true;
                    x->p->p->is_black = false;
                    x = x->p->p;
                } else { 
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
            } else { 
                
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















template <class T>
RedBlackTree<T>& RedBlackTree<T>::operator=(const RedBlackTree& rbtree) {
    if (this != &rbtree) { 
        RemoveAll(); 
        CopyTree(GetRoot(), rbtree.GetRoot(), rbtree.GetRoot()); 
    }
    size = rbtree.Size(); 
    return *this;
}











template <class T>
RedBlackTree<T>::~RedBlackTree() {
    RemoveAll();
}














template <class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree& rbtree) : root(NULL), size(0) {
    CopyTree(GetRoot(), rbtree.GetRoot(), rbtree.GetRoot());
    size = rbtree.Size();
}











template <class T>
RedBlackTree<T>::RedBlackTree() : root(NULL), size(0) {
}














template <class T>
unsigned int RedBlackTree<T>::CalculateHeight(Node<T>* node) const {
    if (node != NULL) {
        
        
        int leftHeight = 1 + CalculateHeight(node->left);
        int rightHeight = 1 + CalculateHeight(node->right);
        if (leftHeight > rightHeight) {
            return leftHeight;
        } else {
            return rightHeight;
        }
    } else { 
        return 0;
    }
}


















template <class T>
void RedBlackTree<T>::RemoveAll(Node<T>* node) {
    if (node != NULL) {
        
        
        RemoveAll(node->left);
        RemoveAll(node->right);
        delete node;
    }
    size = 0; 
}















template <class T>
Node<T>* RedBlackTree<T>::CopyTree(Node<T>* thisnode, Node<T>* sourcenode, Node<T>* parentnode) {
    Node<T>* nd = NULL;
    if (sourcenode != NULL) {
        
        
        
        nd = BSTInsert(sourcenode->data);
        ++size;
        nd->is_black = sourcenode->is_black;
        CopyTree(NULL, sourcenode->left, parentnode); 
        CopyTree(NULL, sourcenode->right, parentnode); 
    } 
    
    
    if (sourcenode == parentnode) {
        root = nd;
    }
    return NULL;
}



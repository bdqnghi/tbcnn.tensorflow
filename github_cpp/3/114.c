

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; 
    
    Node* n = t->right;
    t->right = n->left;
    n->left = t;

    t->height = heightOrNeg1(t->left) > heightOrNeg1(t->right) ? heightOrNeg1(t->left) : heightOrNeg1(t->right);
    t->height++;
    n->height = heightOrNeg1(n->left) > heightOrNeg1(n->right) ? heightOrNeg1(n->left) : heightOrNeg1(n->right);
    n->height++;
    t = n;
    n = NULL;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; 
    
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; 
    
    Node* n = t->left;
    t->left = n->right;
    n->right = t;

    t->height = heightOrNeg1(t->left) > heightOrNeg1(t->right) ? heightOrNeg1(t->left) : heightOrNeg1(t->right);
    t->height++;
    n->height = heightOrNeg1(n->left) > heightOrNeg1(n->right) ? heightOrNeg1(n->left) : heightOrNeg1(t->right);
    
    t = n;
    n = NULL;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; 
    
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    
    if(subtree){
	int bal1, bal2;
	bal1 = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
	if(!(bal1 + 2)){
	    bal2 = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
	    if(!(bal2 + 1)){rotateRight(subtree);}
	    else{rotateLeftRight(subtree);}
	}
	else if(!(bal1 - 2)){
	    bal2 = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
	    if(!(bal2 - 1)){rotateLeft(subtree);}
	    else{rotateRightLeft(subtree);}
	}
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    
    if(subtree){
	if(key < subtree->key){insert(subtree->left, key, value);}
	else{insert(subtree->right, key, value);}
	rebalance(subtree);
	subtree->height = heightOrNeg1(subtree->left) > heightOrNeg1(subtree->right) ? heightOrNeg1(subtree->left) : heightOrNeg1(subtree->right);
	subtree->height++;
    }
    else{subtree = new Node(key, value);}
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key){remove(subtree->left, key);}
    else if (key > subtree->key){remove(subtree->right, key);}
    else {
        if (subtree->left == NULL && subtree->right == NULL) {
            
            
            delete subtree;
	    subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            
            
	    Node* n1 = subtree->left;
	    Node* n2 = n1;
	    while(n1->right){
		n2 = n1;
		n1 = n1->right;
	    }

	    swap(n1, subtree);
	    remove(n1, key);

	    n2->right = NULL;
	    n2 = NULL;
	    n1 = NULL;
        } else {
            
            
            Node* n1 = subtree;
	    if(n1->left){n1 = n1->left;}
	    else{n1 = n1->right;}

	    delete subtree;
	    subtree = n1;
	    n1 = NULL;
        }
    }
    rebalance(subtree);
}

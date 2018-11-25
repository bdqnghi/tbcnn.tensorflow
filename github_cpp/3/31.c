

#ifndef AVL_CPP
#define AVL_CPP




template <typename T, typename K>
int AVL<T,K>::bfactor() const
{
    
	return this->is_empty() ? 0 : this->right_subtree()->height() - this->left_subtree()->height();
}



template <typename T, typename K>
void AVL<T,K>::fix_height() const
{
    
	if (!this->is_empty()) {
		int left_height = this->left_subtree()->height();
		int right_height = this->right_subtree()->height();
		this->root->bt_height = 1 + max(left_height, right_height);
	}
}



template <typename T, typename K>
void AVL<T,K>::rotate_left() 
{
    
	typename AVL<T,K>::node* b = dynamic_cast<AVL*>(this->right_subtree())->root;
	this->root->right = b->left;
	b->left = dynamic_cast<AVL*>(this);
	fix_height();
	this->root = b;
	fix_height();
}



template <typename T, typename K>
void AVL<T,K>::rotate_right()
{
     
	typename AVL<T,K>::node* b = dynamic_cast<AVL*>(this->left_subtree())->root;
	this->root->left = b->right;
	b->right = dynamic_cast<AVL*>(this);
	fix_height();
	this->root = b;
	fix_height();



template <typename T, typename K>
void AVL<T,K>::balance()
{
     
	if (this->is_empty()) {
		return;
	}
	fix_height();
	int balance_factor = this->bfactor();

	if (balance_factor == 2) {
		if (dynamic_cast<AVL*>(this->right_subtree())->bfactor() < 0) {
			dynamic_cast<AVL*>(this->right_subtree())->rotate_right();
		}
		return rotate_left();
	}
	else if (balance_factor == -2) {
		if (dynamic_cast<AVL*>(this->left_subtree())->bfactor() > 0) {
			dynamic_cast<AVL*>(this->left_subtree())->rotate_left();
		}
		return rotate_right();
	}
}



template <typename T, typename K>
void AVL<T,K>::insert(const T& x, const K& k)
{
     
	if (this->is_empty()) {
		this->root = new typename AVL<T,K>::node(x,k);
		this->root->left = new AVL<T,K>;
		this->root->right = new AVL<T,K>;
	}

	else if (k < this->root->key)
		this->left_subtree()->insert(x, k);

	else if (k > this->root->key)
		this->right_subtree()->insert(x,k);

	balance();
}




template <typename T, typename K>
void AVL<T,K>::remove(const K& k)
{
     
	if (this->is_empty()) {
		return;
	}

	if (k < this->root->key) {
		this->left_subtree()->remove(k);
	}

	else if (k > this->root->key) {
		this->right_subtree()->remove(k);
	}
	else {
		AVL<T,K>* left_avl = dynamic_cast<AVL*>(this->left_subtree());
		AVL<T,K>* right_avl = dynamic_cast<AVL*>(this->right_subtree());
		if (!left_avl->is_empty() && !right_avl->is_empty()) {
			this->root->value = dynamic_cast<AVL*>(right_avl->find_min())->root->value;
			this->root->key = dynamic_cast<AVL*>(right_avl->find_min())->root->key;
			right_avl->remove(this->root->key);
		}
		else {
			typename AVL<T,K>::node* node_to_remove = this->root;
			if (left_avl->is_empty()) {
				this->root = right_avl->root;
			}
			else {
				this->root = left_avl->root;
			}
			right_avl->root = left_avl->root = NULL;
			delete node_to_remove;
		}
	}

	balance();
}



#endif 

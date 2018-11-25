




#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "avltree.h"

using namespace std;


AVLTree::AVLTree() {
	sentinel = new AVLTNode;
	sentinel->parent = NULL;
	sentinel->left = NULL;
	sentinel->right = sentinel;
	sentinel->height = -1;
	size = 0;
}


AVLTree::~AVLTree() {
	recursive_destroy(sentinel->right);
	delete sentinel;
}



int AVLTree::Insert(string key, void *val) {
	AVLTNode *parent;
	AVLTNode *n;

	parent = sentinel;
	n = sentinel->right;

	while (n != sentinel) {
		if (n->key == key) return 0;
		parent = n;
		if (key < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}

	n = new AVLTNode;
	n->key = key;
	n->val = val;
	n->parent = parent;
	n->left = sentinel;
	n->right = sentinel;
	if (parent == sentinel) {
		sentinel->right = n;
	} else if (key < parent->key) {
		parent->left = n;
	} else {
		parent->right = n;
	}
	size++;
	n->height = 0;

	Check_Balance(n->parent);

	return 1;
}


void *AVLTree::Find(string key) {
	AVLTNode *n;

	n = sentinel->right;
	while (1) {
		if (n == sentinel) return NULL;
		if (key == n->key) return n->val;
		if (key < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}
}



int AVLTree::Delete(string key) {
	AVLTNode *n, *parent, *mlc;
	string tmpkey;
	void *tmpval;

	n = sentinel->right;
	while (n != sentinel && key != n->key) {
		if (key < n->key) {
			n = n->left;
		} else {
			n = n->right;
		}
	}
	if (n == sentinel) return 0;

	parent = n->parent;
	if (n->left == sentinel) {
		if (n == parent->left) {
			parent->left = n->right;
		} else {
			parent->right = n->right;
		}
		if (n->right != sentinel) {
			n->right->parent = parent;
		}
		delete n;
		size--;
	} else if (n->right == sentinel) {
		if (n == parent->left) {
			parent->left = n->left;
		} else {
			parent->right = n->left;
		}
		n->left->parent = parent;
		delete n;
		size--;
	} else {
		for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
		tmpkey = mlc->key;
		tmpval = mlc->val;
		Delete(tmpkey);
		n->key = tmpkey;
		n->val = tmpval;
	}

	Check_Balance(parent);

	return 1;
}


void AVLTree::Print() {
	recursive_inorder_print(0, sentinel->right);
}


int AVLTree::Size() {
	return size;
}


int AVLTree::Empty() {
	return (size == 0);
}


vector <void *> AVLTree::Sorted_Vector() {
	array.clear();
	recursive_make_vector(sentinel->right);
	return array;
}


void AVLTree::Check_Balance(AVLTNode *n) {
	int nlheight, nrheight, setheight;

	if (n == sentinel) return;
	nlheight = n->left->height;
	nrheight = n->right->height;

	if (nlheight > nrheight) setheight = (nlheight + 1);
	else setheight = (nrheight + 1);

	n->height = setheight;
	n = Rebalance(n);
	Check_Balance(n->parent);
}



AVLTNode *AVLTree::Rebalance(AVLTNode *n) {
	AVLTNode *lsub, *rsub, *llsub, *rrsub;
	int lheight = 0, rheight = 0, lsheight = 0, rsheight = 0;

	lheight = n->left->height;
	rheight = n->right->height;

	if (abs(lheight - rheight) <= 1) return n;

	
	lsub = n->left;
	rsub = n->right;

	
	if (lheight > rheight) {
		llsub = lsub->left;
		rrsub = lsub->right;
		lsheight = llsub->height;
		rsheight = rrsub->height;

		
		if (lsheight >= rsheight) {
			Rotate(lsub);
			Check_Balance(lsub->parent);
			return lsub;
		}
		
		else {
			Rotate(rrsub);
			Rotate(rrsub);
			Check_Balance(rrsub->parent);
			return rrsub;
		}
	}
	
	else {
		llsub = rsub->left;
		rrsub = rsub->right;
		lsheight = llsub->height;
		rsheight = rrsub->height;

		
		if (rsheight >= lsheight) {
			Rotate(rsub);
			Check_Balance(rsub->parent);
			return rsub;
		}
		
		else {
			Rotate(llsub);
			Rotate(llsub);
			Check_Balance(llsub->parent);
			return llsub;
		}
	}

	return n;
}


void AVLTree::Rotate(AVLTNode *n) {
	AVLTNode *parent, *child, *oldparent;
	int newheight, lheight = -1, rheight = -1;

	if (Empty()) return;

	
	parent = n->parent;
	oldparent = parent->parent;
	if (oldparent->left == parent) oldparent->left = n;
	else oldparent->right = n;

	
	
	
	if (parent->left == n) {
		
		child = n->right;
		parent->left = child;
		n->right = parent;
	}
	else {
		
		child = n->left;
		parent->right = child;
		n->left = parent;
	}

	
	n->parent = oldparent;
	parent->parent = n;
	if (child != sentinel) child->parent = parent;

	
	lheight = parent->left->height;
	rheight = parent->right->height;

	if (lheight > rheight) newheight = (lheight + 1);
	else newheight = (rheight + 1);

	parent->height = newheight;
	newheight = 0;
	lheight = -1;
	rheight = -1;

	lheight = n->left->height;
	rheight = n->right->height;

	if (lheight > rheight) newheight = (lheight + 1);
	else newheight = (rheight + 1);

	n->height = newheight;

	return;
}


void AVLTree::recursive_inorder_print(int level, AVLTNode *n) {
	if (n == sentinel) return;
	recursive_inorder_print(level+2, n->right);
	printf("%*s%d %s\n", level, "", n->height, n->key.c_str());
	recursive_inorder_print(level+2, n->left);
}



void AVLTree::recursive_make_vector(AVLTNode *n) {
	if (n == sentinel) return;
	recursive_make_vector(n->left);
	array.push_back(n->val);
	recursive_make_vector(n->right);
}


void AVLTree::recursive_destroy(AVLTNode *n) {
	if (n == sentinel) return;
	recursive_destroy(n->left);
	recursive_destroy(n->right);
	delete n;
}

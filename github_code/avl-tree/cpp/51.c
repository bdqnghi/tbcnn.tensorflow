#ifndef AVL_H
#define AVL_H

#include "tree.h"

template <class T> 
class AVL : public Tree<T> {
public:
	// constructors
	AVL( const T &v ) : Tree<T>(v) {}

	AVL( const T &v, AVL<T> *l, AVL<T> *r ) 
		: Tree<T>(v,l,r,NULL) {}

	AVL( const T &v, AVL<T> *l, AVL<T> *r, AVL<T> *p ) 
		: Tree<T>(v,l,r,p) {}

	AVL( const T &v, int h, AVL<T> *l, AVL<T> *r, AVL<T> *p ) 
		: Tree<T>(v,l,r,p,h) {}


	// cloners
	AVL( const AVL<T> & c ) 
		: Tree<T>(c.value, c.left, c.right, c.parent, c.height) {}

	AVL( AVL<T> *c ) 
		: Tree<T>(c->value, c->left, c->right, c->parent, c->height) {}


	// unvirtualized utilities
	AVL<T> * search( const T &v );
		// returns pointer to node (containing v, if exists) or NULL (otherwise)

	AVL<T> * insert( const T &v );
		// returns pointer updated tree (containing v)

	AVL<T> * remove( const T &v );
		// returns pointer updated tree (no longer containing v)

	void rotateR();
	
	void rotateL();


	// little helpers
	AVL<T> * balance();		
		// rebalance tree

	void updateHeight();	
		// recompute heights of all nodes in tree

	int heightDifference();	
		// compute height differences between children

};

#include "avl.cpp"

#endif


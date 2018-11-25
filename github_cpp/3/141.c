#ifndef AVL_H
#define AVL_H

#include "tree.h"

template <class T> 
class AVL : public Tree<T> {
public:
	
	AVL( const T &v ) : Tree<T>(v) {}

	AVL( const T &v, AVL<T> *l, AVL<T> *r ) 
		: Tree<T>(v,l,r,NULL) {}

	AVL( const T &v, AVL<T> *l, AVL<T> *r, AVL<T> *p ) 
		: Tree<T>(v,l,r,p) {}

	AVL( const T &v, int h, AVL<T> *l, AVL<T> *r, AVL<T> *p ) 
		: Tree<T>(v,l,r,p,h) {}


	
	AVL( const AVL<T> & c ) 
		: Tree<T>(c.value, c.left, c.right, c.parent, c.height) {}

	AVL( AVL<T> *c ) 
		: Tree<T>(c->value, c->left, c->right, c->parent, c->height) {}


	
	AVL<T> * search( const T &v );
		

	AVL<T> * insert( const T &v );
		

	AVL<T> * remove( const T &v );
		


	
	AVL<T> * balance();		
		

	
		
	AVL<T> *getRoot();
	int heightDifference();	
		

};

#include "avl.cpp"

#endif


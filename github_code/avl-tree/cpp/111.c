#ifndef AVL_CPP
#define AVL_CPP
#include "Node.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <cstdlib>
#include <sstream>
using namespace std;

template <typename Comparable>
class AVL_Tree {
  private:
    int height( Node<Comparable> *t ) const {
        return t == NULL ? -1 : t->height;
    }
    void insert( Node<Comparable> *&x, Node<Comparable> *&t) {
        if( t == NULL ) 
            t = new Node<Comparable>( x->element, NULL, NULL, 0, 0, 0 );
        else if( x->element < t->element ) 
            insert( x, t->left );
        else if( t->element < x->element ) 
            insert( x, t->right );
        else if( t->element == x->element) 
            insert(x, t->right);
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;
    // Assume t is balanced or within one of being balanced
    void balance( Node<Comparable> *&t) { 
        if( t == NULL )
        return;
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
        if( height( t->left->left ) >= height( t->left->right ) )
        rotateWithLeftChild( t );
        else
        doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
        if( height( t->right->right ) >= height( t->right->left ) )
        rotateWithRightChild( t );
        else
        doubleWithRightChild( t );
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    void rotateWithLeftChild( Node<Comparable> * & k2 ) {
        Node<Comparable> *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    void rotateWithRightChild( Node<Comparable> * & k2 ) {
        Node<Comparable> *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max( height( k2->right ), height( k2->left ) ) + 1;
        k1->height = max( height( k1->right ), k2->height ) + 1;
        k2 = k1;
    }
  
    void doubleWithLeftChild( Node<Comparable> * & k3 ) {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    void doubleWithRightChild( Node<Comparable> * & k3 ) {
        rotateWithLeftChild( k3->right );
        rotateWithRightChild( k3 );
    }

    void remove( const Comparable & x, Node<Comparable> *&t) {
      if( t == NULL ) {
          return; // Item not found; do nothing
      }
      if( x < t->element ) {
          remove( x, t->left );
      }
      else if( t->element < x ) {
          remove( x, t->right );
      }
      else if( t->left != NULL && t->right != NULL ) { // Two children
          t->element = findMin( t->right )->element;
          remove( t->element, t->right );
      }
      else {
          Node<Comparable> *oldNode = t;
          t = ( t->left != NULL ) ? t->left : t->right;
          delete oldNode;
      }

      balance( t );
    }
    
  public:
    Node<Comparable> *root;
    AVL_Tree() : root(0) {}
    void insert( Comparable &x ) { 
        Node<Comparable> *t = new Node<Comparable> (x, NULL, NULL, 0, 0, 0);
        insert(t, root);
    }
};

#endif
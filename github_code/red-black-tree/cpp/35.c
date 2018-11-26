#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include "Wrapper.h"

// Red-black tree class.
//
// CONSTRUCTION: with negative infinity object
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// Comparable find( x )   --> Return item that matches x
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws exceptions as warranted.


template <class Comparable>
class RedBlackTree;

template <class Comparable>
class RedBlackNode;

template <class Comparable>
class RedBlackTree
{
  public:
    RedBlackTree( const Comparable & negInf );
    RedBlackTree( const RedBlackTree & rhs );
    ~RedBlackTree( );

    Cref<Comparable> findMin( ) const;
    Cref<Comparable> findMax( ) const;
    Cref<Comparable> find( const Comparable & x ) const;
    bool isEmpty( ) const;

    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );

    enum { RED, BLACK };

    const RedBlackTree & operator=( const RedBlackTree & rhs );

    typedef RedBlackNode<Comparable> Node;

  private:
    Node *header;   // The tree header (contains negInf)
    Node *nullNode;

      // Used in insert routine and its helpers (logically static)
    Node *current;
    Node *parent;
    Node *grand;
    Node *great;

      // Usual recursive stuff
    void reclaimMemory( Node *t ) const;
    RedBlackNode<Comparable> * clone( Node * t ) const;

      // Red-black tree manipulations
    void handleReorient( const Comparable & item );
    RedBlackNode<Comparable> * rotate( const Comparable & item,
                                Node *parent ) const;
    void rotateWithLeftChild( Node * & k2 ) const;
    void rotateWithRightChild( Node * & k1 ) const;
};

template <class Comparable>
class RedBlackNode
{
    Comparable    element;
    RedBlackNode *left;
    RedBlackNode *right;
    int           color;

    RedBlackNode( const Comparable & theElement = Comparable( ),
                      RedBlackNode *lt = NULL, RedBlackNode *rt = NULL,
                      int c = RedBlackTree<Comparable>::BLACK )
      : element( theElement ), left( lt ), right( rt ), color( c ) { }
    friend class RedBlackTree<Comparable>;
};

#include "RedBlackTree.cpp"
#endif

        #ifndef RED_BLACK_TREE_H_
        #define RED_BLACK_TREE_H_

        #include "dsexceptions.h"
        #include <iostream>       // For NULL

        // Red-black tree class
        //
        // CONSTRUCTION: with negative infinity object also
        //               used to signal failed finds
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x (unimplemented)
        // Comparable find( x )   --> Return item that matches x
        // Comparable findMin( )  --> Return smallest item
        // Comparable findMax( )  --> Return largest item
        // boolean isEmpty( )     --> Return true if empty; else false
        // void makeEmpty( )      --> Remove all items
        // void printTree( )      --> Print tree in sorted order



          // Node and forward declaration because g++ does
          // not understand nested classes.
        template <class Comparable>
        class RedBlackTree;

        template <class Comparable>
        class RedBlackNode
        {
            Comparable    element;
            RedBlackNode *left;
            RedBlackNode *right;
            int           color;

            // c = 1 should be c = RedBlackTree<Comparable>::BLACK
            // But Visual 5.0 does not comprehend it.
            RedBlackNode( const Comparable & theElement = Comparable( ),
                              RedBlackNode *lt = NULL, RedBlackNode *rt = NULL,
                              int c = 1 )
              : element( theElement ), left( lt ), right( rt ), color( c ) { }
            friend class RedBlackTree<Comparable>;
        };

        template <class Comparable>
        class RedBlackTree
        {
          public:
            explicit RedBlackTree( const Comparable & negInf );
            RedBlackTree( const RedBlackTree & rhs );
            ~RedBlackTree( );

            const Comparable & findMin( ) const;
            const Comparable & findMax( ) const;
            const Comparable & find( const Comparable & x ) const;
            bool isEmpty( ) const;
            void printTree( ) const;

            void makeEmpty( );
            void insert( const Comparable & x );
            void remove( const Comparable & x );

            enum { RED, BLACK };

            const RedBlackTree & operator=( const RedBlackTree & rhs );

          private:
            RedBlackNode<Comparable> *header;   // The tree header (contains negInf)
            const Comparable ITEM_NOT_FOUND;
            RedBlackNode<Comparable> *nullNode;

                // Used in insert routine and its helpers (logically static)
            RedBlackNode<Comparable> *current;
            RedBlackNode<Comparable> *parent;
            RedBlackNode<Comparable> *grand;
            RedBlackNode<Comparable> *great;

                // Usual recursive stuff
            void reclaimMemory( RedBlackNode<Comparable> *t ) const;
            void printTree( RedBlackNode<Comparable> *t ) const;
            RedBlackNode<Comparable> * clone( RedBlackNode<Comparable> * t ) const;

                // Red-black tree manipulations
            void handleReorient( const Comparable & item );
            RedBlackNode<Comparable> * rotate( const Comparable & item,
                                        RedBlackNode<Comparable> *parent ) const;
            void rotateWithLeftChild( RedBlackNode<Comparable> * & k2 ) const;
            void rotateWithRightChild( RedBlackNode<Comparable> * & k1 ) const;
        };

        #include "RedBlackTree.cpp"
        #endif

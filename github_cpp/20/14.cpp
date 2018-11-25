        #ifndef RED_BLACK_TREE_H_
        #define RED_BLACK_TREE_H_

        #include "dsexceptions.h"
        #include <iostream>       

        
        
        
        
        
        
        
        
        
        
        
        
        
        



          
          
        template <class Comparable>
        class RedBlackTree;

        template <class Comparable>
        class RedBlackNode
        {
            Comparable    element;
            RedBlackNode *left;
            RedBlackNode *right;
            int           color;

            
            
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
            RedBlackNode<Comparable> *header;   
            const Comparable ITEM_NOT_FOUND;
            RedBlackNode<Comparable> *nullNode;

                
            RedBlackNode<Comparable> *current;
            RedBlackNode<Comparable> *parent;
            RedBlackNode<Comparable> *grand;
            RedBlackNode<Comparable> *great;

                
            void reclaimMemory( RedBlackNode<Comparable> *t ) const;
            void printTree( RedBlackNode<Comparable> *t ) const;
            RedBlackNode<Comparable> * clone( RedBlackNode<Comparable> * t ) const;

                
            void handleReorient( const Comparable & item );
            RedBlackNode<Comparable> * rotate( const Comparable & item,
                                        RedBlackNode<Comparable> *parent ) const;
            void rotateWithLeftChild( RedBlackNode<Comparable> * & k2 ) const;
            void rotateWithRightChild( RedBlackNode<Comparable> * & k1 ) const;
        };

        #include "RedBlackTree.cpp"
        #endif

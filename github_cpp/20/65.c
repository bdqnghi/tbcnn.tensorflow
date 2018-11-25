	#ifndef IMPLEMENTATION_RED_BLACK_TREE_
	#define IMPLEMENTATION_RED_BLACK_TREE_
        
	#include "RedBlackTree.h"
	using namespace std;
	
        
        template <class Comparable>
        RedBlackTree<Comparable>::RedBlackTree( const Comparable & negInf )
          : ITEM_NOT_FOUND( negInf )
        {
            nullNode    = new RedBlackNode<Comparable>;
            nullNode->left = nullNode->right = nullNode;
            header      = new RedBlackNode<Comparable>( negInf );
            header->left = header->right = nullNode;
        }

        
        template <class Comparable>
        RedBlackTree<Comparable>::RedBlackTree( const RedBlackTree<Comparable> & rhs )
          : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
        {
            nullNode    = new RedBlackNode<Comparable>;
            nullNode->left = nullNode->right = nullNode;
            header      = new RedBlackNode<Comparable>( ITEM_NOT_FOUND );
            header->left = header->right = nullNode;
            *this = rhs;
        }

        
        template <class Comparable>
        RedBlackTree<Comparable>::~RedBlackTree( )
        {
            makeEmpty( );
            delete nullNode;
            delete header;
        }

        
        template <class Comparable>
        void RedBlackTree<Comparable>::insert( const Comparable & x )
        {
            current = parent = grand = header;
            nullNode->element = x;

            while( current->element != x )
            {
                great = grand; grand = parent; parent = current;
                current = x < current->element ?  current->left : current->right;

                    
                if( current->left->color == RED && current->right->color == RED )
                     handleReorient( x );
            }

                
            if( current != nullNode )
                return;
            current = new RedBlackNode<Comparable>( x, nullNode, nullNode );

                
            if( x < parent->element )
                parent->left = current;
            else
                parent->right = current;
            handleReorient( x );
        }

        
        template <class Comparable>
        void RedBlackTree<Comparable>::remove( const Comparable & x )
        {
            cout << "Sorry, remove unimplemented; " << x <<
                 " still present" << endl;
        }

        
        template <class Comparable>
        const Comparable & RedBlackTree<Comparable>::findMin( ) const
        {
            if( isEmpty( ) )
                return ITEM_NOT_FOUND;

            RedBlackNode<Comparable> *itr = header->right;

            while( itr->left != nullNode )
                itr = itr->left;

            return itr->element;
        }

        
        template <class Comparable>
        const Comparable & RedBlackTree<Comparable>::findMax( ) const
        {
            if( isEmpty( ) )
                return ITEM_NOT_FOUND;

            RedBlackNode<Comparable> *itr = header->right;

            while( itr->right != nullNode )
                itr = itr->right;

            return itr->element;
        }

        
        template <class Comparable>
        const Comparable & RedBlackTree<Comparable>::find( const Comparable & x ) const
        {
            nullNode->element = x;
            RedBlackNode<Comparable> *curr = header->right;

            for( ; ; )
            {
                if( x < curr->element )
                    curr = curr->left;
                else if( curr->element < x )
                    curr = curr->right;
                else if( curr != nullNode )
                    return curr->element;
                else
                    return ITEM_NOT_FOUND;
            }
        }

        
        template <class Comparable>
        void RedBlackTree<Comparable>::makeEmpty( )
        {
            reclaimMemory( header->right );
            header->right = nullNode;
        }

        
        template <class Comparable>
        bool RedBlackTree<Comparable>::isEmpty( ) const
        {
            return header->right == nullNode;
        }

        
        template <class Comparable>
        void RedBlackTree<Comparable>::printTree( ) const
        {
            if( header->right == nullNode )
                cout << "Empty tree" << endl;
            else
                printTree( header->right );
        }


        
        template <class Comparable>
        const RedBlackTree<Comparable> &
        RedBlackTree<Comparable>::operator=( const RedBlackTree<Comparable> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                header->right = clone( rhs.header->right );
            }

            return *this;
        }

        
        template <class Comparable>
        void RedBlackTree<Comparable>::printTree( RedBlackNode<Comparable> *t ) const
        {
            if( t != t->left )
            {
                printTree( t->left );
                cout << t->element << endl;
                printTree( t->right );
            }
        }

        
        template <class Comparable>
        RedBlackNode<Comparable> *
        RedBlackTree<Comparable>::clone( RedBlackNode<Comparable> * t ) const
        {
            if( t == t->left )  
                return nullNode;
            else
                return new RedBlackNode<Comparable>( t->element, clone( t->left ),
                                               clone( t->right ), t->color );
        }


        
        template <class Comparable>
        void RedBlackTree<Comparable>::handleReorient( const Comparable & item )
        {
                
            current->color = RED;
            current->left->color = BLACK;
            current->right->color = BLACK;

            if( parent->color == RED )   
            {
                grand->color = RED;
                if( item < grand->element != item < parent->element )
                    parent = rotate( item, grand );  
                current = rotate( item, great );
                current->color = BLACK;
            }
            header->right->color = BLACK; 
        }

        
        template <class Comparable>
        RedBlackNode<Comparable> *
        RedBlackTree<Comparable>::rotate( const Comparable & item,
                              RedBlackNode<Comparable> *theParent ) const
        {
            if( item < theParent->element )
            {
                item < theParent->left->element ?
                    rotateWithLeftChild( theParent->left )  :  
                    rotateWithRightChild( theParent->left ) ;  
                return theParent->left;
            }
            else
            {
                item < theParent->right->element ?
                    rotateWithLeftChild( theParent->right ) :  
                    rotateWithRightChild( theParent->right );  
                return theParent->right;
            }
        }

        
        template <class Comparable>
        void RedBlackTree<Comparable>::
        rotateWithLeftChild( RedBlackNode<Comparable> * & k2 ) const
        {
            RedBlackNode<Comparable> *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2 = k1;
        }

        
        template <class Comparable>
        void RedBlackTree<Comparable>::
        rotateWithRightChild( RedBlackNode<Comparable> * & k1 ) const
        {
            RedBlackNode<Comparable> *k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k1 = k2;
        }


        
        template <class Comparable>
        void RedBlackTree<Comparable>::reclaimMemory( RedBlackNode<Comparable> *t ) const
        {
            if( t != t->left )
            {
                reclaimMemory( t->left );
                reclaimMemory( t->right );
                delete t;
            }
        }
	
	#endif

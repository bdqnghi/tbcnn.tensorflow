	#ifndef IMPLEMENTATION_RED_BLACK_TREE_
	#define IMPLEMENTATION_RED_BLACK_TREE_
        
	#include "RedBlackTree.h"
	using namespace std;
	
        /**
         * Construct the tree.
         * negInf is a value less than or equal to all others.
         * It is also used as ITEM_NOT_FOUND.
         */
        template <class Comparable>
        RedBlackTree<Comparable>::RedBlackTree( const Comparable & negInf )
          : ITEM_NOT_FOUND( negInf )
        {
            nullNode    = new RedBlackNode<Comparable>;
            nullNode->left = nullNode->right = nullNode;
            header      = new RedBlackNode<Comparable>( negInf );
            header->left = header->right = nullNode;
        }

        /**
         * Copy constructor.
         */
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

        /**
         * Destroy the tree.
         */
        template <class Comparable>
        RedBlackTree<Comparable>::~RedBlackTree( )
        {
            makeEmpty( );
            delete nullNode;
            delete header;
        }

        /**
         * Insert item x into the tree. Does nothing if x already present.
         */
        template <class Comparable>
        void RedBlackTree<Comparable>::insert( const Comparable & x )
        {
            current = parent = grand = header;
            nullNode->element = x;

            while( current->element != x )
            {
                great = grand; grand = parent; parent = current;
                current = x < current->element ?  current->left : current->right;

                    // Check if two red children; fix if so
                if( current->left->color == RED && current->right->color == RED )
                     handleReorient( x );
            }

                // Insertion fails if already present
            if( current != nullNode )
                return;
            current = new RedBlackNode<Comparable>( x, nullNode, nullNode );

                // Attach to parent
            if( x < parent->element )
                parent->left = current;
            else
                parent->right = current;
            handleReorient( x );
        }

        /**
         * Remove item x from the tree.
         * Not implemented in this version.
         */
        template <class Comparable>
        void RedBlackTree<Comparable>::remove( const Comparable & x )
        {
            cout << "Sorry, remove unimplemented; " << x <<
                 " still present" << endl;
        }

        /**
         * Find the smallest item  the tree.
         * Return the smallest item or ITEM_NOT_FOUND if empty.
         */
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

        /**
         * Find the largest item in the tree.
         * Return the largest item or ITEM_NOT_FOUND if empty.
         */
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

        /**
         * Find item x in the tree.
         * Return the matching item or ITEM_NOT_FOUND if not found.
         */
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

        /**
         * Make the tree logically empty.
         */
        template <class Comparable>
        void RedBlackTree<Comparable>::makeEmpty( )
        {
            reclaimMemory( header->right );
            header->right = nullNode;
        }

        /**
         * Test if the tree is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Comparable>
        bool RedBlackTree<Comparable>::isEmpty( ) const
        {
            return header->right == nullNode;
        }

        /**
         * Print the tree contents in sorted order.
         */
        template <class Comparable>
        void RedBlackTree<Comparable>::printTree( ) const
        {
            if( header->right == nullNode )
                cout << "Empty tree" << endl;
            else
                printTree( header->right );
        }


        /**
         * Deep copy.
         */
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

        /**
         * Internal method to print a subtree t in sorted order.
         */
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

        /**
         * Internal method to clone subtree.
         */
        template <class Comparable>
        RedBlackNode<Comparable> *
        RedBlackTree<Comparable>::clone( RedBlackNode<Comparable> * t ) const
        {
            if( t == t->left )  // Cannot test against nullNode!!!
                return nullNode;
            else
                return new RedBlackNode<Comparable>( t->element, clone( t->left ),
                                               clone( t->right ), t->color );
        }


        /**
         * Internal routine that is called during an insertion
         *     if a node has two red children. Performs flip
         *     and rotatons.
         * item is the item being inserted.
         */
        template <class Comparable>
        void RedBlackTree<Comparable>::handleReorient( const Comparable & item )
        {
                // Do the color flip
            current->color = RED;
            current->left->color = BLACK;
            current->right->color = BLACK;

            if( parent->color == RED )   // Have to rotate
            {
                grand->color = RED;
                if( item < grand->element != item < parent->element )
                    parent = rotate( item, grand );  // Start dbl rotate
                current = rotate( item, great );
                current->color = BLACK;
            }
            header->right->color = BLACK; // Make root black
        }

        /**
         * Internal routine that performs a single or double rotation.
         * Because the result is attached to the parent, there are four cases.
         * Called by handleReorient.
         * item is the item in handleReorient.
         * parent is the parent of the root of the rotated subtree.
         * Return the root of the rotated subtree.
         */
        template <class Comparable>
        RedBlackNode<Comparable> *
        RedBlackTree<Comparable>::rotate( const Comparable & item,
                              RedBlackNode<Comparable> *theParent ) const
        {
            if( item < theParent->element )
            {
                item < theParent->left->element ?
                    rotateWithLeftChild( theParent->left )  :  // LL
                    rotateWithRightChild( theParent->left ) ;  // LR
                return theParent->left;
            }
            else
            {
                item < theParent->right->element ?
                    rotateWithLeftChild( theParent->right ) :  // RL
                    rotateWithRightChild( theParent->right );  // RR
                return theParent->right;
            }
        }

        /**
         * Rotate binary tree node with left child.
         */
        template <class Comparable>
        void RedBlackTree<Comparable>::
        rotateWithLeftChild( RedBlackNode<Comparable> * & k2 ) const
        {
            RedBlackNode<Comparable> *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2 = k1;
        }

        /**
         * Rotate binary tree node with right child.
         */
        template <class Comparable>
        void RedBlackTree<Comparable>::
        rotateWithRightChild( RedBlackNode<Comparable> * & k1 ) const
        {
            RedBlackNode<Comparable> *k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k1 = k2;
        }


        /**
         * Internal method to reclaim internal nodes
         * in subtree t.
         */
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

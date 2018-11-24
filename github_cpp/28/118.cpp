        #include "SplayTree.h"

        /**
         * Construct the tree.
         */
        template <class Comparable>
        SplayTree<Comparable>::SplayTree( const Comparable & notFound )
          : ITEM_NOT_FOUND( notFound )
        {
            nullNode = new SplayBinaryNode<Comparable>;
            nullNode->left = nullNode->right = nullNode;
            nullNode->element = notFound;
            root = nullNode;
        }

        /**
         * Copy constructor.
         */
        template <class Comparable>
        SplayTree<Comparable>::SplayTree( const SplayTree<Comparable> & rhs )
          : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
        {
            nullNode = new SplayBinaryNode<Comparable>;
            nullNode->left = nullNode->right = nullNode;
            nullNode->element = ITEM_NOT_FOUND;
            root = nullNode;
            *this = rhs;
        }

        /**
         * Destructor.
         */
        template <class Comparable>
        SplayTree<Comparable>::~SplayTree( )
        {
            makeEmpty( );
            delete nullNode;
        }

        /**
         * Insert x into the tree.
         */
        template <class Comparable>
        void SplayTree<Comparable>::insert( const Comparable & x )
        {
            static SplayBinaryNode<Comparable> *newNode = NULL;

            if( newNode == NULL )
                newNode = new SplayBinaryNode<Comparable>;
            newNode->element = x;

            if( root == nullNode )
            {
                newNode->left = newNode->right = nullNode;
                root = newNode;
            }
            else
            {
                splay( x, root );
                if( x < root->element )
                {
                    newNode->left = root->left;
                    newNode->right = root;
                    root->left = nullNode;
                    root = newNode;
                }
                else
                if( root->element < x )
                {
                    newNode->right = root->right;
                    newNode->left = root;
                    root->right = nullNode;
                    root = newNode;
                }
                else
                    return;
            }
            newNode = NULL;   // So next insert will call new
        }

        /**
         * Remove x from the tree.
         */
        template <class Comparable>
        void SplayTree<Comparable>::remove( const Comparable & x )
        {
            SplayBinaryNode<Comparable> *newTree;

                // If x is found, it will be at the root
            splay( x, root );
            if( root->element != x )
                return;   // Item not found; do nothing

            if( root->left == nullNode )
                newTree = root->right;
            else
            {
                // Find the maximum in the left subtree
                // Splay it to the root; and then attach right child
                newTree = root->left;
                splay( x, newTree );
                newTree->right = root->right;
            }
            delete root;
            root = newTree;
        }

        /**
         * Find the smallest item in the tree.
         * Not the most efficient implementation (uses two passes), but has correct
         *     amortized behavior.
         * A good alternative is to first call Find with parameter
         *     smaller than any item in the tree, then call findMin.
         * Return the smallest item or ITEM_NOT_FOUND if empty.
         */
        template <class Comparable>
        const Comparable & SplayTree<Comparable>::findMin( )
        {
            if( isEmpty( ) )
                return ITEM_NOT_FOUND;

            SplayBinaryNode<Comparable> *ptr = root;

            while( ptr->left != nullNode )
                ptr = ptr->left;

            splay( ptr->element, root );
            return ptr->element;
        }

        /**
         * Find the largest item in the tree.
         * Not the most efficient implementation (uses two passes), but has correct
         *     amortized behavior.
         * A good alternative is to first call Find with parameter
         *     larger than any item in the tree, then call findMax.
         * Return the largest item or ITEM_NOT_FOUND if empty.
         */
        template <class Comparable>
        const Comparable & SplayTree<Comparable>::findMax( )
        {
            if( isEmpty( ) )
                return ITEM_NOT_FOUND;

            SplayBinaryNode<Comparable> *ptr = root;

            while( ptr->right != nullNode )
                ptr = ptr->right;

            splay( ptr->element, root );
            return ptr->element;
        }

        /**
         * Find item x in the tree.
         * Return the matching item or ITEM_NOT_FOUND if not found.
         */
        template <class Comparable>
        const Comparable & SplayTree<Comparable>::find( const Comparable & x )
        {
            splay( x, root );
            if( root->element != x )
                return ITEM_NOT_FOUND;

            return root->element;
        }

        /**
         * Make the tree logically empty.
         */
        template <class Comparable>
        void SplayTree<Comparable>::makeEmpty( )
        {
        /******************************
         * Comment this out, because it is prone to excessive
         * recursion on degenerate trees. Use alternate algorithm.
         
            reclaimMemory( root );
            root = nullNode;
         *******************************/
            findMax( );        // Splay max item to root
            while( !isEmpty( ) )
                remove( root->element );
        }

        /**
         * Test if the tree is logically empty.
         * @return true if empty, false otherwise.
         */
        template <class Comparable>
        bool SplayTree<Comparable>::isEmpty( ) const
        {
            return root == nullNode;
        }

        /**
         * Print the tree contents in sorted order.
         */
        template <class Comparable>
        void SplayTree<Comparable>::printTree( ) const
        {
            if( isEmpty( ) )
                cout << "Empty tree" << endl;
            else
                printTree( root );
        }

        /**
         * Deep copy.
         */
        template <class Comparable>
        const SplayTree<Comparable> &
        SplayTree<Comparable>::operator=( const SplayTree<Comparable> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                root = clone( rhs.root );
            }

            return *this;
        }

        /**
         * Internal method to perform a top-down splay.
         * The last accessed node becomes the new root.
         * This method may be overridden to use a different
         * splaying algorithm, however, the splay tree code
         * depends on the accessed item going to the root.
         * x is the target item to splay around.
         * t is the root of the subtree to splay.
         */
        template <class Comparable>
        void SplayTree<Comparable>::splay( const Comparable & x,
                                           SplayBinaryNode<Comparable> * & t ) const
        {
            SplayBinaryNode<Comparable> *leftTreeMax, *rightTreeMin;
            static SplayBinaryNode<Comparable> header;

            header.left = header.right = nullNode;
            leftTreeMax = rightTreeMin = &header;

            nullNode->element = x;   // Guarantee a match

            for( ; ; )
                if( x < t->element )
                {
                    if( x < t->left->element )
                        rotateWithLeftChild( t );
                    if( t->left == nullNode )
                        break;
                    // Link Right
                    rightTreeMin->left = t;
                    rightTreeMin = t;
                    t = t->left;
                }
                else if( t->element < x )
                {
                    if( t->right->element < x )
                        rotateWithRightChild( t );
                    if( t->right == nullNode )
                        break;
                    // Link Left
                    leftTreeMax->right = t;
                    leftTreeMax = t;
                    t = t->right;
                }
                else
                    break;

            leftTreeMax->right = t->left;
            rightTreeMin->left = t->right;
            t->left = header.right;
            t->right = header.left;
        }

        /**
         * Rotate binary tree node with left child.
         */
        template <class Comparable>
        void SplayTree<Comparable>::rotateWithLeftChild( SplayBinaryNode<Comparable> * & k2 ) const
        {
            SplayBinaryNode<Comparable> *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2 = k1;
        }

        /**
         * Rotate binary tree node with right child.
         */
        template <class Comparable>
        void SplayTree<Comparable>::rotateWithRightChild( SplayBinaryNode<Comparable> * & k1 ) const
        {
            SplayBinaryNode<Comparable> *k2 = k1->right;
            k1->right = k2->left;
            k2->left = k1;
            k1 = k2;
        }

        /**
         * Internal method to print a subtree t in sorted order.
         * WARNING: This is prone to running out of stack space.
         */
        template <class Comparable>
        void SplayTree<Comparable>::printTree( SplayBinaryNode<Comparable> *t ) const
        {
            if( t != t->left )
            {
                printTree( t->left );
                cout << t->element << endl;
                printTree( t->right );
            }
        }

        /**
         * Internal method to reclaim internal nodes in subtree t.
         * WARNING: This is prone to running out of stack space.
         */
        template <class Comparable>
        void SplayTree<Comparable>::reclaimMemory( SplayBinaryNode<Comparable> * t ) const
        {
            if( t != t->left )
            {
                reclaimMemory( t->left );
                reclaimMemory( t->right );
                delete t;
            }
        }

        /**
         * Internal method to clone subtree.
         * WARNING: This is prone to running out of stack space.
         */
        template <class Comparable>
        SplayBinaryNode<Comparable> *
        SplayTree<Comparable>::clone( SplayBinaryNode<Comparable> * t ) const
        {
            if( t == t->left )  // Cannot test against nullNode!!!
                return nullNode;
            else
                return new SplayBinaryNode<Comparable>( t->element, clone( t->left ), clone( t->right ) );
        }

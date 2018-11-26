
#include <memory>
#include <iostream>

#pragma once

namespace NonStd {

    template < typename T >
    class RedBlackTree {

        struct TreeNode;

        typedef std::unique_ptr < TreeNode > uniqueTN;

        struct TreeNode {

            T data;
            bool is_red;
            uniqueTN left;
            uniqueTN right;
            TreeNode * parent;

            TreeNode ( T data ) : data ( data ), is_red ( true ) {};
            TreeNode (
                
                T data,
                uniqueTN & left,
                uniqueTN & right
                
            ) :
            data ( data ),
            is_red ( true ),
            left ( std::move ( left ) ),
            right ( std::move ( right ) ) {};

            void changeColor () { this -> is_red = ! this -> is_red; };

        };

        uniqueTN root;
        std::size_t length;

        void validateTree ();
        void validateTree ( TreeNode * node, const bool is_left );
        void rotate ( const T & data, uniqueTN & node );

        int validateBlackHeight ( TreeNode * node );
        bool validateParentChild ( TreeNode * node );
        void leftRotate ( TreeNode * node );
        void rightRotate ( TreeNode * node );
        bool search ( const T & data, const uniqueTN & node );

        public:

            RedBlackTree ( const T & data );
            // virtual ~RedBlackTree ();

            bool add ( const T & data );
            bool remove ( const T & data );
            bool find ( const T & data );

    };

};

#include "red_black_tree.cpp"
//
//  redblacktree.cpp
//  RedBlackTree
//
//  Created by Oriah Ulrich on 2/2/15.
//  Copyright (c) 2015 Oriah Ulrich. All rights reserved.
//

#include "redblacktree.h"


// Red Black Tree Public Definitions //
// _________________________________ //

namespace Structures {

    
    RedBlackTree::RedBlackTree() : BinaryTree::BinaryTree()
    {
        // this points to the current root of the tree
        m_root = 0;
        
        // this is used as a sentinel for leaf nodes, m_root's parent, and nil
        m_nil = new RedBlackNode( RedBlackNode::Black );
    }
    
    RedBlackTree::~RedBlackTree()
    {
        baseclass::~BinaryTree();
        delete m_nil;
        m_nil = NULL;
    }
    
    bool RedBlackTree::insert( Node* newNode )
    {
        if ( !baseclass::insert( newNode ) )
        {
            return false;
        }

        RedBlackNode* node = dynamic_cast<RedBlackNode*>( newNode );
        assert( node );
        
        node->setLeft( NULL );
        node->setRight( NULL );
        node->setColor( RedBlackNode::Red );
        
        return post_insert_fix_tree( node );
    }

    Node* RedBlackTree::find( int key )
    {
        return baseclass::find( key );
    }

    bool RedBlackTree::remove( int key )
    {
        /** Find the node to remove (based on key) */
        
        Node* nodeToRemove = baseclass::find( key );
        
        if ( !nodeToRemove )
        {
            return false; // not in tree
        }
        
        
        /** --- Pre Node Removal --- */
        
        BinaryNode::Direction dir = BinaryNode::None;
        RedBlackNode* parent = (RedBlackNode*) nodeToRemove->getParent();
        
        /* Figure out which node to get from the parent (left or right) 
           after the binary tree deletes the node (post removal). Since 
           we need to know where to start fixing */
        if ( parent )
        {
            if ( parent->left() == nodeToRemove )
            {
                dir = BinaryNode::Left;
            }
            else
            {
                dir = BinaryNode::Right;
            }
        }
        
        
        /** --- Node Removal --- */
        
        if ( !baseclass::remove( nodeToRemove, parent ) )
        {
            return false;
        }
        
        
        /** --- Post Node Removal --- */
        
        /* However if no parent existed then we must have deleted the root..
         in which case no fancy red black tree fixing is needed.. (parent is null) */
        if ( !parent )
        {
            return true;
        }
        
        /* After removal of node, then get the left or right child that 
         replaced the node we just deleted ( the left or right replacement ) */
        return post_remove_fix_tree( parent ); // or parent->get( dir )?
    }
    
} // namespace Structures


// Red Black Tree Internal Definitions //
// ___________________________________ //

namespace Structures {
    
    /** --- RB Tree Rotations --- */
    
    // _________________________________________________________________
    // rotates n (old parent node) with q ( the child node )..
    // q becomes the parent and n the child, n is the "dir-th" child of q
    // (For example, image this was rotate left and "dir" == left
    bool RedBlackTree::rotate( BinaryNode* n, BinaryNode::Direction dir )
    {
        if ( !n || !n->get( !dir ) )
        {
            return false;
        }
        
        Node* q = n->get( !dir );           // keep track before losing
        n->set( !dir, q->get( dir ) );      // assign the right of x to y's left
        
        if ( n->get( !dir ) )
        {
            n->get( !dir )->setParent( n ); // assign x's right's parent ptr to x
        }
        
        q->setParent( n->getParent() );     // set y's parent to x's parent
        
        /* Now we need to worry about the current parent of y (x's old parent)
         And assign that parent's left or right to y.. Although, the parent might
         be null, in which case the tree's root ptr will have to point to y */
        
        if ( !n->getParent() )              // check if nil
        {
            m_root = q;
        }
        else
        {
            /* Not null root then: set the parent's left or right
             depending on which left or right is pointing to x */
            BinaryNode* pParent = (BinaryNode*) n->getParent();
            if ( n == pParent->get( dir ) )
            {
                pParent->set( dir, q );
            }
            else if ( n == pParent->get( !dir ) )
            {
                pParent->set( !dir, q );
            }
            
        }
        
        q->set( dir, n );                   // set y's left to x
        n->setParent( q );                  // set x's parent to y
        
        return true;
    }
    
    // x is parent, y is right child. Make y the parent and x the left
    // child of y, where x will have y's old left child as it's right child
    bool RedBlackTree::rotate_left( BinaryNode* x )
    {
        return rotate( x, BinaryNode::Left );
    }
    
    // same as left rotation but with y's and x's roles "reversed"
    // , and ptrs swaps reversed as well
    bool RedBlackTree::rotate_right( BinaryNode* y )
    {
        return rotate( y, BinaryNode::Right );
    }
 
    
    bool RedBlackTree::fix( RedBlackNode* parent,
                            RedBlackNode* uncle,
                            RedBlackNode* node,
                            BinaryNode::Direction dir )
    {
        
#define RBN(x) ((RedBlackNode*)(x))
        const RedBlackNode::Color Red     = RedBlackNode::Red;
        const RedBlackNode::Color Black   = RedBlackNode::Black;
        const BinaryNode::Direction Left  = BinaryNode::Left;
        const BinaryNode::Direction Right = BinaryNode::Right;
        
        if ( uncle->is( Red ) )
        {
            uncle->setColor( Black );                   // make the uncle black
            RBN(node->getParent())->setColor( Black );  // node's parent is black
            node = RBN(node->getParent()->getParent()); // now select the parent of the parent
            node->setColor( Red );                      // and make it red
            std::cout << "Case: 1" << std::endl;
        }
        else
        {
            if ( node == node->getParent()->get( !dir ) )
            {   // check if sibling
                node = RBN(node->getParent());
                rotate( node, dir );
                std::cout << "Case: 2" << std::endl;
            }
            else
            {
                std::cout << "Case: 3" << std::endl;
            }
            RBN(node->getParent())->setColor( Black );
            RBN(node->getParent()->getParent())->setColor( Red );
            //                    rotate_right( RBN(node->getParent()->getParent()) );
            rotate( RBN(node->getParent()->getParent()), (dir == Left ? Right : Left) );
        }
#undef RBN
       
        return true;
    }
    
    /** --- RB Tree Fixups (Post insert && Post removal) --- */
    
    bool RedBlackTree::post_insert_fix_tree( RedBlackNode* node )
    {
        if ( !node )
        {
            // did not fix tree (in this case
            // it didnt need to since node was null)
            return false;
        }
        
        // local helpers for identifying rb_node color and node direction
        const RedBlackNode::Color Red     = RedBlackNode::Red;
        const RedBlackNode::Color Black   = RedBlackNode::Black;
        const BinaryNode::Direction Left  = BinaryNode::Left;
        const BinaryNode::Direction Right = BinaryNode::Right;
        
#define RBN(x) ((RedBlackNode*)(x))
        /* fixup the red black tree structure after an insert */
        while ( node->is( Red ) )
        {
            RedBlackNode* parent = RBN( OPTIONAL(node, getParent, getParent, get, Left) );
            RedBlackNode* uncle  = RBN( OPTIONAL(node, getParent, getParent, get, Right) );
            if ( parent && uncle && node->getParent() == parent )
            {
                std::cout << "Fix w/ Left Rotation" << std::endl;
                fix( parent, uncle, node, Left );
            }
            else
            {
                parent = RBN( OPTIONAL(node, getParent, getParent, get, Right) );
                uncle = RBN( OPTIONAL(node, getParent, getParent, get, Left) );
        
                if ( parent && uncle && node->getParent() == parent )
                {
                    std::cout << "Fix w/ Right Rotation" << std::endl;
                    fix( parent, uncle, node, Right );
                }
                else
                {
                    break;
                }
            }
        }
#undef RBN
        
        dynamic_cast<RedBlackNode*>(m_root)->setColor( Black );
        
        return true;
    }
    
    bool RedBlackTree::post_remove_fix_tree( RedBlackNode* node )
    {
        if ( !node )
        {
            return false;
        }
        
        /* TODO: fixup the red black tree structure */
        
        return true;
    }
    
} // namespace Structures

// end of file //


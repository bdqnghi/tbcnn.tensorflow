







#include "redblacktree.h"





namespace Structures {

    
    RedBlackTree::RedBlackTree() : BinaryTree::BinaryTree()
    {
        
        m_root = 0;
        
        
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
        
        
        Node* nodeToRemove = baseclass::find( key );
        
        if ( !nodeToRemove )
        {
            return false; 
        }
        
        
        
        
        BinaryNode::Direction dir = BinaryNode::None;
        RedBlackNode* parent = (RedBlackNode*) nodeToRemove->getParent();
        
        
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
        
        
        
        
        if ( !baseclass::remove( nodeToRemove, parent ) )
        {
            return false;
        }
        
        
        
        
        
        if ( !parent )
        {
            return true;
        }
        
        
        return post_remove_fix_tree( parent ); 
    }
    
} 





namespace Structures {
    
    
    
    
    
    
    
    bool RedBlackTree::rotate( BinaryNode* n, BinaryNode::Direction dir )
    {
        if ( !n || !n->get( !dir ) )
        {
            return false;
        }
        
        Node* q = n->get( !dir );           
        n->set( !dir, q->get( dir ) );      
        
        if ( n->get( !dir ) )
        {
            n->get( !dir )->setParent( n ); 
        }
        
        q->setParent( n->getParent() );     
        
        
        
        if ( !n->getParent() )              
        {
            m_root = q;
        }
        else
        {
            
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
        
        q->set( dir, n );                   
        n->setParent( q );                  
        
        return true;
    }
    
    
    
    bool RedBlackTree::rotate_left( BinaryNode* x )
    {
        return rotate( x, BinaryNode::Left );
    }
    
    
    
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
            uncle->setColor( Black );                   
            RBN(node->getParent())->setColor( Black );  
            node = RBN(node->getParent()->getParent()); 
            node->setColor( Red );                      
            std::cout << "Case: 1" << std::endl;
        }
        else
        {
            if ( node == node->getParent()->get( !dir ) )
            {   
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
            
            rotate( RBN(node->getParent()->getParent()), (dir == Left ? Right : Left) );
        }
#undef RBN
       
        return true;
    }
    
    
    
    bool RedBlackTree::post_insert_fix_tree( RedBlackNode* node )
    {
        if ( !node )
        {
            
            
            return false;
        }
        
        
        const RedBlackNode::Color Red     = RedBlackNode::Red;
        const RedBlackNode::Color Black   = RedBlackNode::Black;
        const BinaryNode::Direction Left  = BinaryNode::Left;
        const BinaryNode::Direction Right = BinaryNode::Right;
        
#define RBN(x) ((RedBlackNode*)(x))
        
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
        
        
        
        return true;
    }
    
} 




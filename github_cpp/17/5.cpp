








#if !defined( CHECKS_H )
#include <Checks.h>
#endif  

#if !defined( __BTREE_H )
#include <BTree.h>
#endif  

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif





void Btree::finishInit( int O )
{
    if( O < 3 )
        ClassLib_error( __EORDER3 );
    ownsElements( 0 );
    root = 0;
    Order = O;
    Order2 = 2 * (O+1);
    Leaf_MaxIndex = Order2 - 1;     
    Inner_MaxIndex = Order;         
    
    
    
    
    
    
    
    
    
    Leaf_LowWaterMark = ((Leaf_MaxIndex+1            
                                         )-1) / 2    
                                                  - 1; 
                                                     

    Inner_LowWaterMark = (Order-1) / 2;
}

Btree::Btree(int O) : itemsInContainer(0)
{
    finishInit(O);
}

Btree::~Btree(void)
{
    if( root != 0 )
        delete root;
}

void Btree::flush( DeleteType dt )
{
    int oldValue = ownsElements();
    ownsElements( delObj(dt) );
    if( root != 0 )
        delete root;
    itemsInContainer = 0;
    root = 0;
    ownsElements( oldValue );
}

int Btree::hasMember( Object& o ) const
{
    if( !o.isSortable() )
        ClassLib_error( __ENOTSORT );
    if( root == 0 )
        return 0;
    else
        {
        Node* loc;
        int idx;
        return root->found(&(Sortable&)o, &loc, &idx) != NOOBJECT;
        }
}

long Btree::rank( const Object& o ) const
{
    if( !o.isSortable() )
        ClassLib_error( __ENOTSORT );
    if( root == 0 )
        return -1;
    else
        return root->findRank(&(Sortable&)o);
}

Object& Btree::findMember( Object& o ) const
{
    if( !o.isSortable() )
        ClassLib_error(__ENOTSORT);
    if( root == 0 )
        return NOOBJECT;
    else
        {
        Node* loc;
        int idx;
        return root->found(&(Sortable&)o, &loc, &idx);
        }
}

void Btree::printOn( ostream& out ) const
{
    if( root == 0 )
        out << "<empty>" ;
    else
        root->printOn(out);
}

extern "C" void __ErrorMessage( const char * );

int Btree::isEqual( const Object& obj ) const
{
    if( obj.isA() == btreeClass )
        {
        __ErrorMessage( "Btree isEqual not implemented\n" );
        exit(1);
        }
    return 0;

    
    
    
}


long Btree::i_add( const Object& o )
{
    long r;
    if( !o.isSortable() )
        ClassLib_error( __ENOTSORT );
    if( root == 0 )
        {
        root = new LeafNode( 0, &(Sortable&)o, this );
        CHECK( root != 0 );
        incrNofKeys();
        r = 0;
        }
    else
        {
        Node* loc;
        int idx;
        if( root->found(&(Sortable&)o, &loc, &idx) != NOOBJECT )
            {
            
            
            
            
            
            
            }
        else
            {
            CHECK( loc->isLeaf );
            }
        if( loc->isLeaf )
            {
            if( loc->parent == 0 )
                r = idx;
            else
                r = idx + loc->parent->findRank_bu( loc );
            }
        else
            {
            InnerNode *iloc = (InnerNode*)loc;
            r = iloc->findRank_bu( iloc->getTree( idx ) );
            }
        loc->add( &(Sortable&)o, idx );
        }
    CHECK( r == rank( (Sortable&)o ) || (Sortable&)o == (*this)[r] );
    return r;
}

void Btree::add( Object& o )
{
    if( !o.isSortable() )
        ClassLib_error( __ENOTSORT );
    if (root == 0)
        {
        root = new LeafNode( 0, &(Sortable&)o, this );
        CHECK( root != 0 );
        incrNofKeys();
        }
    else
        {
        Node* loc;
        int idx;
        if( root->found(&(Sortable&)o, &loc, &idx) != NOOBJECT )
            {
            
            
            
            
            
            }
        loc->add( &(Sortable&)o, idx );
        }
}

void Btree::detach( Object& o, DeleteType dt )
{
    if( !o.isSortable() )
        ClassLib_error(__ENOTSORT);
    if( root == 0 )
        return;

    Node* loc;
    int idx;
    Object* obj = &(root->found( &(Sortable&)o, &loc, &idx ));
    if( *obj == NOOBJECT )
        return;
    loc->remove( idx );
    if( delObj(dt) )
        delete obj;
}

void Btree::rootIsFull()
{
    
    
    Node* oldroot = root;
    root = new InnerNode( 0, this, oldroot );
    CHECK( root != 0 );
    oldroot->split();
}

void Btree::rootIsEmpty()
{
    if( root->isLeaf )
        {
        LeafNode* lroot = (LeafNode*)root;
        CHECK( lroot->Psize() == 0 );
        delete lroot;
        root = 0;
        }
    else {
        InnerNode* iroot = (InnerNode*)root;
        CHECK(iroot->Psize() == 0);
        root = iroot->getTree(0);
        root->parent = 0;
        delete iroot;
        }
}

Item::Item()
{
    nofKeysInTree = 0;
    tree = 0;
    key = 0;
}

Item::Item(Node* n, Sortable* o)
{
    nofKeysInTree = n->nofKeys()+1;
    tree = n;
    key = o;
}

Item::Item(Sortable* o, Node* n)
{
    nofKeysInTree = n->nofKeys()+1;
    tree = n;
    key = o;
}

Item::~Item()
{
}





Node::Node(int isleaf, InnerNode* P, Btree* T)
{
    
    last = -1;
    debugKey = 1017; 
    isLeaf = isleaf;
    parent = P;
    if( P == 0 )
        {
        CHECK( T != 0 );
        tree = T;
        }
    else
        tree = P->tree;
}

Node::~Node()
{
}





void BtreeIterator::restart()
{
    index = 0;
}

Object& BtreeIterator::operator++()
{
    return beingIterated[++index];
}

Object& BtreeIterator::operator++( int )
{
    return beingIterated[index++];
}

Object& BtreeIterator::current()
{
    return beingIterated[index];
}


ContainerIterator&
Btree::initIterator() const
{
    return *( (ContainerIterator *)new BtreeIterator( *this ) );
}

BtreeIterator::~BtreeIterator()
{
}


BtreeIterator::operator int()
{
    return index < beingIterated.getItemsInContainer();
}

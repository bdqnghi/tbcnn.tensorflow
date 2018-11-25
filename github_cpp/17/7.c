#include "btree.h"


BTreeNode::BTreeNode( int t1, bool leaf1 )
{
    
    t = t1;
    leaf = leaf1;

    
    
    keys = new int[2 * t - 1];
    C = new BTreeNode * [2 * t];
    posicion = new int[2*t-1];
    length = new int[2*t-1];

    
    n = 0;
}

BTreeNode::~BTreeNode()
{
    delete [] keys;
    for( int i = 0; i < t * 2; i++)
        delete [] C[i];
      delete [] C;
    delete [] posicion;
    delete [] length;
}


BTreeNode *BTreeNode::search( int k )
{
    
    int i = 0;
    while ( i < n && k > keys[i] )
        i++;

    
    if ( keys[i] == k )
    {
        this->x = i;
        return this;
    }
    
    if ( leaf == true )
        return NULL;

    
    return C[i]->search( k );
}


void BTree::insert( int k, int p, int l )
{
    
    if ( root == NULL )
    {
        
        root = new BTreeNode( t, true );
        root->keys[0] = k;  
        root->posicion[0] = p; 
        root->length[0] = l; 
        root->n = 1;  
    }
    else 
    {
        
        if ( root->n == 2 * t - 1 )
        {
            
            BTreeNode *s = new BTreeNode( t, false );

            
            s->C[0] = root;

            
            s->splitChild( 0, root );

            
            
            int i = 0;
            if ( s->keys[0] < k )
                i++;
            s->C[i]->insertNonFull( k, p, l );

            
            root = s;
        }
        else  
            root->insertNonFull( k, p, l );
    }
}




void BTreeNode::insertNonFull( int k, int p, int l )
{
    
    int i = n - 1;

    
    if ( leaf == true )
    {
        
        
        
        while ( i >= 0 && keys[i] > k )
        {
            keys[i + 1] = keys[i];
            posicion[i + 1] = posicion[i];
            length[i + 1] = length[i];
            i--;
        }

        
        keys[i + 1] = k;
        posicion[i + 1] = p;
        length[i + 1] = l;
        n = n + 1;
    }
    else 
    {
        
        while ( i >= 0 && keys[i] > k )
            i--;

        
        if ( C[i + 1]->n == 2 * t - 1 )
        {
            
            splitChild( i + 1, C[i + 1] );

            
            
            
            if ( keys[i + 1] < k )
                i++;
        }
        C[i + 1]->insertNonFull( k, p, l );
    }
}



void BTreeNode::splitChild(int i, BTreeNode *y)
{
    
    
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    
    for (int j = 0; j < t - 1; j++)
    {    z->keys[j] = y->keys[j + t];
         z->posicion[j] = y->posicion[j + t];
         z->length[j] = y->length[j + t];
    }
    
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];

    }

    
    y->n = t - 1;

    
    
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    
    C[i + 1] = z;

    
    
    for (int j = n - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];
        posicion[j + 1] = posicion[j];
        length[j + 1] = length[j];
    }

    
    keys[i] = y->keys[t - 1];
    posicion[i] = y->posicion[t - 1];
    length[i] = y->length[t - 1];

    
    n = n + 1;
}


void BTreeNode::traverse()
{

    
    
    int i;
    for (i = 0; i < n; i++)
    {
        
        
        if (leaf == false)
            C[i]->traverse();
    }

    
    if (leaf == false)
        C[i]->traverse();
}



#include "btree.h"

// Constructor for BTreeNode class
BTreeNode::BTreeNode( int t1, bool leaf1 )
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2 * t - 1];
    C = new BTreeNode * [2 * t];
    posicion = new int[2*t-1];
    length = new int[2*t-1];

    // Initialize the number of keys as 0
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

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search( int k )
{
    // Find the first key greater than or equal to k
    int i = 0;
    while ( i < n && k > keys[i] )
        i++;

    // If the found key is equal to k, return this node
    if ( keys[i] == k )
    {
        this->x = i;
        return this;
    }
    // If key is not found here and this is a leaf node
    if ( leaf == true )
        return NULL;

    // Go to the appropriate child
    return C[i]->search( k );
}

// The main function that inserts a new key in this B-Tree
void BTree::insert( int k, int p, int l )
{
    // If tree is empty
    if ( root == NULL )
    {
        // Allocate memory for root
        root = new BTreeNode( t, true );
        root->keys[0] = k;  // Insert key
        root->posicion[0] = p; // Insert posicion
        root->length[0] = l; // Insert length
        root->n = 1;  // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if ( root->n == 2 * t - 1 )
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode( t, false );

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild( 0, root );

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if ( s->keys[0] < k )
                i++;
            s->C[i]->insertNonFull( k, p, l );

            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull( k, p, l );
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull( int k, int p, int l )
{
    // Initialize index as index of rightmost element
    int i = n - 1;

    // If this is a leaf node
    if ( leaf == true )
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while ( i >= 0 && keys[i] > k )
        {
            keys[i + 1] = keys[i];
            posicion[i + 1] = posicion[i];
            length[i + 1] = length[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = k;
        posicion[i + 1] = p;
        length[i + 1] = l;
        n = n + 1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while ( i >= 0 && keys[i] > k )
            i--;

        // See if the found child is full
        if ( C[i + 1]->n == 2 * t - 1 )
        {
            // If the child is full, then split it
            splitChild( i + 1, C[i + 1] );

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if ( keys[i + 1] < k )
                i++;
        }
        C[i + 1]->insertNonFull( k, p, l );
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
    {    z->keys[j] = y->keys[j + t];
         z->posicion[j] = y->posicion[j + t];
         z->length[j] = y->length[j + t];
    }
    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];

    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    // Link the new child to this node
    C[i + 1] = z;

    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = n - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];
        posicion[j + 1] = posicion[j];
        length[j + 1] = length[j];
    }

    // Copy the middle key of y to this node
    keys[i] = y->keys[t - 1];
    posicion[i] = y->posicion[t - 1];
    length[i] = y->length[t - 1];

    // Increment count of keys in this node
    n = n + 1;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{

    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}



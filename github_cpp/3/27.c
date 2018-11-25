




#include "avltree.h"

AvlTree::AvlTree( const string & notFound )
    : ITEM_NOT_FOUND( notFound ), root( NULL ) {
    SingleRotations = 0;
    DoubleRotations = 0;
    RightLinksFollowed = 0;
    LeftLinksFollowed = 0;
    num_nodes = 0;
}


AvlTree::AvlTree( const AvlTree & rhs )
    : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ), root( NULL ) {
    *this = rhs;
}


AvlTree::~AvlTree( ) {
    makeEmpty( );
}



int AvlTree::GetLeftLinksFollowed( ) const {
    return LeftLinksFollowed;
}


int AvlTree::GetDoubleRotations( ) const {
    return DoubleRotations;
}

int AvlTree::GetSingleRotations( ) const {
    return SingleRotations;
}


int AvlTree::GetRightLinksFollowed( ) const {
    return RightLinksFollowed;
}


int AvlTree::card_of( ) const {
    return num_nodes;
}



void AvlTree::insert( const string & x ) {
    insert( x, root );
    num_nodes++;

}


void AvlTree::remove( const string & x ) {
    cout << "Sorry, remove unimplemented; " << x <<
         " still present" << endl;

    num_nodes--;
   

}


const string & AvlTree::findMin( ) const {
    return elementAt( findMin( root ) );
}


const string & AvlTree::findMax( ) const {
    return elementAt( findMax( root ) );
}


const string & AvlTree::
find( const string & x ) const {
    return elementAt( find( x, root ) );
}


void AvlTree::makeEmpty( ) {
    makeEmpty( root );
}


bool AvlTree::isEmpty( ) const {
    return root == NULL;
}


void AvlTree::printTree( ) const {
    if ( isEmpty( ) )
        cout << "Empty tree" << endl;
    else
        printTree( root );
}


const AvlTree &
AvlTree::
operator=( const AvlTree & rhs ) {
    if ( this != &rhs ) {
        makeEmpty( );
        root = clone( rhs.root );
    }
 
    return *this;

}

int AvlTree::int_path_length(AvlNode *t, int depth) {
 
  if(t==NULL) return 0;

  return depth + int_path_length(t->left, depth +1)+ int_path_length(t->right, depth+1);

}

double AvlTree:: exp_path_length(){
  double temp = int_path_length(root, 0);
  return (temp/num_nodes) ;
}



const string & AvlTree::elementAt( AvlNode *t ) const {
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}


void AvlTree::insert( const string & x, AvlNode * & t ) const {
    if ( t == NULL ) {
        t = new AvlNode( x, NULL, NULL );
    } else if ( x < t->element ) {
        insert( x, t->left );
        if ( height( t->left ) - height( t->right ) == 2 ) {
            if ( x < t->left->element ) {
                rotateWithLeftChild( t );
            } else {
                doubleWithLeftChild( t );
            }
        }
    } else if ( t->element < x ) {
        insert( x, t->right );
        if ( height( t->right ) - height( t->left ) == 2 ) {
            if ( t->right->element < x ) {
                rotateWithRightChild( t );
            } else {
                doubleWithRightChild( t );
            }
        }
    } else
        ;  
    t->height = max( height( t->left ), height( t->right ) ) + 1;
}


AvlNode *
AvlTree::findMin( AvlNode *t ) const {
    if ( t == NULL)
        return t;
    while ( t->left != NULL )
        t = t->left;
    return t;
}


AvlNode *
AvlTree::findMax( AvlNode *t ) const {
    if ( t == NULL )
        return t;
    while ( t->right != NULL )
        t = t->right;
    return t;
}


AvlNode *
AvlTree::find( const string & x, AvlNode *t ) const {
    while ( t != NULL )
        if ( x < t->element ) {
            t = t->left;
	    LeftLinksFollowed ++;
        } else if ( t->element < x ) {
            t = t->right;
	    RightLinksFollowed++;
        } else
            return t;    
    return NULL;   
}


void AvlTree::makeEmpty( AvlNode * & t ) const {
    if ( t != NULL ) {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
    num_nodes =0;
}


AvlNode *
AvlTree::clone( AvlNode * t ) const {
    if ( t == NULL )
        return NULL;
    else
        return new AvlNode( t->element, clone( t->left ),
                            clone( t->right ), t->height );
}


int AvlTree::height( AvlNode *t ) const {
    return t == NULL ? -1 : t->height;
}


int AvlTree::max( int lhs, int rhs ) const {
    return lhs > rhs ? lhs : rhs;
}


void AvlTree::rotateWithLeftChild( AvlNode * & k2 ) const {
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
    SingleRotations++;
}


void AvlTree::rotateWithRightChild( AvlNode * & k1 ) const {
    AvlNode * k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
  SingleRotations ++;
}


void AvlTree::doubleWithLeftChild( AvlNode * & k3 ) const {
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
    DoubleRotations++;
    SingleRotations -= 2;
}


void AvlTree::doubleWithRightChild( AvlNode * & k1 ) const {
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
    DoubleRotations++;
    SingleRotations -= 2;
}


void AvlTree::printTree( AvlNode *t ) const {
    if ( t != NULL ) {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}

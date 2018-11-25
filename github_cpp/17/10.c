#include "B-tree.h"
#include <malloc.h>
#include <stdio.h>

struct ParentWithChild{   
    Node *children;       
    Node *parent;         
    int position;         
};

void swap                     ( int *, int * );                                                        
Node* initNode                ( int levelTree );                                                       
void insertKeyIntoNode        ( Node *, int levelTree, int newKey, string  *newStr );                                   
void splitNode                ( Node *, int levelTree, int position );                                 
bool mergeNodes               ( Node *, int levelTree, int positionFirst, int positionSecond );        
void destroyNode              ( Node *, int levelTree );                                                              
bool deleteKeyFromLeaf        ( Node *, int levelTree, int positionKey );                              
ParentWithChild findKeyInTree ( Tree *, int findKey );                                                 
ParentWithChild findKeyInNode ( Node *, Node *, int findKey, int positionNode );                       
int positionKeyInNode         ( Node *, int findKey);                                                  
ParentWithChild findLeft      ( Node * );                                                              
ParentWithChild findRight     ( Node * );                                                              
void replaceKeyToLeft         ( Node *, Node *, Node *, int position);                                 
void replaceKeyToRight        ( Node *, Node *, Node *, int position);                                 
bool deleteKeyFromNode        ( Node *, int levelTree, int deleteKey, int deletePosition );            

Tree* initTree ( int levelTree )
{
    

    Tree *temp  = ( Tree * )malloc( sizeof( Tree ) );

    temp->level = levelTree;
    temp->root  = initNode( levelTree );

    return temp;
}

Node* initNode ( int levelTree )
{
    

    Node* temp    = ( Node * )malloc( sizeof( Node ) );

    temp->leaf    = true;
    temp->counter = 0;
    temp->key     = ( int * )malloc( ( 2 * levelTree - 1 ) * sizeof( int ) );
    temp->child   = ( Node ** )malloc( 2 * levelTree * sizeof( Node * ) );
    temp->str     = strMasCreate( 2 *  levelTree - 1 );

    return temp;
}

void insertKeyIntoTree ( Tree *currentTree, int newKey, string *newStr )
{
    

    Node* tempRoot = currentTree->root;

    if ( tempRoot->counter == 2 * currentTree->level - 1 ){

        Node *newRoot = initNode( currentTree->level );

        newRoot->leaf     = false;
        currentTree->root = newRoot;
        newRoot->child[0] = tempRoot;

        splitNode( newRoot, currentTree->level, 0 );

        insertKeyIntoNode( newRoot, currentTree->level, newKey, newStr );
    }
    else{

        insertKeyIntoNode( tempRoot, currentTree->level, newKey, newStr );
    }
}

void insertKeyIntoNode ( Node *currentNode, int levelTree, int newKey, string *newStr )
{
    

    int pos = currentNode->counter - 1;

    if ( currentNode->leaf ){

        while ( ( pos >= 0 ) && ( newKey < currentNode->key[ pos ] ) ){

            currentNode->key[ pos + 1 ] = currentNode->key[ pos ];
            strCopy( currentNode->str[ pos ], currentNode->str[ pos + 1 ] );
            pos -= 1;
        }

        currentNode->key[ pos + 1 ] = newKey;
        strCopy( newStr, currentNode->str[ pos + 1 ] );

        currentNode->counter += 1;
    }
    else{

        while ( ( pos >= 0 ) && ( newKey < currentNode->key[ pos ] ) ){

            pos -= 1;
        }

        pos += 1;

        if ( currentNode->child[ pos ]->counter == 2 * levelTree - 1 ){

            if ( currentNode->child[ pos ]->leaf )
                splitNode( currentNode, levelTree, pos );
            else
                splitNode( currentNode, levelTree, ( 2 * levelTree - 1 ) / 2  );

            
            if ( newKey > currentNode->key[ pos ] ) {

                pos += 1;
            }
        }

        insertKeyIntoNode( currentNode->child[ pos ], levelTree, newKey, newStr );
        if ( currentNode->child[ pos ]->counter > 2 * levelTree - 1 )
            splitNode( currentNode, levelTree, pos );

    }
}

void splitNode ( Node *currentNode, int levelTree, int position )
{
    

    Node *firstPart;
    Node *secondPart;

    firstPart  = currentNode->child[ position ];

    secondPart          = initNode( levelTree );
    secondPart->leaf    = firstPart->leaf;
    secondPart->counter = levelTree - 1;

    for ( int j = 0; j < levelTree - 1; j++ ){

        secondPart->key[ j ] = firstPart->key[ j + levelTree ];
        strCopy( firstPart->str[ j + levelTree ], secondPart->str[ j ] );
    }

    if ( !secondPart->leaf ){

        for ( int j = 0; j < levelTree; j++ ){

            secondPart->child[ j ] = firstPart->child[ j + levelTree ];
        }
    }

    firstPart->counter = levelTree;
    firstPart->child[ levelTree ] = secondPart;

    for ( int j = currentNode->counter + 1; j >= position + 1; j-- ){

        currentNode->child[ j + 1 ] = currentNode->child[ j ];
    }

    currentNode->child[ position + 1 ] = secondPart;

    for ( int j = currentNode->counter; j >= position; j-- ){

        currentNode->key[ j + 1 ] = currentNode->key[ j ];

    }

    currentNode->key[ position ] = firstPart->key[ levelTree ];
    strDestroy( currentNode->str[ position ] );
    currentNode->str[ position ] = strCreate();

    currentNode->counter += 1;
}

bool mergeNodes ( Node *currentNode, int levelTree, int positionFirst, int positionSecond )
{
    

    if ( positionFirst < 0 || positionFirst > currentNode->counter ) {

        return false;
    }

    if ( positionSecond < 0 || positionSecond > currentNode->counter ) {

        return false;
    }

    if ( positionFirst > positionSecond ) {

        swap( &positionFirst, &positionSecond );
    }

    Node *firstNode  = currentNode->child[ positionFirst ];
    Node *secondNode = currentNode->child[ positionSecond ];



    if ( ( firstNode->counter + secondNode->counter + 1 ) > ( 2 * levelTree - 1 ) ){

        return false;
    }

    
    

    for ( int i = 0; i < secondNode->counter; i++ ){

        firstNode->key[ i + firstNode->counter ] = secondNode->key[ i ];
        strCopy( secondNode->str[ i ], firstNode->str[ i + firstNode->counter ] );
    }
    for ( int i = 0; i <= secondNode->counter; i++ ){

        firstNode->child[ i + firstNode->counter ] = secondNode->child[ i ];
    }

    firstNode->counter += secondNode->counter;

    destroyNode( secondNode, levelTree );


    if ( currentNode->counter != 1 ){

        for ( int i = positionFirst; i < currentNode->counter - 1; i++ ) {

            currentNode->key[ i ] = currentNode->key[ i + 1 ];
        }

        for ( int i = positionFirst + 1; i < currentNode->counter; i++ ) {

            currentNode->child[ i ] = currentNode->child[ i + 1 ];
        }

        currentNode->counter -= 1;
    }
    else{

        currentNode->counter = firstNode->counter;
        currentNode->leaf    = firstNode->leaf;

        for ( int i = 0; i < currentNode->counter; i++ ) {

            currentNode->key[ i ] = firstNode->key[ i ];
            strCopy( firstNode->str[ i ], currentNode->str[ i ] );
        }

        for ( int i = 0; i <= currentNode->counter; i++ ) {

            currentNode->child[ i ] = firstNode->child[ i ];
        }

        destroyNode( firstNode, levelTree );
    }

    return true;
}

ParentWithChild findKeyInTree ( Tree *currentTree, int findKey )
{
    

    return findKeyInNode ( currentTree->root, currentTree->root, findKey, 0 );
}

ParentWithChild findKeyInNode ( Node *childNode, Node *parentNode, int findKey, int positionNode )
{
    

    
    int positionKey = positionKeyInNode( childNode, findKey );

    if ( positionKey == -1 && childNode->leaf ){

        ParentWithChild temp;

        temp.children = NULL;
        temp.parent   = NULL;
        temp.position = -1;

        return temp;
    }

    if ( positionKey != -1 ){

        ParentWithChild temp;

        temp.children = childNode;
        temp.parent   = parentNode;
        temp.position = positionNode;

        return temp;
    }
    for (int i = 1; i < childNode->counter; i++) {

        if (childNode->key[i - 1] > findKey) {

            return findKeyInNode(childNode->child[i - 1], childNode, findKey, i - 1);
        }
    }

    if ( childNode == parentNode ) {
        if (childNode->key[childNode->counter - 1] > findKey) {

            return findKeyInNode(childNode->child[childNode->counter - 1], childNode, findKey, childNode->counter - 1);
        }

    }

    return findKeyInNode( childNode->child[ childNode->counter ], childNode, findKey, childNode->counter );
}

int positionKeyInNode ( Node *currentNode, int findKey )
{
    

    if ( !currentNode->leaf )
        return -1;

    for ( int i = 0; i < currentNode->counter; i++ ) {

        if ( currentNode->key[ i ] == findKey ) {

            return i;
        }
    }

    return -1;
}

bool deleteKeyFromTree ( Tree *currentTree, int deleteKey )
{
    

    if ( currentTree == NULL || currentTree->root->counter == 0 ){

        printf("%s\n", "Tree is empty.");

        return 0;
    }

    ParentWithChild temp = findKeyInTree( currentTree, deleteKey );

    if ( temp.position == -1 ){

        printf( "%s\n", "Key don't find in Tree" );

        return 0;
    }

    if ( temp.children == currentTree->root && temp.children->leaf ){

        int pos = positionKeyInNode( temp.children, deleteKey );

        for ( int i = pos; i < temp.children->counter - 1; i++ ){
            temp.children->key[ i ] = temp.children->key[ i + 1 ];
        }


        for ( int i = pos; i <= temp.children->counter - 1; i++ ){
            temp.children->child[ i ] = temp.children->child[ i + 1 ];
        }

        temp.children->counter -= 1;

        return 1;
    }

    if ( temp.children->leaf ){

        if ( temp.children->counter > currentTree->level - 1 ) {

            int pos = positionKeyInNode( temp.children, deleteKey );

            return deleteKeyFromLeaf( temp.children, currentTree->level, pos );
        }
        else {

            if ( temp.position == temp.parent->counter ) {

                if ( temp.parent->child[ temp.position - 1 ]->counter > currentTree->level - 1 ){

                    replaceKeyToRight( temp.parent, temp.parent->child[ temp.position - 1 ], temp.children, temp.position - 1 );

                    int pos = positionKeyInNode( temp.parent->child[ temp.position ], deleteKey );

                    return deleteKeyFromLeaf( temp.parent->child[ temp.position ], currentTree->level, pos );
                }
                else{

                    mergeNodes( temp.parent, currentTree->level, temp.position, temp.position - 1 );

                    if ( temp.parent->leaf ){

                        int pos = positionKeyInNode( temp.parent, deleteKey );

                        return deleteKeyFromLeaf( temp.parent, currentTree->level, pos );
                    }
                    else {

                        int pos = positionKeyInNode(temp.parent->child[temp.position - 1], deleteKey);

                        return deleteKeyFromLeaf(temp.parent->child[temp.position - 1], currentTree->level, pos);
                    }
                }

            }
            else {

                if ( temp.parent->child[ temp.position + 1 ]->counter > currentTree->level - 1 ) {

                    replaceKeyToLeft( temp.parent, temp.children, temp.parent->child[ temp.position + 1 ], temp.position);

                    int pos = positionKeyInNode(temp.children, deleteKey);

                    return deleteKeyFromLeaf(temp.children, currentTree->level, pos);
                }
                else {

                    mergeNodes(temp.parent, currentTree->level, temp.position, temp.position + 1);

                    if ( temp.parent->leaf ){

                        int pos = positionKeyInNode( temp.parent, deleteKey );

                        return deleteKeyFromLeaf( temp.parent, currentTree->level, pos );
                    }
                    else {

                        int pos = positionKeyInNode(temp.children, deleteKey);

                        return deleteKeyFromLeaf(temp.children, currentTree->level, pos);
                    }
                }
            }
        }
    }
    else {

        int pos = positionKeyInNode(temp.children, deleteKey);

        return deleteKeyFromNode( temp.children, currentTree->level, deleteKey , pos );
    }
}

void swap (int *x, int *y)
{
    

    int t = *x;
    *x = *y;
    *y = t;
}

ParentWithChild findLeft ( Node *childNode)
{
    

    if ( childNode->child[ 0 ]->leaf ){

        ParentWithChild temp;

        temp.parent   = childNode;
        temp.children = childNode->child[ 0 ];
        temp.position = 0;

        return temp;
    }

    return findLeft( childNode->child[ 0 ] );
}

ParentWithChild findRight ( Node *childNode)
{
    

    if ( childNode->child[ childNode->counter ]->leaf ){

        ParentWithChild temp;

        temp.parent = childNode;
        temp.children = childNode->child[ childNode->counter ];
        temp.position = childNode->counter;

        return temp;
    }

    return findRight( childNode->child[ childNode->counter ] );
}

bool deleteKeyFromNode ( Node *currentNode, int levelTree, int deleteKey, int deletePosition ){
    

    if ( currentNode->leaf ){

        return deleteKeyFromLeaf( currentNode, levelTree, deletePosition );
    }

    ParentWithChild Left;
    if ( currentNode->child[ deletePosition + 1 ]->leaf){

        Left.parent   = currentNode;
        Left.children = currentNode->child[ deletePosition + 1 ];
        Left.position = deletePosition + 1;
    }
    else{

        findLeft( currentNode->child[ deletePosition + 1 ] );
    }

    ParentWithChild Right;
    if ( currentNode->child[ deletePosition ]->leaf ){

        Right.parent   = currentNode;
        Right.children = currentNode->child[ deletePosition ];
        Right.position = deletePosition;
    }
    else{

        findRight( currentNode->child[ deletePosition ] );
    }

    if ( Left.children->counter > levelTree - 1 ){

        swap( &currentNode->key[ deletePosition ], &Left.children->key[ 0 ] );

        return deleteKeyFromNode( Left.children, levelTree, deleteKey, 0 );
    }
    else{
        if ( Right.children->counter > levelTree - 1 ){

            swap( &currentNode->key[ deletePosition ], &Right.children->key[ Right.children->counter - 1 ] );

            return deleteKeyFromNode( Right.children, levelTree, deleteKey, Right.children->counter - 1 );
        }
        else{
            if ( Right.parent->child[ Right.position + 1 ]->counter > levelTree - 1 ){

                swap( &currentNode->key[ deletePosition ], &Right.parent->key[ Right.position ] );
                replaceKeyToLeft( Right.parent, Right.children, Right.parent->child[ Right.position + 1 ], Right.position );

                int temp = positionKeyInNode( Right.children, deleteKey );

                return deleteKeyFromNode( Right.children, levelTree, deleteKey, temp );
            }
            else{

                swap( &currentNode->key[ deletePosition ], &Right.parent->key[ Right.position ] );

                mergeNodes( Right.parent, levelTree, Right.position, Right.position + 1 );

                if ( Right.parent->leaf ) {

                    int temp = positionKeyInNode( Right.parent, deleteKey );

                    return deleteKeyFromNode( Right.parent, levelTree, deleteKey, temp );
                }
                else{

                    int temp = positionKeyInNode( Right.children, deleteKey );

                    return deleteKeyFromNode( Right.children, levelTree, deleteKey, temp );
                }
            }
        }
    }
}

void replaceKeyToLeft( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position)
{
    

    leftChildNode->counter += 1;

    leftChildNode->key[ leftChildNode->counter - 1 ] = rightChildNode->key[ 0 ];
    strCopy( rightChildNode->str[0], leftChildNode->str[ leftChildNode->counter - 1 ] );
    leftChildNode->child[ leftChildNode->counter - 1 ]   =  rightChildNode->child[ 0 ];
    leftChildNode->child[ leftChildNode->counter ] = rightChildNode;

    parentNode->key[ position ] = rightChildNode->key[ 1 ];

    for ( int i = 0; i <= rightChildNode->counter; i++ ){

        rightChildNode->child[ i ] = rightChildNode->child[ i + 1 ];
    }

    for ( int i = 0; i < rightChildNode->counter; i++ ){

        rightChildNode->key[ i ] = rightChildNode->key[ i + 1 ];
        strCopy( rightChildNode->str[ i + 1 ], rightChildNode->str[ i ] );
    }

    rightChildNode->counter -= 1;
}

void replaceKeyToRight( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position)
{
    

    for ( int i = rightChildNode->counter; i > 0; i-- ){

        rightChildNode->key[ i ] = rightChildNode->key[i - 1];
    }

    for ( int i = rightChildNode->counter + 1; i > 0; i-- ){

        rightChildNode->child[ i ] = rightChildNode->child[i - 1];
    }

    rightChildNode->counter += 1;

    rightChildNode->key[ 0 ]   = leftChildNode->key[ leftChildNode->counter - 1 ];
    rightChildNode->child[ 0 ] = leftChildNode->child[ leftChildNode->counter - 1 ];
    rightChildNode->str[ 0 ]   = rightChildNode->str[ leftChildNode->counter - 1 ];

    parentNode->key[ position ] = rightChildNode->key[ 0 ];

    leftChildNode->counter -= 1;
    leftChildNode->child[ leftChildNode->counter ] = rightChildNode;
}

bool deleteKeyFromLeaf ( Node *nodeIsLeaf, int levelTree, int positionKey )
{
    

    if ( nodeIsLeaf->counter == levelTree - 1 ) {

        return false;
    }

    for ( int i = positionKey; i < nodeIsLeaf->counter - 1; i++){

        nodeIsLeaf->key[ i ] = nodeIsLeaf->key[ i + 1 ];
        strCopy( nodeIsLeaf->str[ i + 1 ], nodeIsLeaf->str[ i ] );
    }

    for ( int i = positionKey; i < nodeIsLeaf->counter; i++){

        nodeIsLeaf->child[ i ] = nodeIsLeaf->child[ i + 1 ];
    }

    nodeIsLeaf->counter -= 1;

    return true;
}

void wr ( Node *temp, Tree *tr )
{
    printf("%s %d\n", "Start Node:", temp->counter);
    for ( int i = 0; i < temp->counter; i++ ){
        printf("%d ", temp->key[i]);
        strPrint( temp->str[i] );
    }
    printf("\n");
    if ( temp == tr->root ){
        for ( int i = 0; i <= temp->counter; i++ ){
            if ( !temp->leaf )
                wr ( temp->child[i], tr );
        }
        printf("%s\n\n", "End Node.");
    }else {
        if (temp->leaf) {
            for (int i = 0; i < temp->counter; i++) {
                if (!temp->leaf)
                    wr(temp->child[i], tr);
            }
            printf("%s\n\n", "End Leaf.");
        } else {
            for (int i = 0; i < temp->counter; i++) {
                if (!temp->leaf)
                    wr(temp->child[i], tr);
            }
            printf("%s\n\n", "End Node.");
        }
    }
}

void destroyNode ( Node *currentNode, int levelTree )
{
    if ( currentNode != NULL ) {
      
        free(currentNode->child);
        free(currentNode->key);
        
        free(currentNode);
    }
    printf("%s\n", "end");
}

void destroyTree ( Node *deleteNode, int levelTree ) {
    
    if (deleteNode->leaf) {

        destroyNode(deleteNode, levelTree );
    }
    else {

       


        for (int i = deleteNode->counter; i >= 0; i-- ) {
            printf("%d %d\n", deleteNode->counter, i);
            destroyTree(deleteNode->child[i], levelTree );
        }

        free(deleteNode);
    }


    
}

void write( Tree *temp )
{
    wr( temp->root, temp );
}
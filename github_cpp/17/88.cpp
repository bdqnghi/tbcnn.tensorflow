#include "Btree.h"

Btree::Btree()
{
    this->root=NULL;
}



void Btree :: insert (int Ipointer)
{
    int i ;
    Node *cont, *head ;
    int flag = setIpointer ( Ipointer, root, &i, &cont ) ;
    if ( flag )
    {
        head = new Node ;
        head-> count = 1 ;
        head-> value[1] = i ;
        head-> child[0] = root ;
        head-> child[1] = cont ;
        root = head ;
    }
}


int Btree ::setIpointer(int Ipointer, Node *node, int *point, Node **temp)
{
    int pos ;
    if ( node == NULL )
    {
        *point = Ipointer ;
        *temp = NULL ;
        return 1 ;
    }
    else
    {
        if ( searchnode ( Ipointer, node, &pos ) )
            cout <<  "Ya existe" << endl ;
        if ( setIpointer( Ipointer, node -> child[pos], point, temp) )
        {
            if ( node -> count < MAX )
            {
                fillnode ( *point, *temp, node, pos ) ;
                return 0 ;
            }
            else
            {
                split ( *point, *temp, node, pos, point, temp ) ;
                return 1 ;
            }
        }
        return 0 ;
    }
}

Node * Btree ::search(int Ipointer, Node *root, int *position)
{
    if ( root == NULL )
        return NULL ;
    else
    {
        if ( searchnode ( Ipointer, root, position ) )
            return root ;
        else
            return search ( Ipointer, root -> child[*position], position ) ;
    }
}

int Btree ::searchnode(int Ipointer, Node *node, int *position)
{
    if ( Ipointer < node -> value[1] )
    {
        *position = 0 ;
        return 0 ;
    }
    else
    {
        *position = node -> count ;
        while ( ( Ipointer < node -> value[*position] ) && *position > 1 )
            ( *position )-- ;
        if ( Ipointer == node -> value[*position] )
            return 1 ;
        else
            return 0 ;
    }
}

void Btree ::fillnode(int Ipointer, Node *temp, Node *node, int kposition)
{
    int i ;
    for ( i = node -> count ; i > kposition ; i-- )
    {
        node -> value[i + 1] = node -> value[i] ;
        node-> child[i + 1] = node -> child[i] ;
    }
    node -> value[kposition + 1] = Ipointer ;
    node -> child[kposition + 1] = temp ;
    node -> count++ ;
}

void Btree ::split(int Ipointer, Node *temp, Node *node, int kposition, int *ypos, Node **newnode)
{
    int i, mid ;

    if ( kposition <= MIN )
        mid = MIN ;
    else
        mid = MIN + 1 ;

    *newnode = new Node ;

    for ( i = mid + 1 ; i <= MAX ; i++ )
    {
        ( *newnode ) -> value[i - mid] = node -> value[i] ;
        ( *newnode ) -> child[i - mid] = node -> child[i] ;
    }

    ( *newnode ) -> count = MAX - mid ;
    node -> count = mid ;

    if ( kposition <= MIN )
        fillnode ( Ipointer, temp, node, kposition ) ;
    else
        fillnode ( Ipointer, temp, *newnode, kposition - mid ) ;

    *ypos = node -> value[node -> count] ;
    ( *newnode ) -> child[0] = node -> child[node -> count] ;
    node -> count-- ;
}

void Btree ::erase(int Ipointer)
{
    Node * temp ;

    if ( ! searchAux( Ipointer, root ) )
        cout << endl << "Value " << Ipointer << " not found." ;
    else
    {
        if ( root -> count == 0 )
        {
            temp = root ;
            root = root -> child[0] ;
            delete temp ;
        }
    }
}

int Btree ::searchAux(int Ipointer, Node *root)
{
    int i ;
    int flag ;

    if ( root == NULL )
        return 0 ;
    else
    {
        flag = searchnode ( Ipointer, root, &i ) ;
        if ( flag )
        {
            if ( root -> child[i - 1] )
            {
                copy ( root, i ) ;
                flag = searchAux ( root -> value[i], root -> child[i] ) ;
                if ( !flag )
                    cout << endl << "Value " << Ipointer << " not found." ;
            }
            else
                clear ( root, i ) ;
        }
        else
            flag = searchAux( Ipointer, root -> child[i] ) ;
        if ( root -> child[i] != NULL )
        {
            if ( root -> child[i] -> count < MIN )
                restore ( root, i ) ;
        }
        return flag ;
    }
}

void Btree ::clear(Node *root, int kpos)
{
    int i ;
    for ( i = kpos + 1 ; i <= root -> count ; i++ )
    {
        root -> value[i - 1] = root -> value[i] ;
        root -> child[i - 1] = root -> child[i] ;
    }
    root -> count-- ;
}

void Btree :: copy ( Node *root, int i )
{
    Node *temp = root -> child[i] ;

    while ( temp -> child[0] )
        temp = temp -> child[0] ;

    root -> value[i] = temp -> value[1] ;
}


void Btree :: restore ( Node *root, int i )
{
    if ( i == 0 )
    {
        if ( root -> child [1] -> count > MIN )
            left ( 1 ) ;
        else
            merge ( 1 ) ;
    }
    else
    {
        if ( i == root -> count )
        {
            if ( root -> child[i - 1] -> count > MIN )
                right ( i ) ;
            else
                merge ( i ) ;
        }
        else
        {
            if ( root -> child[i - 1] -> count > MIN )
                right ( i ) ;
            else
            {
                if ( root -> child[i + 1] -> count > MIN )
                    left ( i + 1 ) ;
                else
                    merge ( i ) ;
            }
        }
    }
}

void Btree ::right(int kpos)
{
    int i ;
    Node *temp ;

    temp = root -> child[kpos] ;

    for ( i = temp -> count ; i > 0 ; i-- )
    {
        temp -> value[i + 1] = temp -> value[i] ;
        temp -> child[i + 1] = temp -> child[i] ;
    }

    temp -> child[1] = temp -> child[0] ;
    temp -> count++ ;
    temp -> value[1] = root -> value[kpos] ;
    temp = root -> child[kpos - 1] ;
    root -> value[kpos] = temp -> value[temp -> count] ;
    root -> child[kpos] -> child [0] = temp -> child[temp -> count] ;
    temp -> count-- ;
}

void Btree ::left(int kpos)
{
    Node *temp ;

    temp = root -> child[kpos - 1] ;
    temp -> count++ ;
    temp -> value[temp -> count] = root -> value[kpos] ;
    temp -> child[temp -> count] = root -> child[kpos] -> child[0] ;
    temp = root -> child[kpos] ;
    root -> value[kpos] = temp -> value[1] ;
    temp -> child[0] = temp -> child[1] ;
    temp -> count-- ;
    for ( int i = 1 ; i <= temp -> count ; i++ )
    {
        temp -> value[i] = temp -> value[i + 1] ;
        temp -> child[i] = temp -> child[i + 1] ;
    }
}

void Btree :: merge(int kpos)
{
    Node *temp1, *temp2 ;
    temp1 = root -> child[kpos] ;
    temp2 = root -> child[kpos - 1] ;
    temp2 -> count++ ;
    temp2 -> value[temp2 -> count] = root -> value[kpos] ;
    temp2 -> child[temp2 -> count] = root ->child[0] ;

    for ( int i = 1 ; i <= temp1 -> count ; i++ )
    {
        temp2 -> count++ ;
        temp2 -> value[temp2 -> count] = temp1 -> value[i] ;
        temp2 -> child[temp2 -> count] = temp1 -> child[i] ;
    }
    for (int i = kpos ; i < root -> count ; i++ )
    {
        root -> value[i] = root -> value[i + 1] ;
        root -> child[i] = root -> child[i + 1] ;
    }
    root -> count-- ;
    delete temp1 ;
}

void Btree :: show( )
{
    display ( root ) ;
}

void Btree :: display ( Node *root )
{
    int i;
    if ( root != NULL )
    {
        for (  i = 0 ; i < root -> count ; i++ )
        {
            display ( root -> child[i] ) ;
            cout << root -> value[i + 1] << "\t" ;
        }
        display ( root -> child[i] ) ;
    }
}

void Btree ::deltree(Node *root)
{
    int i;
    if ( root != NULL )
    {
        for ( i = 0 ; i < root -> count ; i++ )
        {
            deltree ( root -> child[i] ) ;
            delete ( root -> child[i] ) ;
        }
        deltree ( root -> child[i] ) ;
        delete ( root -> child[i] ) ;
    }
}


bool Btree ::search(int Ipointer)
{
    Node * temp ;

    if ( ! searchAux( Ipointer, root ) ){
        cout << endl << "Value " << Ipointer << " not found." ;
        return false;
    }
    else
    {
        if ( root -> count == 0 )
        {
            temp = root ;
            root = root -> child[0] ;
            return true;
        }
    }
}



Btree :: ~Btree( )
{
    deltree ( root ) ;
}

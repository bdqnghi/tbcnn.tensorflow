/*
    g++ bubble.cpp -o bubble
Reference:
    http://www.sorting-algorithms.com/bubble-sort
*/
#include <stdio.h>
#include "util.h"

// bubble
// ========================================================================
void sort( const int N, int *data )
{
    for( int i = 0; i < N; i++ )
    {
        bool swapped = false;
        for( int j = N-1; j > i; j-- )
        {
printf( "i:%d  j: %d\n", i, j );
            if( data[j] < data[j-1] )
            {
                swapped = true;
                swap( data, j-1, j );
dump( N, data );
            }
        }
printf( "sorted [%d]\n", i );
printf( "\n" );
        if( !swapped )
            break;
    }
}

int main()
{
    /* */ int src[] = { 3, 4, 2, 1 };
//int src[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 }; // reverse
//int src[] = { 9, 7, 5, 3, 1, 2, 4, 6, 8 }; // alternating reverse and forward
    const int len   = sizeof( src ) / sizeof( int );

    dump( len, src );
    sort( len, src );
    dump( len, src );

    return 0;
}


#include <stdio.h>
#include "util.h"



void sort( const int N, int *data )
{
    for( int i = 1; i < N; i++ )
    {
        for( int k = i; k > 1 && (data[k] < data[k-1]); k-- )
        {
printf( "i:%d  k-1: %d\n", i, k-1 );
            swap( data, i, k-1 );
dump( N, data );
        }
printf( "sorted [%d]\n", i );
printf( "\n" );
    }
}

int main()
{
     int src[] = { 3, 4, 2, 1 };


    const int len   = sizeof( src ) / sizeof( int );

    dump( len, src );
    sort( len, src );
    dump( len, src );

    return 0;
}

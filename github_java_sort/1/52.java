package com.company;
import edu.princeton.cs.algs4.*;

public class MergeSortCountInversions {

    public static boolean less( Comparable a, Comparable b ) {
        return a.compareTo( b ) == -1;
    }

    
    public static void exchange( Comparable[] a, int i, int j ) {
        Comparable temp = a[ i ];
        a[ i ] = a[ j ];
        a[ j ] = temp;
    }

    public static int insertionSort( Comparable[] a ) {
        int exchangeCount = 0;
        for ( int i = 1; i < a.length; ++i ) {
            for ( int j = i; j > 0 && less( a[ j ], a[ j - 1 ] ); --j ) {
                exchange( a, j, j - 1 );
                ++exchangeCount;
            }
        }
        return exchangeCount;
    }
    

    
    public static int sort( Comparable[] a ) {
        Comparable[] aux = new Comparable[ a.length ];
        return sort( a, aux, 0, a.length - 1 );
    }

    public static int sort( Comparable[] a, Comparable[] aux, int low, int high ) {
        if ( low >= high ) return 0;
        int mid = ( low + high ) / 2;
        int exchanges = 0;

        exchanges += sort( a, aux, low, mid );
        exchanges += sort( a, aux, mid + 1, high );
        exchanges += merge( a, aux, low, mid, high );

        return exchanges;
    }

    public static int merge( Comparable[] a, Comparable[] aux, int low, int mid, int high ) {
        int i = low;
        int j = mid + 1;
        int exchanges = 0;

        for ( int k = low; k <= high; ++k ) {
            aux[ k ] = a[ k ];
        }

        for ( int k = low; k <= high; ++k ) {
            if ( i > mid ) {
                a[ k ] = aux[ j++ ];
                ++exchanges;
            } else if ( j > high ) {
                a[ k ] = aux[ i++ ];
                ++exchanges;
            } else if ( less( aux[ j ], aux[ i ] ) ) {
                a[ k ] = aux[ j++ ];
                ++exchanges;
            } else {
                a[ k ] = aux[ i++ ];
                ++exchanges;
            }
        }
        return exchanges;
    }
    

    public static void main( String[] args ) {
        Integer[] intArr = { 14, 12, 10, 8, 6, 4, 2, 0, 1, 3, 5, 7, 9 };

        StdOut.println( "DEBUG: intArr (BEFORE): " + java.util.Arrays.toString( intArr ) );

        
        int exchanges = sort( intArr );

        StdOut.println( "DEBUG: intArr (AFTER): " + java.util.Arrays.toString( intArr ) );
        StdOut.println( "DEBUG: exchanges (AFTER - EXPECTED: 53): " + exchanges );
    }
}

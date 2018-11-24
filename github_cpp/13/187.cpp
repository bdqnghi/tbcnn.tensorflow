/*
  koder : melkor
  TASK  : MergeSort
  
  Time Complexity: O(N log N)
*/

#include <cstdio>
#include <cstring>

#define MAXN 50005

int N;

int a[MAXN], tmp[MAXN];

void MergeSort( int lo, int hi ) {

  if ( lo == hi ) return;
  
  int mid = ( lo + hi ) >> 1;
  
  // Recursively sort the two portions of the input sequence
  
  MergeSort( lo, mid );
  MergeSort( mid + 1, hi );
  
  // Merge in linear time the two sorted sequences
  
  int cnt = 0;
  int llo = lo, lhi = mid,
      rlo = mid + 1, rhi = hi;
  
  while ( llo <= lhi && rlo <= rhi )
    if ( a[llo] < a[rlo] )
         tmp[ cnt++ ] = a[ llo++ ];
    else tmp[ cnt++ ] = a[ rlo++ ];
  
  while ( llo <= lhi ) tmp[ cnt++ ] = a[ llo++ ];
  while ( rlo <= rhi ) tmp[ cnt++ ] = a[ rlo++ ];
  
  // Copy the sorted sequence in the original one
  
  cnt = 0;
  for ( int i = lo; i <= hi; i++ ) a[i] = tmp[ cnt++ ];
}

int main() {

  freopen( "in.txt", "r", stdin );
  freopen( "out.txt", "w", stdout );
  
  scanf( "%d", &N );
  for ( int i = 0; i < N; i++ ) scanf( "%d", &a[i] );
  
  MergeSort( 0, N - 1 );
  
  for ( int i = 0; i < N; i++ ) printf( "%d\n", a[i] );

  return 0;
}//melkor

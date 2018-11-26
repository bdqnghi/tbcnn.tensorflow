/*
  koder : melkor
  TASK  : Insertion Sort
  
  Running time: O(N^2), Omega(N)
*/

#include <cstdio>

#define MAXN 1000

int N, key, i, j;

int a[MAXN];

int main() {

  freopen( "in.txt", "r", stdin );
  freopen( "out.txt", "w", stdout );
  
  scanf( "%d", &N );
  for ( i = 0; i < N; i++ )
    scanf( "%d", &a[i] );

  /* Insertion Sort */
  
  for ( i = 1; i < N; i++ ) {
    key = a[i];
	for ( j = i - 1; j >= 0 && a[j] > key; j-- )
	  a[ j + 1 ] = a[j];
	a[ j + 1 ] = key;
  }
  
  for ( i = 0; i < N; i++ )
    printf( "%d\n", a[i] );
  
  return 0;
}//melkor

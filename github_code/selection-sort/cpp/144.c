/*
  koder : melkor
  TASK  : Selection Sort
  
  Running time: O(N^2)
*/

#include <cstdio>

#define MAXN 2000

int N, tmp;

int a[MAXN];

int main() {

  freopen( "in.txt", "r", stdin );
  freopen( "out.txt", "w", stdout );
  
  scanf( "%d", &N );
  for ( int i = 0; i < N; i++ )
    scanf( "%d", &a[i] );
  
  /* Selection Sort */
  
  for ( int i = 0; i < N - 1; i++ )
    for ( int j = i + 1; j < N; j++ )
      if ( a[j] < a[i] ) {
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
      }
  
  for ( int i = 0; i < N; i++ )
    printf( "%d\n", a[i] );

  return 0;
}//melkor

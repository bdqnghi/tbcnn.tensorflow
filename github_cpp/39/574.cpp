
#include <bits/stdc++.h>
using namespace std;

#define REP(i, a, b) for (int i = a; i <= b; i++)
#define FOR(i, n) for (int i = 0; i < n; i++)
#define foreach(it, ar) for ( typeof(ar.begin()) it = ar.begin(); it != ar.end(); it++ )
#define fill(ar, val) memset(ar, val, sizeof(ar))
#define PI 3.1415926535897932385
#define uint64 unsigned long long
#define Int long long
#define int64 long long
#define all(ar) ar.begin(), ar.end()
#define pb push_back
#define ff first
#define ss second
#define bit(n) (1<<(n))
#define Last(i) ( (i) & (-i) )
#define sq(x) ((x) * (x))
#define INF INT_MAX
#define mp make_pair

const int MAXN = 1e5 + 5  ; 

vector<int> t[ 4*MAXN ] ; 

int query(  int v, int tl , int tr , int l , int r , int x )
 {
    if( l > r )
     return INT_MAX ; 
    
    if( l == tl && r == tr )
     {
         vector<int>::iterator it = lower_bound( t[v].begin( ) , t[v].end() , x ) ;
         return t[v].end() - *it ;
     } 	  
     
     int tm = ( tl + tr )>>1 ; 
     return        query( v*2 , tl , tm , l , min( r, tm ) , x ) +
                   query( v*2 + 1 , tm + 1 , tr , max( l , tm + 1 ) , r , x ) ; 
     	         


 }

 void build(  int v , int tl , int tr ) 
  {
      if(  tl == tr )
         t[v] = vector<int> ( 1 , a[tl]) ; 
      else
       {
           int tm = ( tl + tr ) >> 1 ; 
           build( a , v*2 , tl , tm ); 
           build( a , v*2 + 1 , tm + 1 , tr ) ; 
           merge( t[v*2].begin() , t[v*2].end(),t[v*2+1].begin() , t[v*2+2].end() , back_inserter(t[v]) ) ;    

       }    

  }




int main ( ) 
 {

    int n ;
    cin >> n ; 
    FOR( i , n )
     scanf("%d",&a[i + 1]) ; 

     build( 1 , 1 , n  ) ;    

 }
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#define MAXN 100
using namespace std;
int n,m ;
vector < int > g [MAXN] ;
bool used [ MAXN ] ;
vector < int > ans ;

void dfs ( int v ) {
    //cout<<"YO"<<endl;
	used [ v ] = true ;
	for ( size_t i = 0 ; i < g [ v ] . size ( ) ; ++ i ) {
		int to = g [ v ] [ i ] ;
		if ( ! used [ to ] )
			dfs ( to ) ;
	}
	ans. push_back ( v ) ;
}

void topological_sort ( ) {
	for ( int i = 0 ; i < n ; ++ i )
		used [ i ] = false ;
	ans. clear ( ) ;
	//cout<<"YO";
	for ( int i = 0 ; i < n ; ++ i )
		if ( ! used [ i ] )
			dfs ( i ) ;
	reverse ( ans. begin ( ) , ans. end ( ) ) ;
}
int main()
{
    scanf("%d %d",&n,&m);
    while(m--){
        int a,b;
        scanf("%d %d",&a,&b);
        g[a-1].push_back(b-1);

    }
        topological_sort();
        for(int i=0;i<ans.size();i++)
        {
            cout<<ans[i]+1<<" ";
        }
}

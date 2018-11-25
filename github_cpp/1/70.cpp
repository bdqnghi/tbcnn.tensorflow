#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
#include <cstring>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

const int INF = 0x3f3f3f3f;

int main(){
    ios::sync_with_stdio(false);
    int t, m, n;
    cin >> t;
    while ( t-- ){
        cin >> m >> n;
        char c;
        int k = 0, l = 0;
        int adj[n][m];
        bool visitado[n][m];
        queue<pair<int, ii> > bfs, bfss;
        for ( int i = 0; i < n; ++i ){
            for ( int j = 0; j < m; ++j ){
                cin >> c;
                if ( c == '.' ){
					adj[i][j] = 0;
					if ( bfs.empty() ) bfs.push( mp( 0, mp( i, j ) ) );
                }
                else adj[i][j] = INF;
                visitado[i][j] = false;
            }
        }
        int MAX = 0;
        while ( !bfs.empty() ){
			int a = bfs.front().first;
			int q = bfs.front().second.first;
			int w = bfs.front().second.second;
			if ( MAX < a ){
				MAX = a;
				k = q; l = w;
			}
			visitado[q][w] = true;
			bfs.pop();
			if ( q+1 < n && adj[q+1][w] == 0 && !visitado[q+1][w] ){
				bfs.push( mp( a+1, mp( q+1, w ) ) );
				visitado[q+1][w] = true;
			}
			if ( q-1 >= 0 && adj[q-1][w] == 0 && !visitado[q-1][w] ){
				bfs.push( mp( a+1, mp( q-1, w ) ) );
				visitado[q-1][w] = true;
			}
			if ( w+1 < m && adj[q][w+1] == 0 && !visitado[q][w+1] ){
				bfs.push( mp( a+1, mp( q, w+1 ) ) );
				visitado[q][w+1] = true;
			}
			if ( w-1 >= 0 && adj[q][w-1] == 0 && !visitado[q][w-1] ){
				bfs.push( mp( a+1, mp( q, w-1 ) ) );
				visitado[q][w-1] = true;
			}
        }
		
        memset( visitado, false, sizeof(visitado));
        bfs.push( mp( 0, mp( k, l ) ) );
        MAX = 0;
		
		while ( !bfs.empty() ){
			int a = bfs.front().first;
			int q = bfs.front().second.first;
			int w = bfs.front().second.second;
			if ( MAX < a ) MAX = a;
			visitado[q][w] = true;
			bfs.pop();
			if ( q+1 < n && adj[q+1][w] == 0 && !visitado[q+1][w] ){
				bfs.push( mp( a+1, mp( q+1, w ) ) );
				visitado[q+1][w] = true;
			}
			if ( q-1 >= 0 && adj[q-1][w] == 0 && !visitado[q-1][w] ){
				bfs.push( mp( a+1, mp( q-1, w ) ) );
				visitado[q-1][w] = true;
			}
			if ( w+1 < m && adj[q][w+1] == 0 && !visitado[q][w+1] ){
				bfs.push( mp( a+1, mp( q, w+1 ) ) );
				visitado[q][w+1] = true;
			}
			if ( w-1 >= 0 && adj[q][w-1] == 0 && !visitado[q][w-1] ){
				bfs.push( mp( a+1, mp( q, w-1 ) ) );
				visitado[q][w-1] = true;
			}
        }
		
        cout << "Maximum rope length is " << MAX << ".\n";
    }
}

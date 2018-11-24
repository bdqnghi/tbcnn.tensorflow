/* Algo     : Floyd Warshall
   Paradigm : Dynamic Programming
   Time Complexity : O(n^3)
   
   Advantage  : works over negative weights and ," all pairs-shortest path "
   Limitation : number of nodes are less ,for matrix creation 


*/
#include <bits/stdc++.h>

using namespace std;

#define MAX 500;

int adj[MAX][MAX];
int dist[MAX][MAX];

const int INF = 99999;

int n,m,x,y,wt,q;

void floyd() {

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            dist[i][j] = adj[i][j];
        }
    }
    
    for (int k=1; k<=n; k++) {
        for (int i=1;i<=n;i++) {
            for (int j=1;j<=n;j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    cin >> n >> m;                              // n-> nodes, m->edges
    for (int i=1; i<=n; i++) {
        for (int j=1;j<=n; j++) {
            if(i == j)
                adj[i][j]=0;                    // as there is no negative cycle
            else
                adj[i][j] = INF;
        }
    }
    for (int i=1; i<=m; i++) {
        cin >> x >> y >> wt;
        adj[x][y] = wt;
    }
    
    floyd();
   
    cin >> q;                                     // queries
    
    while(q--)  {
        cin >>  x >> y;
        if(dist[x][y] == INF) {
            cout << "-1\n";
        }
        else
            cout << dist[x][y] << "\n";
    }
    return 0;
}

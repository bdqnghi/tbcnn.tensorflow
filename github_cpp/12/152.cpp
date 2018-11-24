/*
    Name: Floyd-Warshall algorithm
    
    Time complexity: O(N ^ 3)
    Space complexity: O(N ^ 2)
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 510;
const int INF = 1e9;

int g[N][N], dist[N][N];

void FloydWarshall(int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            dist[i][j] = g[i][j];
        
        dist[i][i] = 0;
    }

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        fill(g[i] + 1, g[i] + n + 1, INF);

    for (int i = 0, u, v, w; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        g[u][v] = w;
    }

    FloydWarshall(n, m);

    return 0;
}

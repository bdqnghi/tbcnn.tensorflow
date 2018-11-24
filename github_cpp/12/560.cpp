/**
 * Floyd-Warshall algorithm
 * All-Pairs Shortest Path
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int INF = 1e9;

int d[MAXN][MAXN];    // Adjacency matrix

main()
{
    // freopen("input.in", "r", stdin);

    int testcase;
    cin >> testcase;
    while (testcase--) {
        int n, m;
        cin >> n >> m;

        // Initialization
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                d[i][j] = INF;
        for (int i = 0; i < n; ++i)
            d[i][i] = 0;

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            d[u][v] = w;
        }

        // DP
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }

        // Total distance for each vertex
        for (int i = 0; i < n; ++i)
            for (int j = 1; j < n; ++j)
                d[i][0] += d[i][j];
        
        int min_median = 0, min_cost = INF;
        for (int i = 0; i < n; ++i) {
            if (d[i][0] < min_cost) {
                min_median = i;
                min_cost = d[i][0];
            }
        }
        cout << min_median << endl;
    }
}

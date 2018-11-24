/*
  Algoritam: Flojd-Varsalov algoritam
  Slozenost: O(n ^ 3)

* * *
Moguce je ustanoviti postojojanje negativnog ciklusa (tada je dist[i][i] < 0).
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 310;
const int inf = 1e9;

int n, m;
int g[N][N], dist[N][N];

void FloydWarshall() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) dist[i][j] = g[i][j];
    dist[i][i] = 0;
  }

  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) g[i][j] = g[j][i] = inf;

  for (int i = 0; i < m; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    g[a][b] = min(g[a][b], c);
    g[b][a] = min(g[b][a], c);
  }

  FloydWarshall();

  return 0;
}

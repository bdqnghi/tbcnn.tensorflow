#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 100;

int vis[MAXN], par[MAXN], adj[MAXN][MAXN];
queue<int> q;

bool BFS() {
  fill (vis, vis+MAXN, 0);
  vis[1] = 1;
  par[1] = -1;
  q.push(1);
  while (!q.empty()) {
    int a = q.front(); q.pop();
    for (int u = 1; u <= N; ++u) {
      if (vis[u] || !adj[a][u]) continue;
      vis[u] = 1;
      par[u] = a;
      q.push(u);
    }
  }
  return vis[N];
}

int solve() {
  int ans = 0;
  while (BFS()) {
    int mp = 1e9, p;
    for (int i = N; i != 1; i = par[i]) {
      p = par[i];
      mp = min(mp, adj[p][i]);
    }
    for (int i = N; i != 1; i = par[i]) {
      p = par[i];
      adj[p][i] -= mp;
      adj[i][p] += mp;
    }
    ans += mp;
  }
  return ans;
}

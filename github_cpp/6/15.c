#include "../template/template.h"

#define MAXV 100001
vector<int> adj[MAXV];
int dfs_num[MAXV], dfs_low[MAXV], dfs_parent[MAXV];
int dfscounter, V, dfsRoot, rootChildren, ans;
int articulation[MAXV], articulations;
vector<ii> bridges;

void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfscounter++;
  rep(i, 0, adj[u].size()) {
    int v = adj[u][i];
    if (dfs_num[v] == -1) {
      dfs_parent[v] = u;
      if (u == dfsRoot) rootChildren++;

      articulationPointAndBridge(v);
      if (dfs_low[v] >= dfs_num[u]) articulation[u] = true;
      if (dfs_low[v] > dfs_num[u]) bridges.pb(mp(u, v));

      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    } else if (v != dfs_parent[u])
      dfs_low[u] = min(dfs_low[u], dfs_num[v]);
  }
}

int main() {
  
  dfscounter = 0;
  rep(i, 0, V) {
    dfs_low[i] = dfs_parent[i] = articulation[i] = 0;
    dfs_num[i] = -1;
  }
  articulations = 0;
  bridges.clear();
  rep(i, 0, V) if (dfs_num[i] == -1) {
    dfsRoot = i;
    rootChildren = 0;
    articulationPointAndBridge(i);
    articulation[dfsRoot] = (rootChildren > 1);
  }
  printf("#articulations = %d\n", articulations);
  rep(i, 0, V) if (articulation[i]) printf("Vertex %d\n", i);
  printf("#bridges = %d\n", bridges.size());
  rep(i, 0, bridges.size())
      printf("Bridge %d<->%d\n", bridges[i].F, bridges[i].S);
  return 0;
}
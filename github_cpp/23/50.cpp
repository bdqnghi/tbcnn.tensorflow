#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 1e5 + 1;
const int INF = 1e9 + 1;


struct Edge {
  Edge(int _to, int _cap, int _rev)
    : to(_to), cap(_cap), rev(_rev) {}
  int to;
  int cap; 
  int rev; 
};

vector< Edge > G[MAX_V]; 
bool used[MAX_V]; 


void add_edge(int _from, int _to, int _cap) {
  G[_from].emplace_back(Edge(_to, _cap, G[_to].size()));
  G[_to].emplace_back(Edge(_from, 0, G[_from].size() - 1));
}


int dfs(int from, int to, int cost) {
  if (from == to) return cost;
  used[from] = true;
  for (int i = 0; i < G[from].size(); ++i) {
    Edge &e = G[from][i];
    if (!used[e.to] && e.cap > 0) {
      int d = dfs(e.to, to, min(cost, e.cap));
      if (d > 0) {
	e.cap = -d;
	G[e.to][e.rev].cap += d;
	return d;
      }
    }
  }
  return 0;
}


int max_flow(int s, int t) {
  int flow = 0;
  for ( ; ; ) {
    memset(used, 0, sizeof(used));
    int f = dfs(s, t, INF);
    if (f == 0) return flow;
    flow += f;
  }
}

int main()
{
  int V, E;
  cin >> V >> E;
  for (int i = 0; i < E; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    add_edge(u, v, c);
  }
  
  cout << max_flow(0, V - 1) << endl;
  
  return 0;
}

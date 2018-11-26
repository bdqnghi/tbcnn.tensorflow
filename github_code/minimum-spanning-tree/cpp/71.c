#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'
#define MAX (int)1e4 + 5

// Referencias:
// https://www.hackerearth.com/notes/minimum-spanning-tree/

using namespace std;

struct Edge {
  int from;
  int to;
  long long weight;
  Edge (){}
  Edge (int f, int t, long long w) : from(f), to(t), weight(w) {}
  bool operator < (const Edge &e) const{
    return weight < e.weight;
  }
};

int p[MAX], nodes, edges;
vector <Edge> G(MAX);

int find_set(int x) {
  return (p[x] == x)? x : p[x] = find_set(p[x]);
}

void union_set(int x, int y) {
  int px = find_set(x);
  int py = find_set(y);
  if (px == py) return;
  p[px] = py;
}

void init() {
  for (int i = 0; i < MAX; i++)
    p[i] = i;
}

long long kruskal(vector<Edge> &G) {
  sort(G.begin(), G.begin() + edges);
  long long ans = 0;

  for (int i = 0; i < edges; i++) {
    int u = G[i].from;
    int v = G[i].to;
    long long w = G[i].weight;

    if (find_set(u) != find_set(v)) {
      ans += w;
      union_set(u, v);
    }
  }
  return ans;
}

int main() {
  fast;
  init();
  cin >> nodes >> edges;
  for (int i = 0; i < edges; i++) cin >> G[i].from >> G[i].to >> G[i].weight;
  cout << kruskal(G) << endl;
  return 0;
}

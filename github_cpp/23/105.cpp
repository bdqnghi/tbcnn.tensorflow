

using namespace std;
using ll = long long;

















struct MaxFlow {
  struct Edge {
    int from, to;
    ll cap, rev;
    int To(int i) const { return from == i ? to : from; }
    ll& Cap(int i) { return from == i ? cap : rev; }
    ll& Rev(int i) { return from == i ? rev : cap; }
  };
  int n;
  vector< Edge > edges;
  vector< vector< int > > g;
  ll inf;
  MaxFlow(int n, ll inf = 1e18) : n(n), g(n), inf(inf) {}
  int addEdge(int a, int b, ll cap, bool undirected = false) {
    edges.emplace_back((Edge){a, b, cap, undirected ? cap : 0});
    g[a].emplace_back(edges.size() - 1);
    g[b].emplace_back(edges.size() - 1);
    return edges.size() - 1;
  }
  ll build(int s, int t) {
    ll flow = 0;
    while(1) {
      vector< int > used(n, 0);
      ll x = dfs(used, s, t, inf);
      if(x == 0) break;
      flow += x;
      if(flow >= inf) return inf;
    }
    return flow;
  }
  vector< int > isCut;
  void restoreMinCut(int s) {
    isCut = vector< int >(edges.size());
    
    vector< int > used(n);
    queue< int > q;
    q.emplace(s);
    used[s] = 1;
    while(q.size()) {
      int i = q.front();
      q.pop();
      for(int idx : g[i]) {
        Edge& edge = edges[idx];
        if(!used[edge.To(i)] && edge.Cap(i) > 0) {
          q.emplace(edge.To(i));
          used[edge.To(i)] = 1;
        }
      }
    }
    for(size_t i = 0; i < edges.size(); i++) {
      if(used[edges[i].from] != used[edges[i].to]) isCut[i] = 1;
    }
  }

private:
  ll dfs(vector< int >& used, int i, int t, ll x) {
    if(i == t) return x;
    used[i] = 1;
    for(int idx : g[i]) {
      Edge& edge = edges[idx];
      if(!used[edge.To(i)] && edge.Cap(i) > 0) {
        ll d = dfs(used, edge.To(i), t, min(x, edge.Cap(i)));
        if(d == 0) continue; 
        edge.Cap(i) -= d;
        edge.Rev(i) += d;
        return d;
      }
    }
    return 0;
  }
};



const int N = 2e6;
const ll inf = 1e18;
MaxFlow flow(N, inf);

template< typename T >
struct FordFulkerson
{
  struct edge
  {
    int to;
    T cap;
    int rev;
  };

  vector< vector< edge > > graph;
  vector< int > used;
  const T INF;
  int timestamp;

  FordFulkerson(int n) : INF(numeric_limits< T >::max()), timestamp(0)
  {
    graph.resize(n);
    used.assign(n, -1);
  }

  void add_edge(int from, int to, T cap)
  {
    graph[from].emplace_back((edge) {to, cap, (int) graph[to].size()});
    graph[to].emplace_back((edge) {from, 0, (int) graph[from].size() - 1});
  }

  T dfs(int idx, const int t, T flow)
  {
    if(idx == t) return flow;
    used[idx] = timestamp;
    for(auto &e : graph[idx]) {
      if(e.cap > 0 && used[e.to] != timestamp) {
        T d = dfs(e.to, t, min(flow, e.cap));
        if(d > 0) {
          e.cap -= d;
          graph[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  T max_flow(int s, int t)
  {
    T flow = 0;
    for(T f; (f = dfs(s, t, INF)) > 0; timestamp++) {
      flow += f;
    }
    return flow;
  }
};

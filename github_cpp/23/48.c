class FordFulkerson {
  public:
    struct edge {
      explicit edge(size_t t, int c, size_t r) : to(t), cap(c), rev(r) {}
      size_t to; int cap; size_t rev;
    };

    explicit FordFulkerson(size_t v): G(v), used(v) {}
    ~FordFulkerson() = default;

    void add_edge(size_t from, size_t to, int cap) {
      G[from].emplace_back(to, cap, G[to].size());
      G[to].emplace_back(from, 0, G[from].size() - 1);
    }
    int dfs(size_t v, size_t t, int f) {
      if (v == t) return f;
      used[v] = true;
      for (auto &&e : G[v]) {
        if (used[e.to] || e.cap <= 0) continue;
        int d = dfs(e.to, t, std::min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          reverse(e).cap += d;
          return d;
        }
      }
      return 0;
    }
    int max_flow(size_t s, size_t t) {
      int flow = 0;
      while (true) {
        std::fill(used.begin(), used.end(), 0);
        int f = dfs(s, t, INF);
        if (f == 0) return flow;
        flow += f;
      }
    }

  private:
    std::vector<std::vector<edge>> G;
    std::vector<bool> used;
    edge &reverse(edge const &e) {
      return G[e.to][e.rev];
    }
};

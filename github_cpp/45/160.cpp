struct Edge {
    int from;
    int to;
    int capacity;
    int flow;

    Edge() {}
    Edge(int _from, int _to, int _capacity = 0, int _flow = 0)
        : from(_from), to(_to), capacity(_capacity), flow(_flow) {}
};

struct flowNetwork {
    int n;
    int source;
    int sink;
    vector<Edge> edges;
    vector< vector<int> > adjLists;

    flowNetwork() {}
    flowNetwork(int _n, int _source, int _sink) : n(_n), source(_source), sink(_sink) {
        adjLists.resize(n);
    }

    void addEdge(Edge e) {
        adjLists[e.from].push_back(edges.size());
        edges.push_back(e);
        e = Edge(e.to, e.from, 0);
        adjLists[e.from].push_back(edges.size());
        edges.push_back(e);
    }

    ll dfs(int u, int minC) {
        if (u == sink) {
            return minC;
        }

        visited[u] = 1;
        for (auto uv : adjLists[u]) {
            if (!visited[edges[uv].to] && edges[uv].flow < edges[uv].capacity) {
                int delta = dfs(edges[uv].to, min(minC, edges[uv].capacity - edges[uv].flow));

                if (delta > 0) {
                    edges[uv].flow += delta;
                    edges[uv ^ 1].flow -= delta;
                    return delta;
                }
            }
        }

        return 0;
    }
};





#ifndef ALGORITHMS_FORD_FULKERSON_H
#ifndef INF_INT
#define INF_INT 0x3fffffff
#endif

#include <algorithm>
#include <vector>
#include <cstring>

using std::min;
using std::vector;
using std::memset;

typedef struct ford_fulkerson_edge {
    int to;
    int capacity;
    int reverse;
} ff_edge;


int dfs(int s, int t, int flow, vector<ff_edge> *G, bool *used) {
    if (s == t) {
        return flow;
    }
    used[s] = true;
    for (int i = 0; i < G[s].size(); ++i) {
        ff_edge &e = G[s][i];
        if (!used[e.to] && e.capacity > 0) {
            int d = dfs(e.to, t, min(flow, e.capacity), G, used);
            if (d > 0) {
                e.capacity -= d;
                G[e.to][e.reverse].capacity += d;
                return d;
            }
        }
    }
    return 0;
}


int ford_fulkerson(vector<ff_edge> *G, int V, int s, int t) {
    auto *used = new bool[V];
    int flow = 0;
    while (true) {
        memset(used, 0, sizeof(*used) * V);
        int f = dfs(s, t, INF_INT, G, used);
        if (f == 0) {
            delete[] used;
            return flow;
        }
        flow += f;
    }
}

void add_edge(vector<ff_edge> *G, int from, int to, int capacity) {
    G[from].emplace_back((ff_edge) {to, capacity, (int) G[to].size()});
    G[to].emplace_back((ff_edge) {from, 0, (int) G[from].size() - 1});
}

#define ALGORITHMS_FORD_FULKERSON_H

#endif 

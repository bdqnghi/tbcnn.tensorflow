#include <bits/stdc++.h>
using namespace std;
vector<int> vi;
typedef pair<int,int> ii;

/* ================= */
/* METHOD 1: KRUSKAL */
/* ================= */

struct Edge {
    int u, int v, int cost;
    bool operator<(const Edge& o) const {
        return cost < o.cost;
    }
};
namespace Kruskal {
    struct UnionFind {
        vi p, rank;
        int numSets;
        UnionFind(int n) {
            numSets = n;
            rank.assign(n,0);
            p.resize(n);
            rep(i,0,n-1) p[i] = i;
        }
        int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
        void unionSet(int i, int j) {
            if (!isSameSet(i, j)) {
                numSets--;
                int x = findSet(i), y = findSet(j);
                if (rank[x] > rank[y]) {
                    p[y] = x;
                } else {
                    p[x] = y;
                    if (rank[x] == rank[y]) rank[y]++;
                }
            }
        }
    };

    int find_mst(int n_nodes, vector<Edge>& edges, vector<vector<ii>>& mst) {
        sort(edges.begin(), edges.end());
        UnionFind uf(n_nodes);
        mst.assign(n_nodes, vector<ii>());
        int mstcost = 0;
        int count = 1;
        for (auto& e : edges) {
            int u = e.u, v = e.v, cost = e.cost;
            if (!uf.isSameSet(u, v)) {
                mstcost += cost;
                uf.unionSet(u, v);
                mst[u].emplace_back(v, cost);
                mst[v].emplace_back(u, cost);
                if (++count == n_nodes) break;
            }
        }
        return mstcost;
    }
}

/* ============== */
/* METHOD 2: PRIM */
/* ============== */

struct Edge {
    int u, v, cost;
    bool operator<(const Edge& o) const {
        return cost > o.cost; // we use '>' instead of '<' so that
        // priority_queue<Edge> works as a minheap
    }
};
namespace Prim {
    bool visited[MAXN]
    int find_mst(vector<vector<ii>>& g, vector<vector<ii>>& mst) {
        int n_nodes = g.size();
        memset(visited, false, sizeof(bool) * n_nodes);
        mst.assign(n_nodes, vector<ii>());
        priority_queue<Edge> q;
        int total_cost = 0;
        visited[0] = true;
        for (ii& p : g[0]) q.push({0, p.first, p.second});
        int count = 1;
        while (!q.empty()) {
            Edge edge = q.top(); q.pop();
            if (visited[edge.v]) continue;
            int u = edge.u;
            int v = edge.v;
            int cost = edge.cost;
            visited[v] = true;
            total_cost += cost;
            mst[u].emplace_back(v, cost);
            mst[v].emplace_back(u, cost);
            if (++count == N) break;
            for (ii p : g[v]) {
                if (visited[p.first]) continue;
                q.push({v, p.first, p.second});                
            }            
        }
        return total_cost;
    }
}
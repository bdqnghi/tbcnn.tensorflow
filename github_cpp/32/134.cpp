/*
クラスカル法
計算量 O(Elog(V))
最小全域木を求める
UnionFind木が必要
*/
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_V = 100000;

struct UnionFindTree {
    int par[MAX_V];
    int rank[MAX_V];

    void init(int n) {
        for (int i = 0; i < n; i++) {
            par[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            return par[x] = find(par[x]);
        }
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;

        if (rank[x] < rank[y]) {
            par[x] = y;
        } else {
            par[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }

    bool same(int x, int y) { return find(x) == find(y); }
};

struct edge {
    int u, v, cost;
};

bool comp(const edge &e1, const edge &e2) { return e1.cost < e2.cost; }

vector<edge> es;
int V, E;

int kruskal() {
    sort(es.begin(), es.end(), comp);
    UnionFindTree a;
    a.init(V);
    int res = 0;
    for (int i = 0; i < es.size(); i++) {
        edge e = es[i];
        if (!a.same(e.u, e.v)) {
            a.unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}
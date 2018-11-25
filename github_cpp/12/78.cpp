



#include <vector>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

template<class Cost_t>
class MinimumSpanningTree {
public:
    typedef struct edge_st {
        int u, v;
        Cost_t c;
        bool operator < (const struct edge_st &o) const {
            return c < o.c;
        }
    } Edge;
    vector<Edge> edges;
    vector<int> parents;
    int N;
    
    MinimumSpanningTree(int n) : N(n) { parents.resize(n + 5); }
    void add_edge(int u, int v, Cost_t c) { Edge e = {u, v, c}; edges.push_back(e); }
    Cost_t kruskal() {
        for (int i = 1; i <= N; i++) parents[i] = i;        
        int sz = edges.size();
        sort(edges.begin(), edges.end());
        Cost_t res = 0;
        int need_edge = N - 1;
        for (int i = 0; i < sz && need_edge; i++) {
            int pu = find_parent(edges[i].u);
            int pv = find_parent(edges[i].v);
            if (pu != pv) { res += edges[i].c; need_edge--; parents[pu] = pv; }
        }
        assert(need_edge == 0);
        return res;
    }
private:
    int find_parent(int u) {
        if (u == parents[u]) return u;
        return parents[u] = find_parent(parents[u]);
    }
};    
        
int main() {
    MinimumSpanningTree<int> mst(5);
    mst.add_edge(1, 4, 1);
    mst.add_edge(1, 4, 7);
    mst.add_edge(2, 3, 5);
    mst.add_edge(5, 3, 9);
    mst.add_edge(1, 3, 4);
    mst.add_edge(1, 2, 3);
    mst.add_edge(2, 5, 2);
    assert(mst.kruskal() == 10);
    mst.add_edge(1, 3, 1);
    assert(mst.kruskal() == 7);
    return 0;
}

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define weight(x) x.first
#define vertices(x) x.second

class UnionFind {
    private:
        vector<int> parent, rank;
        int V;
    public:
        UnionFind(int N)
        {
            parent.assign(N, 0);
            rank.assign(N, 0);
            for (int i = 0; i < N; ++i)
                parent[i] = i;
            V = N;
        }

        int find_set(int node) // find parent and compress path
        {
            if (parent[node] != node)
                parent[node] = find_set(parent[node]);
            return parent[node];
        }

        int is_same_set(int u, int v)
        {
            return find_set(u) == find_set(v);
        }

        void union_set(int x, int y)
        {
            int u = find_set(x);
            int v = find_set(y);
            if (rank[u] > rank[v])
                parent[v] = u;
            else {
                parent[u] = v;
                if (rank[u] == rank[v])
                    rank[v]++;
            }
        }

        void debug()
        {
            cout << V << " nodes\n";
            for (int i = 0; i < V; ++i)
                cout << "Node:" << i << "- Parent:" << parent[i] << " Rank:" << rank[i] << endl;
        }
};

int main()
{
    int E, V;
    cin >> V >> E;

    vector< pair<int, pair<int, int> > > elist(E);
    /* vector of (w, (u, v)) */
    int u, v, w;
    for (int i = 0; i < E; ++i) {
        cin >> u >> v >> w;
        elist[i] = make_pair(w, make_pair(u, v));
    }
    sort(elist.begin(), elist.end());
    UnionFind mst(V);
    int mst_weight = 0;
    for (int i = 0; i < E; ++i) {
        pair<int, pair<int, int> > p = elist[i];
        if (!mst.is_same_set(vertices(p).first, vertices(p).second)) {
            cout << "Edge " << vertices(p).first << " " << vertices(p).second << endl;
            mst.union_set(vertices(p).first, vertices(p).second);
//            mst.debug();
            mst_weight += weight(p);
        }
    }

    cout << "Weight:" << mst_weight << endl;

    return 0;
}

#include <bits/stdc++.h>


using namespace std;
using LL = long long;
using P = pair<int, int>;
using TP = tuple<int, int, int>;
#define FOR(i, a, n) for(int i = (int)(a); i < (int)(n); ++i)
#define REP(i, n) FOR(i, 0, n)

#define pb(a) push_back(a)
#define all(x) (x).begin(),(x).end()

const int INF = (int)1e9;
const LL INFL = (LL)1e15;
const int MOD = 1e9 + 7;

int dy[]={0, 0, 1, -1, 0};
int dx[]={1, -1, 0, 0, 0};

class UnionFind {
    private:
        vector<int> parent;  
        vector<int> rank;    
    public:
        explicit UnionFind(int n);          
        int Find(int x);           
        void Unite(int x, int y);  
        bool Same(int x, int y);   
};

UnionFind::UnionFind(int n) : parent(vector<int>(n)), rank(vector<int>(n)) 
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int UnionFind::Find(int x) {
    if (parent[x] == x) {
        return x;
    } else {
        return parent[x] = Find(parent[x]);
    }
}

void UnionFind::Unite(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;

    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
}

bool UnionFind::Same(int x, int y) { return Find(x) == Find(y); }

template <typename T>
struct Edge {
    int src, to;
    T cost;
    Edge(int to, T cost) : src(-1), to(to), cost(cost) {}
    Edge(int src, int to, T cost) : src(src), to(to), cost(cost) {}
};

template <typename T>
using Edges = vector<Edge<T>>;
template <typename T>
using AdjList = vector<Edges<T>>;

template <typename T>
class Kruskal {
    private:
        int V;  
        Edges<T> edges;
        AdjList<T> minimumSpanningTree;

    public:
        explicit Kruskal(int n);
        void AddEdge(int from, int to, T cost);
        T Run();
        AdjList<T> GetMinimumSpanningTree();
};

template <typename T>
Kruskal<T>::Kruskal(int n) : V(n), minimumSpanningTree(n) {}

template <typename T>
void Kruskal<T>::AddEdge(int from, int to, T cost) {
    edges.push_back(Edge<T>(from, to, cost));
}

template <typename T>
T Kruskal<T>::Run() {
    sort(edges.begin(), edges.end(),
            [](const Edge<T> &a, const Edge<T> &b) { return a.cost < b.cost; });
    UnionFind tree(V);
    T total = 0;

    for (auto &e : edges) {
        if (!tree.Same(e.src, e.to)) {
            tree.Unite(e.src, e.to);
            total += e.cost;
            minimumSpanningTree[e.src].push_back(Edge<T>(e.to, e.cost));
            minimumSpanningTree[e.to].push_back(Edge<T>(e.src, e.cost));
        }
    }

    return total;
}

template <typename T>
AdjList<T> Kruskal<T>::GetMinimumSpanningTree() {
    return minimumSpanningTree;
}

signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    int n;
    cin >> n;
    vector<TP> p(n);
    Kruskal<int> pri(n);
    REP(i, n) {
        int x, y;
        cin >> x >> y;
        p[i] = make_tuple(x, y, i);
    }
    
    sort(all(p), [](TP a, TP b){return get<0>(a) < get<0>(b);});
    REP(i, n-1) pri.AddEdge(get<2>(p[i]), get<2>(p[i+1]), get<0>(p[i+1]) - get<0>(p[i]));

    sort(all(p), [](TP a, TP b){return get<1>(a) < get<1>(b);});
    REP(i, n-1) pri.AddEdge(get<2>(p[i]), get<2>(p[i+1]), get<1>(p[i+1]) - get<1>(p[i]));

    cout << pri.Run() << endl;

}

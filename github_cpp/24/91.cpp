//common
typedef long long Weight;
const Weight WEIGHT_INF = std::numeric_limits<Weight>::max()/4;

struct Edge {
    int src, dst;
    Weight weight;
};
bool operator<(const Edge& a, const Edge& b) {
    return (a.weight < b.weight);
};
bool operator>(const Edge& a, const Edge& b) {
    return (a.weight > b.weight);
};
typedef std::vector<Edge> Edges;
typedef std::vector<Edges> Graph;

//Prim(Graph ver)(O(E log V))
Graph g;
Edges msTree;
Weight prim(int r) {
    int n = g.size();
    Weight total = 0;
    std::vector<bool> visited(n, false);
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > que;
    que.push(Edge{-1, r, 0});
    while(!que.empty()) {
        Edge e = que.top();
        que.pop();
        if(visited[e.dst]) continue;
        msTree.push_back(e);
        total += e.weight;
        visited[e.dst] = true;
        for(auto ce: g[e.dst]){
            if(!visited[ce.dst]) {
                que.push(ce);
            }
        }
    }
    return total;
}

//Prim(Table ver)
std::vector< std::vector< Weight > > costs;
Weight prim(int r) {
    int n = costs.size();
    Weight total = 0;
    std::vector<bool> visited(n, false);
    std::priority_queue< std::pair<Weight,int>, std::vector< std::pair<Weight,int> >, std::greater< std::pair<Weight,int> > > que;
    que.push(std::make_pair(0, r));
    while(!que.empty()) {
        auto p = que.top();
        que.pop();

        if(visited[p.second]) continue;
        total += p.first;
        visited[p.second] = true;
        REP(i, n) {
            if(costs[p.second][i] >= 0 && !visited[i] ) {
                que.push(std::make_pair(costs[p.second][i], i));
            }
        }
    }
    return total;
}

//Kruskal(O(E log V + A(E) E))
//use union-find tree
template<class T> struct UnionFind {
    std::vector<T> data;
    UnionFind(){};
    UnionFind(T size): data(size, -1){};
    void init(T size) {
        data.resize(size, -1);
    }
    T root(T x) {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
    bool same(T x, T y) {
        return root(x) == root(y);
    }
    T size(T x) {
        return -data[root(x)];
    }
    bool unite(T x, T y) {
        x = root(x);
        y = root(y);
        if(x != y){
            if(data[y] < data[x]){
                std::swap(x, y);
            }
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }
};

Edges edges;
UnionFind<int> uf;
Edges msTree;
Weight kruskal(int r) {
    int n = g.size();
    std::sort(edges.begin(), edges.end());
    int cnt = 0;
    Weight total = 0;
    msTree.reserve(n-1);
    for(auto e: edges) {
        if(cnt >= n-1) break;

        if(uf.unite(e.src, e.dst)) {
            total += e.weight;
            msTree.pb(e);
            cnt++;
        }
    }
    return total;
}


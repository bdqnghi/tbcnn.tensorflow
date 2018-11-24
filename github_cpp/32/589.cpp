#include "template.cpp"
#include "unionfind.cpp"



/* unionfindを使います */

class kruskal
{
private:
    struct edge{
        long long cost, u, v;
        
        bool operator<(const edge& e1) const {
            return cost < e1.cost;
        }
    };
    vector<edge> es;
    long long vertex;    // vertexは頂点の数
public:
    kruskal(long long n);   // nは頂点数
    void add_edge(long long u, long long v, long long cost);    // 頂点uから頂点vにコストcostの辺を貼る
    long long run();
};

kruskal::kruskal(long long n){
    vertex = n;
}

void kruskal::add_edge(long long u, long long v, long long cost){
    es.push_back({cost, u, v});
    es.push_back({cost, v, u});
}

long long kruskal::run(){
    sort(es.begin(), es.end());
    
    unionfind uni(vertex);
    long long res = 0;
    
    for(auto e : es){
        if(!uni.same(e.u, e.v)){
            uni.unite(e.u, e.v);
            res += e.cost;
        }
    }
    
    return res;
}
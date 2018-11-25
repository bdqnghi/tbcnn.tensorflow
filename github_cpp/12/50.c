



#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge{
    int u;
    int v;
    int weight;
    friend bool operator<(const Edge& edge1, const Edge& edge2){
        return edge1.weight < edge2.weight;
    }
};

class MinimumSpanningTree{
private:
    vector<Edge> edges;
    int node;
public:
    MinimumSpanningTree(){}
    void init(vector<Edge> edges, int node){
        this->edges = edges;
        this->node = node;
    }

    void makeSet(vector<int>& v, int n){
        v.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            v[i] = i;
        }
    }

    int findSet(vector<int>& v, int v1_u){
        auto v1_s = v1_u;
        while(v[v1_s]!=v1_s){
            v1_s = v[v1_s];
        }

        return v1_s;
    }

    void kruskal(){
        
        vector<int> v;
        
        vector<Edge> spanningTree;
        
        auto weights = 0;
        auto e1 = 0, e2 = 0;
        
        makeSet(v, node);

        for (int i = 0; i < edges.size(); ++i) {
            e1 = findSet(v, edges[i].u);
            e2 = findSet(v, edges[i].v);
            if(e1!=e2){
                spanningTree.push_back(edges[i]);
                weights+=edges[i].weight;
                v[e1] = e2;
            }
        }

        cout << "kruskal result:" << endl;
        for (int i = 0; i < spanningTree.size(); ++i) {
            cout << spanningTree[i].u << " " << spanningTree[i].v << endl;
        }
        cout << "weights: " << weights << endl;
    }
};

int main(){
    auto node = 0;
    auto edgeNum = 0;
    
    cin >> node >> edgeNum;
    vector<Edge> edges;
    edges.assign(edgeNum, Edge());
    
    for (int i = 0; i < edgeNum; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(),edges.end());

    MinimumSpanningTree minimumSpanningTree;
    minimumSpanningTree.init(edges, node);

    minimumSpanningTree.kruskal();
}




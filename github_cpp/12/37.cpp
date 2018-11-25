


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
    int startPoint;
public:
    MinimumSpanningTree(){}
    void init(vector<Edge> edges, int node, int startPoint){
        this->edges = edges;
        this->node = node;
        this->startPoint = startPoint;
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

    void prim(){
        
        vector<int> v;
        
        vector<int> pointers;
        
        vector<Edge> spanningTree;
        
        auto weights = 0;
        auto e1 = 0, e2 = 0;
        
        makeSet(v, node);
        pointers.push_back(startPoint);

        bool isAdd;
        while(spanningTree.size()!=node-1){
            isAdd = false;
            for (int i = 0; i < edges.size(); ++i) {
                
                for (int j = 0; j < spanningTree.size(); ++j) {
                    if(spanningTree[j].u == edges[i].u && spanningTree[j].v == edges[i].v)
                        continue;
                }

                
                for (int j = 0; j < pointers.size(); ++j) {
                    if(edges[i].u == pointers[j] || edges[i].v == pointers[j]){
                        e1 = findSet(v, edges[i].u);
                        e2 = findSet(v, edges[i].v);
                        
                        if(e1!=e2){
                            spanningTree.push_back(edges[i]);
                            weights+=edges[i].weight;
                            v[e1] = e2;

                            if(edges[i].u == pointers[j]){
                                pointers.push_back(edges[i].v);
                            }else if(edges[i].v == pointers[j]){
                                pointers.push_back(edges[i].u);
                            }

                            isAdd = true;
                        }

                        break;
                    }
                }

                if(isAdd){
                    break;
                }
            }
        }

        cout << "prim algorithm result:" << endl;
        for (int i = 0; i < spanningTree.size(); ++i) {
            cout << spanningTree[i].u << " " << spanningTree[i].v << endl;
        }
        cout << "weights: " << weights << endl;
    }
};

int main(){
    auto node = 0;
    auto edgeNum = 0;
    auto startPoint = 0;
    
    cin >> node >> edgeNum;
    vector<Edge> edges;
    edges.assign(edgeNum, Edge());
    
    for (int i = 0; i < edgeNum; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(),edges.end());

    MinimumSpanningTree minimumSpanningTree;
    minimumSpanningTree.init(edges, node, startPoint);

    minimumSpanningTree.prim();
}

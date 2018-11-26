//
// Created by ly on 2018/8/16.
//

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
        //Union-Find
        vector<int> v;
        //store edges
        vector<Edge> spanningTree;
        //weight
        auto weights = 0;
        auto e1 = 0, e2 = 0;
        //init
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
    //input the number of nodes and edges
    cin >> node >> edgeNum;
    vector<Edge> edges;
    edges.assign(edgeNum, Edge());
    //Enter the start, end, and side length of each edge
    for (int i = 0; i < edgeNum; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(),edges.end());

    MinimumSpanningTree minimumSpanningTree;
    minimumSpanningTree.init(edges, node);

    minimumSpanningTree.kruskal();
}

/*
 * input
 *
7 11
0 1 7
0 3 5
1 2 8
1 4 7
1 3 9
2 4 5
3 4 15
3 5 6
4 5 8
4 6 9
5 6 11


7 12
0 1 12
0 5 16
0 6 14
1 2 10
1 5 7
2 5 6
2 4 5
2 3 3
3 4 4
4 5 2
4 6 8
5 6 9
 */


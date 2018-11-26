//
//  main.cpp
//  Graph Algorithm Prim's Algorithm Minimum Spanning Tree
//
//  Created by Zijian Xie on 2016/11/15.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//

#include <iostream>
#include <climits>
#include <vector>
#include <list>
#include <queue>
using namespace std;

const int INF = INT_MAX;
class edge{
public:
    int start;
    int end;
    int weight;
    edge(){}
    edge(int start, int end, int weight){
        this->start = start;
        this->end = end;
        this->weight = weight;
    }
    bool operator<(edge& b){
        return this->weight < b.weight;
    }
};

vector<edge> primAlgorithm(vector<list<pair<int,int>>> graph, edge minEdge){
    vector<edge> spanningTree;
    priority_queue<edge,vector<edge>> Q;
    while(spanningTree.size() == graph.size()-1){
        spanningTree.push_back(minEdge);
        for(auto it : graph[minEdge.start]){
            Q.push(edge(minEdge.start,it.first, it.second));
        }
        for(auto it : graph[minEdge.end]){
            Q.push(edge(minEdge.end,it.first, it.second));
        }
        minEdge = Q.top();
        Q.pop();
    }
    return spanningTree;
}

int main(){
    vector<list<pair<int,int>>>graph;
    int v,e,src,des,weight;
    cin >> v >> e;
    graph.resize(v);
    edge minEdge;
    minEdge.weight = INF;
    while(e--){
        cin >> src >> des >> weight;
        graph[src].push_back(make_pair(des,weight));
        graph[des].push_back(make_pair(src,weight));
        if(weight < minEdge.weight){
            minEdge.start = src, minEdge.end = des, minEdge.weight = weight;
        }
    }
    vector<edge> spanningTree = primAlgorithm(graph,minEdge);
    for(edge x : spanningTree){
        cout << x.start << " " << x.end << " " << x.weight << endl;
    }
    return 0;
}

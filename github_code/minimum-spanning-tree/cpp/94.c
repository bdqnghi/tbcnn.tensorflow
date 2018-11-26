//
//  main.cpp
//  Graph Algorithm - Kruskal's Minimum Spanning Tree Algorithm
//
//  Created by Zijian Xie on 2016/11/15.
//  Copyright © 2016年 Jason Xie. All rights reserved.
// Time complexity: O(vlogv); Space: O(v+e)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class edge{
public:
    int start;
    int des;
    int weight;
    edge(){}
    edge(int start, int des, int weight){
        this->start = start;
        this->des = des;
        this->weight = weight;
    }
    /*
    bool operator<(edge& b){
        if(this->weight < b.weight) return true;
        return false;
    }
    bool operator>(edge& b){
        if(this->weight > b.weight) return true;
        return false;
    }
    bool operator==(edge& b){
        if(this->weight == b.weight) return true;
        return false;
    }*/
};

class UnionFind{
private:
    vector<int> parent;
    vector<int> ranks;
    int _size;
public:
    UnionFind(){}
    UnionFind(int size){
        parent.resize(size);
        ranks.resize(size);
        for(int i = 0; i < size; ++i){
            parent[i] = i;
            ranks[i] = 0;
        }
        _size = size;
    }
    void resize(int size){
        parent.resize(size);
        ranks.resize(size);
        for(int i = 0; i < size; ++i){
            parent[i] = i;
            ranks[i] = 0;
        }
        _size = size;
    }
    int find(int val){
        if(parent[val] == val){
            return val;
        }else{
            val = parent[parent[val]];
        }
        return val;
    }
    bool connected(int a, int b){
        if(find(a) == find(b)) return true;
        return false;
    }
    void merge(int a, int b){
        if(connected(a, b)) return;
        int pa = find(a);
        int pb = find(b);
        if(ranks[pa] > ranks[pb]){
            parent[pb] = parent[pa];
        }else if(ranks[pa] < ranks[pb]){
            parent[pa] = parent[pb];
        }else{
            parent[pb] = parent[pa];
            ranks[pa]++;
        }
        _size--;
    }
    
    void clear(){
        parent.clear();
        ranks.clear();
    }
    int size(){
        return _size;
    }
};

class MinSpanningTree{
private:
    vector<edge> graph;
    int vertices;
public:
    MinSpanningTree(vector<edge>& graph, int vertices){
        this->graph = graph;
        this->vertices = vertices;
    }
    vector<edge> KruskalAlgorithm(){
        UnionFind uf(vertices);
        vector<edge> spanningTree;// the return res
        sort(graph.begin(), graph.end(),[](edge a, edge b){
            return a.weight < b.weight;
        });
        spanningTree.push_back(graph[0]);
        uf.merge(graph[0].start, graph[0].des);
        for(int i = 1; i < graph.size(); ++i){
            if(!uf.connected(graph[i].start, graph[i].des)){
                uf.merge(graph[i].start, graph[i].des);
                spanningTree.push_back(graph[i]);
            }
        }
        return spanningTree;
    }
};

int main(int argc, const char * argv[]) {
    vector<edge> graph;
    int e, v;
    cout<<"Please input e = ";
    cin>>e;
    cout<<"Please input v = ";
    cin>>v;
    graph.resize(e);
    cout<<"Please input start, end and weight: "<<endl;
    for(int i = 0; i < e; ++i){
        cin>>graph[i].start;
        cin>>graph[i].des;
        cin>>graph[i].weight;
        cout<<"Finished " << i+1 <<" vertice(s) information."<<endl;
    }
    MinSpanningTree* test = new MinSpanningTree(graph,v);
    vector<edge> spanningTree = test->KruskalAlgorithm();
    int res = 0;
    for(auto x : spanningTree){
        cout<<x.start<<" "<<x.des<<" "<<x.weight<<" "<<endl;
        res += x.weight;
    }
    cout<<"Min weights is: "<<res<<endl;
    return 0;
}

/*
Test:
0,3,1
1,2,1
2,3,1
4,5,2
1,3,3
0,1,3
2,5,4
2,4,5
3,4,6
*/

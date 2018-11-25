#include <climits>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

struct Edge { int to, length; };

struct Node {
    vector<Edge> edges;
    
    Node() {
        edges.reserve(16);
    }
};

void readGraph(vector<Node> &graph) {
    int iNodes, iEdges;
    cin >> iNodes >> iEdges;
    graph.resize(iNodes);
    
    for (int i = 0; i < iEdges; ++i) {
        int src, dest, dist = 6;
        struct Edge myEdge;
        cin >> src >> dest;
        --src, --dest;
        myEdge.to = dest;
        myEdge.length = dist;
        graph[src].edges.push_back(myEdge);
        myEdge.to = src;
        
        graph[dest].edges.push_back(myEdge);        
    }
}

void dijkstra(vector<int> &minDist, const vector<Node> &graph, int source) {
    int graphSize = graph.size();
    minDist.resize(graphSize, INT_MAX);
    minDist[ source ] = 0;
    
    set< pair<int,int> > active_vertices;
    active_vertices.insert( {0,source} );
    while (!active_vertices.empty()) {
        int where = active_vertices.begin()->second;
        active_vertices.erase( active_vertices.begin() );
        for (auto edge : graph[where].edges) 
            if (minDist[edge.to] > minDist[where] + edge.length) {
                active_vertices.erase( { minDist[edge.to], edge.to } );
                minDist[edge.to] = minDist[where] + edge.length;
                active_vertices.insert( { minDist[edge.to], edge.to } );
            }
    }
    
    for (int &dist : minDist)
        if (dist == INT_MAX)
            dist = -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    int t, source;
    cin >> t;
    
    while (t--) {
        vector<Node> graph;
        vector<int> minDist;
        readGraph(graph);
        cin >> source;
        dijkstra(minDist, graph, --source);
        
        for (int dist : minDist)
            if (dist)
                cout << dist << " ";
        cout << endl;
    }
    
    return 0;
}

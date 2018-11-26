#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <limits.h>
#include <string.h>
#include "../graph/graph.h"
#include "../graph/graph.cpp"

const int vertexCount = 1000;

Graph readGraph() {
    Graph graph = Graph(vertexCount);
    int head, tail, cost;
    std::ifstream infile("graph");
    while (infile >> head >> tail >> cost) {
	graph.addEdge(head, tail, cost);
    }
    return graph;
}

bool bfs(int residualGraph[vertexCount*vertexCount], int source, int drain, int parent[]) {
    bool visited[vertexCount];
    memset(visited, 0, sizeof(visited));
 
    std::queue <int> fringe;
    fringe.push(source);
    visited[source] = true;
    parent[source] = -1;
 
    while (!fringe.empty()) {
        int node = fringe.front();
        fringe.pop();
	for (int child = 0; child < vertexCount; child++) {
            if (!visited[child] && residualGraph[node + vertexCount*child] > 0) {
                fringe.push(child);
                parent[child] = node;
                visited[child] = true;
            }
        }
    }
    return (visited[drain]);
}

int fordFulkerson(Graph graph, int source, int drain) {
    int u, v;
    int parent[vertexCount];
    int max_flow = 0;
    int residualGraph[vertexCount*vertexCount];
    for (u = 0; u < vertexCount; u++)
        for (v = 0; v < vertexCount; v++)
	    residualGraph[u + vertexCount*v] = graph.getCost(u,v);
 
    while (bfs(residualGraph, source, drain, parent))  {
        int path_flow = INT_MAX;
        for (v=drain; v!=source; v=parent[v]) {
            u = parent[v];
            path_flow = std::min(path_flow, residualGraph[u + vertexCount*v]);
        }
        for (v=drain; v != source; v=parent[v]) {
            u = parent[v];
            residualGraph[u + vertexCount*v] -= path_flow;
            residualGraph[v + vertexCount*u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    int source = 109;
    int drain = 609;
    Graph graph = readGraph();
    int maxOutFlow = 0;
    int maxInFlow = 0;
    for (int u = 0; u < vertexCount; u++) {
	if(graph.getCost(source, u) > 0)
	    maxOutFlow += graph.getCost(source, u);
	if(graph.getCost(u, drain) > 0)
	    maxInFlow += graph.getCost(u, drain);
    }
    std::cout<<"Maximal flow: "<<fordFulkerson(graph, source, drain)<<std::endl;
    std::cout<<"Maximal out flow: "<<maxOutFlow<<std::endl;
    std::cout<<"Maximal in flow: "<<maxInFlow<<std::endl;
    return 0;
}

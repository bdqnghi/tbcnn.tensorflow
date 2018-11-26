#include "graph.h"
#include <iostream>

class DepthFirstSearch {
    private:
        const Graph* graph;
        int s;
        bool* visited;
        int count;
        void dfs(const Graph* g, int v);
    public:
        DepthFirstSearch(const Graph * graph, int s);
        bool isConnectedToSource(int v) const;
        int visitedVertices() const;
};

DepthFirstSearch::DepthFirstSearch(const Graph *graph, int s) {
    this->graph = graph;
    this->s = s;
    this->count = 1;
    visited = new bool[this->graph->vertices()] {false};
    dfs(this->graph, s);
}

/*
 * The time taken is proportional to the sum of the the vertices degrees.
 * Incident: if there is an edge connecting two vertices, the edge is said to be indicent
 *           to the vertices.
 * Degree: the degree of a vertex is the number of edges incident to it.
 */
void DepthFirstSearch::dfs(const Graph *g, int v) {
    visited[v] = true; // first step is to mark the vertex as visited
    count++;
    Iterator<int>* it = g->adjacent(v);
    while(it->hasNext()) {
        int w = it->next();
        if (!visited[w]) {
            dfs(g, w);
        }
    }
}

auto DepthFirstSearch::isConnectedToSource(int v) const -> bool {
    std::cout << __func__ << ": is " << v << " connected to " << s << std::endl;
    return visited[v];
}

auto DepthFirstSearch::visitedVertices() const -> int {
    return count;
}

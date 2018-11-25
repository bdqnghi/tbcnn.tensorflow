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


void DepthFirstSearch::dfs(const Graph *g, int v) {
    visited[v] = true; 
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

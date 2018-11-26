#include "DepthFirstSearch.h"

namespace ycg {

DepthFirstSearch::DepthFirstSearch(const DirectedGraphAdjMatrix *graph) {
    this->graph = graph;
    int nVertex = graph->numberOfVertex();
    color = new int[nVertex];
    discover = new int[nVertex];
    finish = new int[nVertex];
    prev = new int [nVertex];
}

DepthFirstSearch::~DepthFirstSearch() {
    delete []color;
    delete []discover;
    delete []finish;
    delete []prev;
}

int DepthFirstSearch::search() {
    for (int u = 0; u < graph->numberOfVertex(); ++u) {
        color[u] = WHITE;
        prev[u] = NIL;
    }

    int count = 0;
    time = 0;
    for (int u = 0; u < graph->numberOfVertex(); ++u) {
        if (color[u] == WHITE) {
            visit(u);
            ++count;
        }
    }
    return count;
}

void DepthFirstSearch::visit(int u) {
    color[u] = GRAY;
    discover[u] = time++;

    for (int v = 0; v < graph->numberOfVertex(); ++v) {
        if (graph->existEdge(Edge(u,v)) && color[v] == WHITE) {
            prev[v] = u;
            visit(v);
        }
    }

    color[u] = BLACK;
    finish[u] = time++;
}

} //~ namespace ycg

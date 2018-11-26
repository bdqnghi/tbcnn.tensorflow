#include "TopologicalSort.h"

namespace ycg {

TopologicalSort::TopologicalSort(const DirectedGraphAdjMatrix* graph) {
    int nVertex = graph->numberOfVertex();
    color = new int[nVertex];
    sequence = new int[nVertex];
    this->graph = graph;
}

TopologicalSort::~TopologicalSort() {
    delete []color;
    delete []sequence;
}

void TopologicalSort::sort() {
    acyclic = true;
    nsequence = graph->numberOfVertex();
    dfs();
}

void TopologicalSort::dfs() {
    for (int u = 0; u < graph->numberOfVertex(); ++u) {
        color[u] = WHITE;
    }
    for (int u = 0; u < graph->numberOfVertex() && acyclic; ++u) {
        if (color[u] == WHITE) {
            visit(u);
        }
    }
}

void TopologicalSort::visit(int u) {
    color[u] = GRAY;
    for (int v = 0; v < graph->numberOfVertex(); ++v) {
        if (graph->existEdge(Edge(u,v))) {
            if (color[v] == WHITE) {
                visit(v);
                if (!acyclic) return;
            } else if (color[v] == GRAY) {
                acyclic = false;
                return;
            }
        }
    }
    color[u] = BLACK;
    sequence[--nsequence] = u;
}

} //~ namespace ycg

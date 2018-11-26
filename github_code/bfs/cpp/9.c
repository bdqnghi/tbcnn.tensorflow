#include "BreadthFirstSearch.h"

namespace ycg {

/*
 * G: The graph to be traveled.
 * S: Source Vertex
 */
BreadthFirstSearch::BreadthFirstSearch(const DirectedGraphAdjMatrix *graph, int source) {
    this->graph = graph;
    this->sourceVertex = source;
    int nVertex = graph->numberOfVertex();
    color = new int[nVertex];
    distance = new int[nVertex];
    prev = new int[nVertex];
}

BreadthFirstSearch::~BreadthFirstSearch() {
    delete []color;
    delete []distance;
    delete []prev;
}

void BreadthFirstSearch::search() {
    const DirectedGraphAdjMatrix &G = *graph;

    int nVertex = G.numberOfVertex();
    for (int i = 0; i < nVertex; ++i) {
        color[i] = WHITE;
        distance[i] = +OO;
        prev[i] = NIL;
    }

    color[sourceVertex] = GRAY;
    distance[sourceVertex] = 0;
    prev[sourceVertex] = NIL;
    Queue<int> Q(nVertex);
    Q.enqueue(sourceVertex);
    while (!Q.isEmpty()) {
        int u = Q.dequeue();
        for (int v = 0; v < nVertex; ++v) {
            if (G[u][v] && color[v] == WHITE) {
                color[v] = GRAY;
                distance[v] = distance[u] + 1;
                prev[v] = u;
                Q.enqueue(v);
            }
        }
        color[u] = BLACK;
    }
}

bool BreadthFirstSearch::queryReachable(int v) {
    return distance[v] < +OO;
}

int BreadthFirstSearch::queryShortestDistance(int v) {
    return distance[v];
}

void BreadthFirstSearch::printShortestPath(int v) {

}

} //~ namespace ycg

#include "topologicalsort.h"

TopologicalSort::TopologicalSort(int initial, int final, Graph *graph)
{
    this->InitialVertex = initial;
    this->FinalVertex   = final;
    this->graph = graph;
}

Queue<Vertex> *TopologicalSort::getQueue()
{
    return &queue;
}

void TopologicalSort::run()
{
    Vertex **V = graph->getVertex();
    int n = graph->getVertexCount();

    for(int i = 0; i < n; i++) {
        V[i]->setParent(NULL);
        V[i]->setEntranceTime(INFINITO);
        V[i]->setExitTime(INFINITO);
        V[i]->setColor(Qt::white);
    }

    time = 0;

    for(int i = InitialVertex; i < n; i++) {
        if(V[i]->getColor() == Qt::white) {
            visit(V[i]);
        }
    }

    emit finished();
}

void TopologicalSort::visit(Vertex *vertex)
{
    Edge *edge; Vertex *actualVertex;

    vertex->setColor(Qt::gray);
    emit repaint();
    sleep(1);

    vertex->setEntranceTime(time++);

    for(edge = vertex->getEdge(); edge != NULL; edge = edge->getNext()) {
        actualVertex = graph->getVertex()[edge->getTargetID()];

        if(actualVertex->getColor() == Qt::white) {
            actualVertex->setParent(vertex);
            visit(actualVertex);
        }
    }

    vertex->setExitTime(time++);
    vertex->setColor(Qt::black);
    queue.append(vertex);

    emit repaint();

    sleep(1);
}

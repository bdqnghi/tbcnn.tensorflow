#include <QDebug>
#include <QList>
#include "fordfulkerson.h"

void FordFulkerson::fordFulkerson() {
    Vertice **V = g->getVertice();
    Aresta *a;
    QList<Aresta*> pathList;
    int n = g->getVerticeCount();
    for(int i = 0; i < n; i++) {
        V[i]->setCor(Qt::white);
        a = V[i]->getAresta();
        while(a != NULL) {
            a->setCapacity(a->getW());
            a->setFlow(0);
            a = a->getNext();
        }
    }
    emit colorChanged();

    findPath(pathList, V, V[source]);

}

void FordFulkerson::findPath(QList<Aresta*> pathList, Vertice **V, Vertice *currentVertice) {
    Aresta *a;
    currentVertice->setCor(Qt::gray);
    emit colorChanged();
    sleep(1);
    
    if(currentVertice->getId() == target) {
        calculateFlow(pathList);
        currentVertice->setCor(Qt::white);
        emit colorChanged();
        sleep(1);
    } else {
        a = currentVertice->getAresta();
        while(a != NULL) {
            
            if(a->getCapacity() > 0 && V[a->getIdV2()]->getCor() == Qt::white) {
                pathList.append(a);
                findPath(pathList, V, V[a->getIdV2()]);
                pathList.removeLast();
            }
            a = a->getNext();
        }
        currentVertice->setCor(Qt::white);
        emit colorChanged();
        sleep(1);
    }
}

void FordFulkerson::calculateFlow(QList<Aresta*> pathList) {
    int menor = INF;
    for(int i = 0; i < pathList.size(); i++) {
        if(pathList.at(i)->getCapacity() < menor) {
            menor = pathList.at(i)->getCapacity();
        }
    }
    maxFlow += menor;
    qDebug() << menor;
    for(int i = 0; i < pathList.size(); i++) {
        pathList.at(i)->decreaseCapacity(menor);
        pathList.at(i)->increaseFlow(menor);
        qDebug() << pathList.at(i)->getFlow() << " / " << pathList.at(i)->getCapacity();
    }
    emit colorChanged();
    sleep(1);
}

int FordFulkerson::getMaxFlow() {
    return this->maxFlow;
}

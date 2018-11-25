#include <QList>
#include "breadthfirstsearch.h"

void BreadthFirstSearch::bfs() {
    QList<Vertice *> f;
    Vertice **v = g->getVertice();
    Vertice *v_aux, *v_atual;
    Aresta *a;
    int i;

    for (i = 0; i < g->getVerticeCount(); i++) {
        v[i]->setPai(NULL);
        v[i]->setCor(Qt::white);
        v[i]->setD(INF);
    }
    v[initial]->setD(0);

    f.append(v[initial]);

    while(!f.isEmpty()) {
        v_atual = f.takeFirst();
        v_atual->setCor(Qt::darkGray);
        emit colorChanged();
        sleep(1);
        for(a = v_atual->getAresta(); a != NULL; a = a->getNext()) {
            v_aux = v[a->getIdV2()];
            if(v_aux->getCor() == Qt::white) {
                v_aux->setCor(Qt::gray);
                emit colorChanged();
                sleep(1);
                v_aux->setPai(v_atual);
                v_aux->setD(v_atual->getD()+1);
                f.append(v_aux);
            }
        }
        v_atual->setCor(Qt::black);
        emit colorChanged();
        sleep(1);
    }
}

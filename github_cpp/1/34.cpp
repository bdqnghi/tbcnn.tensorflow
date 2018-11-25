

#include "breadthfirstsearch.h"

#include "graph/digraph.h"
#include "graph/vertex.h"
#include "graph/arc.h"
#include "property/propertymap.h"

#include <deque>

namespace Algora {

BreadthFirstSearch::BreadthFirstSearch(bool computeValues)
    : PropertyComputingAlgorithm<bool, int>(computeValues),
      startVertex(0), maxBfsNumber(-1),
      onVertexDiscovered(vertexTrue), onArcDiscovered(arcTrue),
      vertexStopCondition(vertexFalse), arcStopCondition(arcFalse)
{

}

BreadthFirstSearch::~BreadthFirstSearch()
{

}

bool BreadthFirstSearch::prepare()
{
    return PropertyComputingAlgorithm<bool, int>::prepare()
            && ( startVertex == 0 || diGraph->containsVertex(startVertex));
}

void BreadthFirstSearch::run()
{
    if (startVertex == 0) {
        startVertex = diGraph->getAnyVertex();
    }

    std::deque<Vertex*> queue;
    PropertyMap<bool> discovered(false);
    PropertyMap<int> *bfsNumber = propertyMap;

    maxBfsNumber = 0;
    queue.push_back(startVertex);
    discovered[startVertex] = true;
    if (computePropertyValues) {
        (*bfsNumber)[startVertex] = maxBfsNumber;
    }

    bool stop = false;

    while (!stop && !queue.empty()) {
        Vertex *curr = queue.front();
        queue.pop_front();
        stop |= vertexStopCondition(curr);
        if (stop) {
            break;
        }

        diGraph->mapOutgoingArcsUntil(curr, [&](Arc *a) {
            bool consider = onArcDiscovered(a);
            stop |= arcStopCondition(a);
            if (stop || !consider) {
                return;
            }
            Vertex *head = a->getHead();
            if (!discovered(head)) {
                if (!onVertexDiscovered(head)) {
                    return;
                }

                queue.push_back(a->getHead());
                discovered[head] = true;
                maxBfsNumber++;
                if (computePropertyValues) {
                    (*bfsNumber)[head] = maxBfsNumber;
                }
            }
        }, [&](const Arc *) { return stop; });
    }
}

bool BreadthFirstSearch::deliver()
{
    return maxBfsNumber + 1 == (int) diGraph->getSize();
}

void BreadthFirstSearch::onDiGraphSet()
{
    maxBfsNumber = -1;
}

}

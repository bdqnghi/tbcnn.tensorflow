#include "breadthfirstsearch.h"

BreadthFirstSearch::BreadthFirstSearch(std::vector<Vertex *> &vertices) :
        Search(vertices) {
}

Vertex *BreadthFirstSearch::oneStep(Vertex* current, ushort, ushort) {
        if(queue.size() == 0) {
            queue.push_back(current);
        }
        for(auto& vertex:current->connections) {
            if(vertex->visited == false) {
                queue.push_back(vertex);
                vertex->lengthMinWay = current->lengthMinWay+1;
                vertex->visited = true;
            }
        }
        if(queue.size() > 1) {
            queue.erase(queue.begin());
        }
        return queue[0];
}

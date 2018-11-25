#include "depthfirstsearch.h"

DepthFirstSearch::DepthFirstSearch(std::vector<Vertex *> &vertices) :
    Search(vertices) {
}

Vertex* DepthFirstSearch::oneStep(Vertex* current, ushort, ushort) {
        if(queue.size() == 0) {
            queue.push_back(current);
        }
        for(auto& vertex:current->connections) {
            if(vertex->visited == false) {
                queue.push_back(vertex);
                vertex->visited = true;
                vertex->lengthMinWay = current->lengthMinWay+1;
                return vertex;
            }
        }
        if(queue.size() > 1) {
            queue.erase(queue.end()-1);
            return queue[queue.size()-1];
        } else {
            return queue[0];
        }
}

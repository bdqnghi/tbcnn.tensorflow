#include "breadth_first_search.hpp"

BreadthFirstSearch::BreadthFirstSearch()
{
    searchGraph = nullptr;
    start = nullptr;
    endCount = nowCount = 0;
}

BreadthFirstSearch::BreadthFirstSearch(EmbeddedGraph* _graph)
{
    searchGraph = _graph;
    start = nullptr;
    endCount = nowCount = 0;
}

BreadthFirstSearch::~BreadthFirstSearch()
{
    
}

void BreadthFirstSearch::init(EmbeddedEdge* _start, bool _clockwise)
{
    start = _start;
    clockwise = _clockwise;
    for (int i = 0; i < GraphProperty::MAX_VERTEX; ++i)
        visited[i] = false;

    int waitingRealCount = 0;
    int waitnigNowCount = 0;
    int count = 0;
    EmbeddedEdge *now, *end;

    waiting[waitingRealCount++] = start;
    while (waitingRealCount != waitnigNowCount) {
        now = end = waiting[waitnigNowCount++];
        visited[now->getStart()] = true;

        do {
            if (!visited[now->getEnd()]) {
                waiting[waitingRealCount++] = now->getInverse();
                visited[now->getEnd()] = true;
            }
            order[count++] = now;
            now = (clockwise) ? now->getNext() : now->getPrev();
        } while (now != end);
    }

    endCount = count;
    nowCount = 0;
}

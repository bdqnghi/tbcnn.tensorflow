#include "breadthfirstsearch.h"

BreadthFirstSearch::BreadthFirstSearch()
{

}

QList<StateSpace *> *BreadthFirstSearch::search(StateSpace *startState)
{
    Node *startNode = new Node(startState, nullptr);
    QList<Node*> *explored = new QList<Node*>();
    QQueue<Node*> *frontier = new QQueue<Node*>();
    Node *currentNode = new Node();
    frontier->enqueue(startNode);


    while (frontier->length() > 0) {
        currentNode = frontier->dequeue();
        if (currentNode->getCurrentState()->isItGoal()) {
            break;
        }

        for (Direction dir: Operator::dirs) {
            Operator *o = new Operator(dir);
            if (o->precondition(currentNode->getCurrentState())) {
                Node *newNode = new Node(o->apply(currentNode->getCurrentState()), currentNode);
                if (!explored->contains(newNode) && !frontier->contains(newNode)) {
                    explored->append(newNode);
                    newNode->setParent(currentNode);
                    frontier->enqueue(newNode);
                }
            }
            delete o;
        }
        explored->append(currentNode);
    }

    QList<StateSpace*> *solution = new QList<StateSpace*>();
    if (frontier->count() > 0) {
        Node *curr = currentNode;
        for (;  curr != nullptr; curr = curr->getParent()) {
            solution->push_front(curr->getCurrentState());
        }
    }
    return solution;
}

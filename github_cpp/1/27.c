
#include "Bfs.h"
#include "Node.h"
using namespace std;
#include <list>
#include <stack>


Bfs::Bfs(Node* startP){
    currPoint = startP;
    startMap = startP;
}

Bfs::Bfs(){}

Node* Bfs::getNext(vector<Node*> neighbors) {
    int nSize = neighbors.size();
    if(nSize == 0){
        return NULL;
    }
    
    
    if (nSize == 1) {
        if (!neighbors.at(0)->getIsObstacle()) {
            pointQue.push(neighbors.at(0));
            neighbors.at(0)->SetFather(currPoint);
        }
    } else {
        for (int i = 0; i < nSize; i++) {
            if (neighbors.at(i)->getIsVisited() <= 1) {
                pointQue.push(neighbors.at(i));
                neighbors.at(i)->SetFather(currPoint);
            }
        }
    }
    currPoint = pointQue.front();
    pointQue.pop();
    return currPoint;
}

void Bfs::printPath() {
    stack <Node*> printStack;
    while (!(currPoint==startMap)) {
        printStack.push(currPoint);
        currPoint = currPoint->getFather();
    }
    cout<<*startMap<<endl;
    while(!printStack.empty()) {
        cout<<*printStack.top()<<endl;
        printStack.pop();
    }
    delete(startMap);

}
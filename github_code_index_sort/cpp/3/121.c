#ifndef TOPOLOGICALSORT_H
#define TOPOLOGICALSORT_H
#include "DirectedGraph.h"
#include <set>
using namespace std;

template<typename T>
void topologicalSort(DirectedGraph<T>* g, GraphNode<T>* node, set<GraphNode<T>*>* gset){
    AdjacentNode<T>* adjNode = node->next;
    while(adjNode){
        if(gset->find(adjNode->node)==gset->end()){
            gset->insert(adjNode->node);
            topologicalSort(g, adjNode->node, gset);
        }
        adjNode = adjNode->next;
    }
    cout<<node->data<<" "; //when all the adjacent nodes have been visited print the node
    // so it will give reverse topological order
}

template<typename T>
void topologicalSort(DirectedGraph<T>* g){
    vector<GraphNode<T>*> list = g->getList();
    set<GraphNode<T>*> gset;
    for(int i=0; i<list.size(); i++){
        if(gset.find(list[i])==gset.end()){
            gset.insert(list[i]);
            topologicalSort(g, list[i], &gset);
        }
    }
}


#endif /* TOPOLOGICALSORT_H */










#include <stdio.h>
#include "adjacencyList.h"
#include <algorithm>

struct Edge {
    int from ;
    int to ;
    int weight ;
};



int mainMST()
{
    std::vector<std::vector<AdjacencyElement>*> *vector = constructGraphFromStandardInputWithMultipleWeight() ;
    
    if (vector->size() == 0) {
        return 0 ;
    }
    std::vector<Edge> vectorEdgeInMST ;
    std::vector<int> vectorVertexInMST ;
    vectorVertexInMST.push_back(0) ;
    
    while (vectorVertexInMST.size() != vector->size()) {
        Edge miniumEdge ;
        miniumEdge.weight = INT_MAX ;
        for (int i = 0; i < vectorVertexInMST.size(); ++i) {
            int vertexInMST = vectorVertexInMST[i] ;
            std::vector<AdjacencyElement> *list = (*vector)[vertexInMST] ;
            for (int j = 0; j < list->size(); ++j) {
                std::vector<int>::iterator iter = find(vectorVertexInMST.begin(), vectorVertexInMST.end(), (*list)[j].neighbor) ;
                if (iter != vectorVertexInMST.end()) {
                    continue ;
                }
                if ((*list)[j].weight < miniumEdge.weight) {
                    miniumEdge.weight = (*list)[j].weight ;
                    miniumEdge.from = vertexInMST ;
                    miniumEdge.to = (*list)[j].neighbor ;
                }
            }
        }
        if (miniumEdge.weight == INT_MAX) {
            printf("error!\n") ;
            break ;
        }
        vectorVertexInMST.push_back(miniumEdge.to) ;
        vectorEdgeInMST.push_back(miniumEdge) ;
    }
    
    for (std::vector<Edge>::iterator begin = vectorEdgeInMST.begin(); begin != vectorEdgeInMST.end(); ++begin) {
        printf("%d->%d weight:%d\n", begin->from, begin->to, begin->weight) ;
    }
    
    freeGraphWithMultipleWeight(vector) ;
    return 0 ;
}
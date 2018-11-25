

#include "MinimumSpanningTreeAlgorithm.h"

MinimumSpanningTreeAlgorithm::MinimumSpanningTreeAlgorithm(char const *inputFile)
{
	nE = 0;
	nV = 0;
	u = 0;
	v = 0;
	cost = 0;
	
	
    ifstream file_in(inputFile);
    file_in >> nV >> nE;
	
	
    edgeHeap = new EdgeHeap(nE);
	adjacencyList = new AdjacencyList(nV);
	
    for (int i = 1; i <= nE; i++)
    {
        file_in >> u >> v >> cost;
		edgeHeap->minHeapInsert(cost, u, v);
		adjacencyList->addVertex(u, v);
		adjacencyList->addVertex(v, u);
    }   
	
    file_in.close();	
}
/*************************************************************************
 * Developer: Raymond Tyler
 * File: MinimumSpanningTreeAlgorithm.cpp
 * Date: April 10, 2013
 *************************************************************************
 * Description: This is the implementation file for the MininimumSpanning-
 *				TreeAlgorithm abstract class. It defines the constructor
 *				for the abstract class that initializes both the Edge Heap, 
 *				and Adjacency List representations of an undirected, weighted
 *				graph that includes edges, vertices, and cost
 *************************************************************************/

#include "MinimumSpanningTreeAlgorithm.h"

MinimumSpanningTreeAlgorithm::MinimumSpanningTreeAlgorithm(char const *inputFile)
{
	nE = 0;
	nV = 0;
	u = 0;
	v = 0;
	cost = 0;
	
	//read from file
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
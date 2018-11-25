#include "graph.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct Graph
{
	int numberOfVertices;
	int **graphArray;
};

Graph *createGraphFromFile(const string &fileName)
{
	Graph *graph = new Graph;

	ifstream file(fileName);

	file >> graph->numberOfVertices;

	graph->graphArray = new int *[graph->numberOfVertices];
	for (int i = 0; i < graph->numberOfVertices; i++)
	{
		graph->graphArray[i] = new int [graph->numberOfVertices];
		for (int j = 0; j < graph->numberOfVertices; j++)
		{
			file >> graph->graphArray[i][j];
		}
	}

	file.close();

	return graph;
}

void deleteGraph(Graph *&graph)
{
	for (int i = 0; i < graph->numberOfVertices; i++)
	{
		delete[] graph->graphArray[i];
	}
}

bool *createVisitedVerticesArray(int numberOfVertices)
{
	bool *visitedVertices = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
	{
		visitedVertices[i] = false;
	}
	return visitedVertices;
}

int **createMinimumSpanningTreeArray(int numberOfVertices)
{
	int **minimumSpanningTree = new int *[numberOfVertices - 1];
	for (int i = 0; i < numberOfVertices - 1; i++)
	{
		minimumSpanningTree[i] = new int [2];
		for (int j = 0; j < 2; j++)
		{
			minimumSpanningTree[i][j] = 0;
		}
	}
	return minimumSpanningTree;
}

void addInMinimumSpanningTree(int **minimumSpanningTree, int first, int second, int numberOfVertices)
{
	for (int i = 0; i < numberOfVertices - 1; i++)
	{
		if (minimumSpanningTree[i][0] == 0 && minimumSpanningTree[i][1] == 0)
		{
			minimumSpanningTree[i][0] = first;
			minimumSpanningTree[i][1] = second;
			return;
		}
	}
}

bool everyVerticeIsVisited(bool *visitedVertices, int numberOfVertices)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		if (!visitedVertices[i])
		{
			return false;
		}
	}
	return true;
}

void searchMinimumSpanningTree(int vertice, Graph *graph, bool *visitedVertices, int **minimumSpanningTree)
{
	visitedVertices[vertice] = true;

	int minEdgeLength = 0;
	int first = 0;
	int second = 0;

	for (int i = 0; i < graph->numberOfVertices; i++)
	{
		for (int j = 0; j < graph->numberOfVertices; j++)
		{
			if (visitedVertices[i] && !visitedVertices[j] && graph->graphArray[i][j] != 0 && (minEdgeLength == 0 || graph->graphArray[i][j] < minEdgeLength))
			{
				minEdgeLength = graph->graphArray[i][j];
				first = i;
				second = j;
			}
		}
	}

	addInMinimumSpanningTree(minimumSpanningTree, first, second, graph->numberOfVertices);

	if (!everyVerticeIsVisited(visitedVertices, graph->numberOfVertices)) 
	{
		searchMinimumSpanningTree(second, graph, visitedVertices, minimumSpanningTree);
	}
}

int **findMinimumSpanningTree(Graph *graph)
{
	bool *visitedVertices = createVisitedVerticesArray(graph->numberOfVertices);
	int **minimumSpanningTree = createMinimumSpanningTreeArray(graph->numberOfVertices);

	searchMinimumSpanningTree(0, graph, visitedVertices, minimumSpanningTree);

	delete[] visitedVertices;

	return minimumSpanningTree;
}

void printTree(int **minimumSpanningTree, Graph *graph)
{
	cout << "minimum spanning tree by pairs of edge's vertices:" << endl;

	for (int i = 0; i < graph->numberOfVertices - 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << minimumSpanningTree[i][j] << " ";
		}
		cout << endl;
	}
}
// A C++ program to print topological sorting of a DAG
#include "stdafx.h"
#include<iostream>
#include <list>
#include <stack>
using namespace std;

// Class to represent a TopologicalGraph
class TopologicalGraph
{
	int V;    // No. of vertices'

			  // Pointer to an array containing adjacency listsList
	list<int> *adj;

	// A function used by topologicalSort
	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
public:
	TopologicalGraph(int V);   // Constructor

					// function to add an edge to TopologicalGraph
	void addEdge(int v, int w);

	// prints a Topological Sort of the complete TopologicalGraph
	void topologicalSort();
};

TopologicalGraph::TopologicalGraph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void TopologicalGraph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v�s list.
}

// A recursive function used by topologicalSort
void TopologicalGraph::topologicalSortUtil(int v, bool visited[],
	stack<int> &Stack)
{
	// Mark the current node as visited.
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack);

	// Push current vertex to stack which stores result
	Stack.push(v);
}

// The function to do Topological Sort. It uses recursive 
// topologicalSortUtil()
void TopologicalGraph::topologicalSort()
{
	stack<int> Stack;

	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to store Topological
	// Sort starting from all vertices one by one
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	// Print contents of stack
	while (Stack.empty() == false)
	{
		cout << Stack.top() << " ";
		Stack.pop();
	}
}
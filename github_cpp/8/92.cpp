
#include "stdafx.h"
#include<iostream>
#include <list>
#include <stack>
using namespace std;


class TopologicalGraph
{
	int V;    

			  
	list<int> *adj;

	
	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
public:
	TopologicalGraph(int V);   

					
	void addEdge(int v, int w);

	
	void topologicalSort();
};

TopologicalGraph::TopologicalGraph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void TopologicalGraph::addEdge(int v, int w)
{
	adj[v].push_back(w); 
}


void TopologicalGraph::topologicalSortUtil(int v, bool visited[],
	stack<int> &Stack)
{
	
	visited[v] = true;

	
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack);

	
	Stack.push(v);
}



void TopologicalGraph::topologicalSort()
{
	stack<int> Stack;

	
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	
	
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			topologicalSortUtil(i, visited, Stack);

	
	while (Stack.empty() == false)
	{
		cout << Stack.top() << " ";
		Stack.pop();
	}
}
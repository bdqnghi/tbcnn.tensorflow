#include "dfs.h"
#include <list>

Graph::Graph (int v)
{
	//copy the vertices enetered by the user into the private data memeber
	this->vertices = v;

	//initialize v number of list
	adj = new std::list<int>[v];
}

void Graph::addEdge (int v, int w)
{
	//push element w at the back of list v
	adj[v].push_back (w);
}

//utility function for DFS traversal
void Graph::DFSUtil (int v, bool visited[])
{
	//mark the current node as visited, and print it
	visited[v] = true;
	std::cout << v << " ";

	std::list<int>::iterator i;

	for (i = adj[v].begin(); i != adj[v].end(); i++)
	{
		if (!visited[*i])
			DFSUtil (*i, visited);
	}
}

void Graph::DFS (int v)
{
	//mark all nodes as not visited
	bool *visited = new bool[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = false;

	//call the utility function

	//if the all nodes are not connected, call all vertices like below
	/*for (int i = 0; i < vertices; i++)
	{
		if (visited[i] ==false)
			DFSUtil (i, visited);
	}*/

	//if all nodes are connected, just call the utility function
		DFSUtil (v, visited);
}

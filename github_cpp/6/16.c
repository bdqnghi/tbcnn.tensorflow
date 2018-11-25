#include "dfs.h"
#include <list>

Graph::Graph (int v)
{
	
	this->vertices = v;

	
	adj = new std::list<int>[v];
}

void Graph::addEdge (int v, int w)
{
	
	adj[v].push_back (w);
}


void Graph::DFSUtil (int v, bool visited[])
{
	
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
	
	bool *visited = new bool[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = false;

	

	
	

	
		DFSUtil (v, visited);
}

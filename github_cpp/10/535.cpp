#include <iostream>
#include <list>

using namespace std;

//Graph class representing a directed graph using adjacency list
class Graph
{
	int V; //no. of vertices
	list<int> *adj; //pointer to an array containing adjacency lists
	void DFSUtil(int v, bool visited[]); // A function used by DFS
public:
	Graph(int V); //Constructor
	void addEdge(int v, int w); //function to add an edge to the graph
	void DFS(int v);  //DFS traversal of the vertices reachable from source		
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); //Add w to v's list
}

void Graph::DFSUtil(int v, bool visited[])
{

	//Mark the current node as visited and print it
	visited[v] = true;
	cout << v << " ";

	//Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); i++)
		if(!visited[*i])
			DFSUtil(*i, visited);
}

//DFS traversal of all vertices reachable from v.

void Graph::DFS(int v)
{
	//Mark all vertices as not visited
	bool *visited = new bool[V];
	for(int i = 0; i < V; i++)
		visited[i] = false;

	//Call the recursive function to print DFS traversal
	DFSUtil(v, visited);
}

int main()
{
	// Create a graph
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Depth First Traversal" << endl;
	g.DFS(1);

	return 0;
}
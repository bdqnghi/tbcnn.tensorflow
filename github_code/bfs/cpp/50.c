#include<iostream>
#include<cstdio>
#include<list>
#include<queue>

using namespace std;
//-----------Graph DS start-------------------------
typedef struct Edge{
		int to;//Ending vertex
		int cost;//Cost of Edge
	}Edge;
	
typedef struct Graph{
	int V,E; //No. of Vertices and Edges
	char *vertices; //Array for mapping vertices to lablel
	list<Edge> *adj; //Adjacency List 
	void init(int V);//Initializer
	void addEdge(int from, int to);//Add edge without cost
	void addEdge(int from, int to, int cost);//Add edge with cost;
}Graph;

void Graph::init(int V){
	this->V = V;
	adj = new list<Edge>[V];
}

void Graph::addEdge(int from, int to){
	Edge edge;
	edge.to = to;
	edge.cost = 0; //Make default cost zero 
	this->adj[from].push_back(edge);
}

void Graph::addEdge(int from, int to, int cost){
	Edge edge;
	edge.to = to;
	edge.cost = cost;
	this->adj[from].push_back(edge);
}
//-----------Graph DS end-------------------------

void BFS(Graph g, int s){
	//Alogorithm: only work for connected graph
	//Time:O(V+E)
	//Space:
	bool visited[g.V];
	//set all nodes as unvisited
	for(int i=0; i<g.V; ++i){
		visited[i] = false;
	}
	//Queue for currently visited nodes
	queue<int> vertexQueue;
	//Start with the source node
	visited[s] = true;
	vertexQueue.push(s);
	list<Edge>::iterator itr;
	printf("The vertices in BFS are:\n");
	while(!vertexQueue.empty()){
		int from = vertexQueue.front();
		printf("%d ",from);
		vertexQueue.pop();
		for(itr=g.adj[from].begin(); itr!=g.adj[from].end(); ++itr){
			int to = (*itr).to;
			if(!visited[to]){
				visited[to] = true;
				vertexQueue.push(to);
			}
		}
		
	}
}

int main(){
	Graph g;
	g.init(4);
	g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 	BFS(g,2);
	return 0;
}

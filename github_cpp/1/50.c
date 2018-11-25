#include<iostream>
#include<cstdio>
#include<list>
#include<queue>

using namespace std;

typedef struct Edge{
		int to;
		int cost;
	}Edge;
	
typedef struct Graph{
	int V,E; 
	char *vertices; 
	list<Edge> *adj; 
	void init(int V);
	void addEdge(int from, int to);
	void addEdge(int from, int to, int cost);
}Graph;

void Graph::init(int V){
	this->V = V;
	adj = new list<Edge>[V];
}

void Graph::addEdge(int from, int to){
	Edge edge;
	edge.to = to;
	edge.cost = 0; 
	this->adj[from].push_back(edge);
}

void Graph::addEdge(int from, int to, int cost){
	Edge edge;
	edge.to = to;
	edge.cost = cost;
	this->adj[from].push_back(edge);
}


void BFS(Graph g, int s){
	
	
	
	bool visited[g.V];
	
	for(int i=0; i<g.V; ++i){
		visited[i] = false;
	}
	
	queue<int> vertexQueue;
	
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

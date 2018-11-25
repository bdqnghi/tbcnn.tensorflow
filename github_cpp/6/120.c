#include<iostream>
#include<cstdio>
#include<list>
#include<stack>

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


void DFS(Graph g, int s){
	
	
	
	bool visited[g.V];
	
	for(int i=0; i<g.V; ++i){
		visited[i] = false;
	}
	
	stack<int> vertexStack;
	
	visited[s] = true;
	vertexStack.push(s);
	list<Edge>::iterator itr;

	while(!vertexStack.empty()){
		int from = vertexStack.top();
		printf("%d ",from);
		vertexStack.pop();
		for(itr=g.adj[from].begin(); itr!=g.adj[from].end(); ++itr){
			int to = (*itr).to;
			if(!visited[to]){
				visited[to] = true;
				vertexStack.push(to);
			}
		}

	}
}

void recursiveDFS(Graph g, int s, bool *visited){
    
	
	
    visited[s] = true;
    printf("%d ",s);
    list<Edge>::iterator itr;

    for(itr = g.adj[s].begin(); itr!=g.adj[s].end(); ++itr){
        int to = (*itr).to;
        if(!visited[to]){
            recursiveDFS(g, to, visited);
        }
    }
}

int main(){
	Graph g;
	g.init(6);
	g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    printf("The vertices in simple DFS are:\n");
 	DFS(g,2);

 	printf("\n\nThe vertices in recursive DFS are:\n");
 	bool visited[6];
 	for(int i=0;i<6;++i){
        visited[i] = false;
 	}
 	recursiveDFS(g, 2, visited);
 	printf("\n");
	return 0;
}

#include<iostream>
#include<cstdio>
#include<list>
#include<stack>

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

void DFS(Graph g, int s){
	//Alogorithm: only work for connected graph | Using stack
	//Time:O(V+E)
	//Space:
	bool visited[g.V];
	//set all nodes as unvisited
	for(int i=0; i<g.V; ++i){
		visited[i] = false;
	}
	//Stack for currently visited nodes
	stack<int> vertexStack;
	//Start with the source node
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
    //Alogorithm: only work for connected graph | Recursive approach
	//Time:O(V+E)
	//Space:
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

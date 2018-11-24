#include <bits/stdc++.h>


#define WHITE	0
#define GRAY	1
#define BLACK	2
#define NIL	-1

using namespace std;

class Vertex {
public:
	int color;
	int d,f;
	int parent;
	Vertex() {
		color = WHITE;
		parent = NIL;
	}
};



vector<list<int> > adj;
vector<Vertex> vertices;
int timestamp = 0;

void DFS_visit(int src) {
	timestamp++;
	vertices[src].d = timestamp;
	vertices[src].color = GRAY;
	cout << src << " ";
	for(auto v: adj[src]) {
		if(vertices[v].color == WHITE){
			vertices[v].parent = src;
			DFS_visit(v);
		}
	}
	vertices[src].color = BLACK;
	timestamp++;
	vertices[src].f = timestamp;
}


void DFS(){
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].color == WHITE)
			DFS_visit(i);
	}
}


int main() {
	int V, E;
	cin >> V >> E;
	adj.resize(V);
	vertices.resize(V);

	for(int i = 0; i < E; i++){
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	DFS();
}
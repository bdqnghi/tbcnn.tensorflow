#include <iostream>
#include <stdio.h>
#include <list>
using namespace std;
class graph{
	int v;
	list < int > *adj;
	void topo_visit(int s, int *visited, list < int >& stk);
public:
	graph(int n);
	void add_edge(int x, int y);
	void topo_sort();
};
graph::graph(int n) : v(n) {
	adj = new list < int > [v];
}
void graph::add_edge(int x, int y) {
	adj[x].push_back(y);
}
void graph::topo_visit(int s, int *visited, list < int >& stk) {
	visited[s] = 1;
	list < int > :: iterator it;
	for(it = adj[s].begin() ; it != adj[s].end() ; it++){
		if(visited[*it] == 0){
			topo_visit(*it, visited, stk);
		}
	}
	stk.push_back(s);
	visited[s] = 2;
}
void graph::topo_sort() {
	int *visited = new int[v];
	list < int > stk;
	for(int i = 0 ; i < v ; i++){
		if(visited[i] == 0){
			topo_visit(i, visited, stk);
		}
	}
	list < int > :: reverse_iterator it;
	for(it = stk.rbegin() ; it != stk.rend() ; it++)
		printf("%d ", *it);
	printf("\n");
}
int main(){
	int n, e, x, y;
	printf("Enter the no. of vertices and edges in the graph (v e) :\n");
	scanf("%d%d", &n, &e);
	printf("Enter the edges in format (u v w) :\n");
	graph g(n);
	for(int i = 0 ; i < e ; i++){
		scanf("%d%d", &x, &y);
		g.add_edge(x,y);
	}	
	g.topo_sort();
	return 0;
}
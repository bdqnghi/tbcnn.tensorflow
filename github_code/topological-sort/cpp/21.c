/*
 * TOPOLOGICAL-SORT(G)
 * 	call DFS(G) to compute finishing times v.f for each vertex v
 * 	as each vertex is finished, insert it onto the front of a linked list
 * 	return the linked list of vertices
 */
/*
 * Tool to process Directed Acyclic Graph
 */
#include <cstdio>
#include <cstring>

#define DEBUG
template<typename T, int N>
void DFSVisit(T (&e)[N], int u, bool visited[], int **ordered) {
	visited[u] = true;
	for (int v = 0; v < N; ++v) {
		if (e[u][v] && !visited[v]) {
			DFSVisit(e, v, visited, ordered);
		}
	}
	*(--*ordered) = u;
}

template<typename T, int N>
void TopologicalSort(T (&e)[N]) {
	bool visited[N];
	memset(visited, 0, sizeof(visited));
	int ordered[N];
	auto back = ordered + N;
	for (int u = 0; u < N; ++u) {
		if (!visited[u]) {
			DFSVisit(e, u, visited, &back);
		}
	}
#ifdef DEBUG
	for (auto u : ordered) {
		fprintf(stdout, "%3d",u);
	}
	fprintf(stdout, "\n");
#endif
}

int main() {
	bool graph[][6] = {
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,1,0,0},
		{0,1,0,0,0,0},
		{1,1,0,0,0,0},
		{1,0,1,0,0,0}
	};
	TopologicalSort(graph);
	return 0;
}

#include <iostream>
#include <queue>
#include <limits>
#include <cstring>
using namespace std;

#define MAX_V 500
#define MAX_E 20000

int c[MAX_V][MAX_V]; 
int cf[MAX_V][MAX_V]; 
int path[MAX_V]; 
int capacity[MAX_V]; 
int visited[MAX_V]; 
int maxFlow; 
int S; 
int T; 
int V; 

bool findAugmentPath() {
	queue<int> Q; 
	memset(path, 0, sizeof(int) * MAX_V); 
	memset(capacity, 0, sizeof(int) * MAX_V); 
	memset(visited, 0, sizeof(int) * MAX_V); 
	capacity[S] = INT32_MAX;
	visited[S] = 1;

	Q.push(S); 

	while (Q.size() != 0) {
		int u = Q.front();
		Q.pop();

		if (u == T) {
			return true; 
		}

		for (int v = 0; v < V; v++) {
			if (cf[u][v] > 0 && visited[v] == 0) {
				
				path[v] = u; 
				capacity[v] = min(cf[u][v], capacity[u]); 
				visited[v] = 1;
				Q.push(v);
			}
		}
	}

	return false;
}

int modifyGraph() {
	int flow = capacity[T];
	int now = T;
	while (now != S) {
		int fa = path[now];
		cf[fa][now] = cf[fa][now] - flow;
		cf[now][fa] = cf[now][fa] + flow; 
		now = fa;
	}
	return 0;
}

int Ford_Fulkerson() {
	while (findAugmentPath()) { 
		maxFlow = maxFlow + capacity[T]; 
		modifyGraph();
	}
	return 0;
}

int main() {
	int n, m;
	cin >> n >> m;
	S = 0;
	T = n - 1;
	V = n;
	int u, v, c;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> c;
		
		cf[u - 1][v - 1] = cf[u - 1][v - 1] + c;
	}
	Ford_Fulkerson();
	cout << maxFlow << endl;
}
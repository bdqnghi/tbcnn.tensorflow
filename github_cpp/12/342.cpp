#include <bits/stdc++.h>
using namespace std;

#define INF 1e6

int main(){
	int V, E, u, v, w, adj[200][200];

	scanf("%d %d", &V, &E);
	int i,j,k;
	for(i=0; i<V; i++){
		for(j=0; j<V; j++)
			adj[i][j] = INF;
		adj[i][i] = 0;
	}

	for(i=0; i<E; i++){
		scanf("%d %d %d", &u, &v, &w);
		adj[u][v] = w;
	}

	for(k=0; k<V; k++)
		for(i=0; i<V; i++)
			for(j=0; j<V; j++)
				adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);

	for(i=0; i<V; i++)
		for(j=0; j<V; j++)
			printf("APSP (%d,%d) = %d\n", i, j, adj[i][j]);

	return 0;
}
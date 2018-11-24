/*
	In the name of Allah
	Code by jahanaraco
	All Pairs Shortest Path
	Floyd-Warshal algorithm for Directed Weighted Graphs
	O(N^3)
*/

#include <iostream>
using namespace std;

const int MAXN = 500;
int mat[MAXN][MAXN],dist[MAXN][MAXN][MAXN], n, m;

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(i != j)
				mat[i][j] = INF;
	for(int i = 0; i < m; i++){
		int v, u, w;
		cin >> v >> u >> w;
		dist[v][u][1] = mat[v][u] = min(mat[v][u], w);
	}
	for(int k = 2; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dist[i][j][k] = min(dist[i][j][k-1], dist[i][k][k-1]+dist[k][j][k-1]);

	for(int i = 1; i <= n; i++, cout << endl)
		for(int j = 1; j <= n; j++)
			cout << dist[i][j][n] << ' ';
	return 0;
}

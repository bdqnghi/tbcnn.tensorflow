#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vector<vi> AdjList;
vi dfs_num, topologicalSort;

void OrdenTopologico(int u) {
	dfs_num[u] = 1;
	for (int i = 0; i < AdjList[u].size(); ++i) {
		int v = AdjList[u][i];
		if(dfs_num[v] == -1)
			OrdenTopologico(v);
	}
	topologicalSort.push_back(u);
}

int main() {

	int V, E, u, v;

	scanf("%d %d", &V, &E);
	AdjList.assign(V, vi());
	while (E--) {
		scanf("%d %d", &u, &v);
		AdjList[u].push_back(v);
	}

	dfs_num.assign(V, -1);
	for (int i = 0; i < V; ++i)
		if(dfs_num[i] == -1)
			OrdenTopologico(i);

	reverse(topologicalSort.begin(), topologicalSort.end());
	for (int i = 0; i < topologicalSort.size(); ++i) {
		printf("%d ", topologicalSort[i]);
	}
	printf("\n");
	return 0;
}

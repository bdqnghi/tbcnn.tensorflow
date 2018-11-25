#include <stdio.h>
#include <queue>
#include <cstring>
#include <conio.h>
using namespace std;

bool dfs(int rg[6][6], int s, int t, int p[]) {
	bool v[6];
	memset(v, 0, sizeof(v));
	queue <int> q;
	q.push(s);
	v[s] = true;
	p[s] = -1;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = 0; i < 6; i++) {
			if(v[i] == false && rg[u][i] != 0) {
				v[i] = true;
				p[i] = u;
				q.push(i);
			}
		}
	}
	if(v[t] == true)return true;
	else return false;
}

int ff(int g[6][6], int s, int t) {
	int rg[6][6];
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 6; j++) {
			rg[i][j] = g[i][j];
		}
	}
	int p[6];
	int maxflow = 0;
	while(dfs(rg, s, t, p)) {
		int path = 10000;
		for(int i = t; i != s; i = p[i]) {
			int j = p[i];
			path = min(path, rg[j][i]);
		}
		for(int i = t; i != s; i = p[i]) {
			int j = p[i];
			rg[j][i] = rg[j][i] - path;
			rg[i][j] = rg[i][j] + path;
		}
		maxflow += path;
	}
	return maxflow;
}

int main() {
    int graph[6][6] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };
	printf("%d\n", ff(graph, 0, 5));
	getchar();
	return 0;
}

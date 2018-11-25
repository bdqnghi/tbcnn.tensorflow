#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

vector<int> adjList[110];
int N, points, dfs_root, dfs_num[110], dfs_low[110], dfs_count = 0, root_childs = 0, dfs_parent[110];
bool articulationPoint[110];

void articulationPoints(int u) {
    dfs_num[u] = dfs_low[u] = dfs_count++;
    for (int j = 0; j < (int) adjList[u].size(); j++) {
        int v = adjList[u][j];
        if (dfs_num[v] == -1) {
            dfs_parent[v] = u;
            if (dfs_root == u) root_childs++;
            articulationPoints(v);
            if (dfs_low[v] >= dfs_num[u] && dfs_root != u) articulationPoint[u] = 1;
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

int main() {
    while(scanf("%d", &N), N) {
        int num;
        memset(dfs_num, -1, sizeof dfs_num);
        memset(dfs_low, -1, sizeof dfs_low);
        memset(dfs_parent, -1, sizeof dfs_parent);
        memset(articulationPoint, 0, sizeof articulationPoint);
        for (int i = 0; i < 110; i++) {
            adjList[i].clear();
        }
        points = 0;
        while(scanf("%d", &num), num) {
            int adj; char contex;
            do {
                scanf("%d%c", &adj, &contex);
                adjList[num].push_back(adj);
                adjList[adj].push_back(num);
            } while (contex != '\n');
        }
        for (int i = 1; i <= N; i++) {
            if (dfs_num[i] == -1) {
                dfs_root = i;
                dfs_count = 0;
                root_childs = 0;
                articulationPoints(i);
                if (root_childs > 1) articulationPoint[i] = 1;
            }
        }
        for (int i = 1; i <= N; i++) {
            if (articulationPoint[i]) {
                points++;
            }
        }
        printf("%d\n", points);
    }
}
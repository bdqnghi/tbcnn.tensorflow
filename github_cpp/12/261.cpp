#include <cstdio>
#include <algorithm>
using namespace std;

#define INF  0x3f3f3f3f
#define MAXN 1001

int n, m;
int path[MAXN][MAXN];

void fw() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                path[i][j] = min(path[i][j], path[i][k] + path[k][j]);
}

int main() {
    int u, v, w;

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            path[i][j] = INF;
        path[i][i] = 0;
    }

    while (m--) {
        scanf("%d %d %d", &u, &v, &w);
        path[u][v] = w;
    }

    fw();
}

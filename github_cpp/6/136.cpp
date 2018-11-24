#include <iostream>
#include <vector>

using namespace std;

#define MAXN 505
#define INF (1<<30)

struct Node {
    int v, dst;
};

vector<Node> adj[MAXN];
int d[MAXN];
bool visited[MAXN];
int n, m;

void init()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        d[i] = INF;
        visited[i] = false;
    }

    for (int i = 0; i < m; i++) {
        int c1, c2, len;
        cin >> c1 >> c2 >> len;
        Node node; node.v = c2; node.dst = len;
        adj[c1].push_back(node);
    }
}

bool bellman(int s)
{
    for (int i = 0; i < n-1; i++) {
        for (int u = 0; u < n; u++) {
            for (int j = 0; j < adj[u].size(); j++) {
                int v = adj[u][j].v;
                int dst = adj[u][j].dst;
                if (d[u] + dst < d[v]) {
                    d[v] = d[u] + dst;
                }
            }
        }

        for (int u = 0; u < n; u++) {
            for (int j = 0; j < adj[u].size(); j++) {
                int v = adj[u][j].v;
                int dst = adj[u][j].dst;
                if (d[u] + dst < d[v]) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main()
{
    init();
    bellman(0);

    return 0;
}

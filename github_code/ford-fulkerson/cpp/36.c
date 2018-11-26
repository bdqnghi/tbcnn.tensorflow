/*
 ~ Ford-Fulkerson/Edmonds-Karp Algorithm ~
 
 Finds max flow in a network.
 Ford-Fulkerson is the general method. Different ways of choosing the augmenting path can lead to faster results.
 For example, the Edmonds-Karp method always chooses the augmenting path with the least number of edges.
 
 Time complexity:
 Ford-Fulkerson - O(EF)
 Edmonds-Karp - O(VE^2)
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
const int INF = 0x3F3F3F3F;
const int MOD = 1e9 + 7;
const int MAX = 205;
const int MAXE = 205;

int N, M;
piii edges[2 * MAXE];
int last[MAX], par[MAX], idx[MAX];
bool vis[MAX];
int S, T;
int cnt = 0;

void dfsUtil(int u) {
    for (int i = last[u]; i != -1; i = edges[i].second) {
        int v = edges[i].first.first;
        int w = edges[i].first.second;
        if (!vis[v] && w) {
            vis[v] = true;
            par[v] = u;
            idx[v] = i;
            dfsUtil(v);
        }
    }
}

bool dfs() {
    
    fill(vis, vis + N + 1, false);
    par[S] = idx[S] = -1;
    vis[S] = true;
    dfsUtil(S);
    return vis[T];
}

bool bfs() {
    
    fill(vis, vis + N + 1, false);
    queue<int> q;
    par[S] = idx[S] = -1;
    vis[S] = true;
    q.push(S);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = last[u]; i != -1; i = edges[i].second) {
            int v = edges[i].first.first;
            int w = edges[i].first.second;
            if (!vis[v] && w) {
                vis[v] = true;
                par[v] = u;
                idx[v] = i;
                q.push(v);
            }
        }
    }
    
    return vis[T];
}

int ff(bool b) {
    
    int maxFlow = 0, flow;
    
    while (b ? bfs() : dfs()) {
        flow = INF;
        int u = T;
        while (par[u] != -1) {
            flow = min(flow, edges[idx[u]].first.second);
            u = par[u];
        }
        u = T;
        while (par[u] != -1) {
            edges[idx[u]].first.second -= flow;
            edges[idx[u] ^ 1].first.second += flow;
            u = par[u];
        }
        maxFlow += flow;
    }
    
    return maxFlow;
}

int main() {
    
    scanf("%d%d", &N, &M);
    fill(last, last + N + 1, -1);
    int a, b, d;
    while (M--) {
        scanf("%d%d%d", &a, &b, &d);
        edges[cnt] = {{b, d}, last[a]};
        last[a] = cnt++;
        edges[cnt] = {{a, 0}, last[b]};
        last[b] = cnt++;
    }
    scanf("%d%d", &S, &T);
    char c;
    
    scanf(" %c", &c);
    if (c == 'F') {
        printf("Max flow (Ford-Fulkerson): %d\n", ff(0));
    } else if (c == 'E') {
        printf("Max flow (Edmonds-Karp): %d\n", ff(1));
    }
    
    return 0;
    
}

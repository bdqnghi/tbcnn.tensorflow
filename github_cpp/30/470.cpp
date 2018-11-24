#include <vector>
#include <queue>
#include <limits>
#define MAXN 200000
using namespace std;

int N, M, T;

vector<int> graph[MAXN], rgraph[MAXN];
bool visited[MAXN];
int dist[MAXN], dist2[MAXN];

int solve(int N, int M, int T, int S[], int E[]){
    for(int i=0; i<M; i++) {
        graph[S[i]].push_back(E[i]);
        rgraph[E[i]].push_back(S[i]);
    }
    for(int i=0; i<N; i++) dist[i] = numeric_limits<int>::max();
    priority_queue< pair<int,int> > pq;
    pq.push(pair<int,int>(0, 0));
    dist[0] = 0;
    while (!pq.empty()) {
        pair<int,int> tmp = pq.top(); pq.pop();
        int t = -tmp.first, u = tmp.second;
        if (t > dist[u])
            continue;
        for (int i=0; i<(int)graph[u].size(); i++) {
            int v = graph[u][i];
            if (dist[v] > 1 + dist[u] && 1 + dist[u] <= T) {
                dist[v] = 1 + dist[u];
                pq.push(pair<int,int>(-dist[v], v));
            }
        }
    }
    if (dist[N-1] < numeric_limits<int>::max())
        return dist[N-1];
    for (int i=0; i<N; i++)
        if (dist[i] <= T) {
            dist2[i] = T;
            pq.push(pair<int,int>(-dist2[i], i));
        } else {
            dist2[i] = numeric_limits<int>::max();
        }
    while (!pq.empty()) {
        pair<int,int> tmp = pq.top(); pq.pop();
        int t = -tmp.first, u = tmp.second;
        if (t > dist2[u])
            continue;
        for (int i=0; i<(int)rgraph[u].size(); i++) {
            int v = rgraph[u][i];
            if (dist2[v] > 1 + dist2[u]) {
                dist2[v] = 1 + dist2[u];
                pq.push(pair<int,int>(-dist2[v], v));
            }
        }
    }
    if (dist2[N-1] == numeric_limits<int>::max())
        return -1;
    else
        return dist2[N-1];
}

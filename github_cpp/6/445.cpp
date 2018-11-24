/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Bellman-Ford algorithm to find shortest path of directed graph (including negative edge)
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define INF 99999999
#define pb push_back
#define mp make_pair
const int sz = 20001;  // size
vector<pair<int,int> > a[sz]; // adjacency list
int dist[sz]; // store shortest distance
bool visit[sz] = {0};
int n, m, x, y, w, source;
int upper[sz]; // upper bound for bellman-ford

void Dijkstra(int source) {
    for (int i=1; i<=n; i++)
        dist[i] = INF;
    priority_queue<pair<int, int> > pq;
    // -w, v
    dist[source] = 0;
    pq.push(mp(0,source));
    while(!pq.empty()) {
        pair<int, int> t = pq.top(); pq.pop();
        int curDist = -t.first;
        int v = t.second;
        // ignore if bigger than the one already found
        if (curDist > dist[v]) continue;
        for (int i=0; i<a[v].size(); i++) {
            // u is next node / w is w(v,u)
            int u = a[v][i].first, w = a[v][i].second;
            if (dist[u] > curDist + w) {
                dist[u] = curDist + w;
                pq.push(mp(-dist[u],u));
            }
        }
    }
}

// return false if there exists negative cycle
bool BellmanFord(int source) {
    for (int i=1; i<=n; i++)
        upper[i] = INF;
    upper[source] = 0;

    // relax |V|-1 times
    for (int i=0; i<n; i++) {
        for (int v=1; v<=n; v++) {
            for (int j=0; j<a[v].size(); j++) {
                int u = a[v][j].first, w = a[v][j].second;
                if (upper[u] > upper[v] + w) {
                    upper[u] = upper[v] + w;
                    if (i == n-1)
                        return false;
                }
            }
        }
    }
    return true;
}

int main() {
    cin >> n >> m >> source;
    for (int i=0; i<m; i++) {
        cin >> x >> y >> w;
        a[x].push_back(make_pair(y,w));
    }

    if (!BellmanFord(source)) {
        cout << "There exists a negative cycle" << endl;
        return 0;
    }
    for (int i=1; i<=n; i++) {
        int cur = upper[i];
        if (cur == INF)
            printf("INF\n");
        else
            printf("%d\n", cur);
    }

    return 0;
}

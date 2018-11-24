#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <memory.h>
#include <queue>

using namespace std;

# define INF 1000000000

typedef pair<int,int> ii;

struct edge{
    int w, weight;
};

int dist[1000];
int parent[1000];
priority_queue<ii, vector<ii>, greater<ii> > pq;

void initialize(vector<vector<edge> > &g, int s)
{
    for (int i = 0; i < g.size(); i++){
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[s] = 0;
    pq.push(ii(0,s));
}

void dijkstra(vector<vector<edge> > &g, int s)
{
    initialize(g,s);

    while (!pq.empty()){
        ii front = pq.top();
        pq.pop();
        int d = front.first;
        int u = front.second;

        if (d == dist[u]){
            for (int j = 0; j < g[u].size(); j++){
                int w = g[u][j].w;
                if (dist[w] > dist[u]+g[u][j].weight){
                    dist[w] = dist[u]+g[u][j].weight;
                    parent[w] = u;
                    pq.push(ii(dist[w],w));
                }
            }
        }
    }
}

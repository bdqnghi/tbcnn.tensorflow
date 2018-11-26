#include <bits/stdc++.h>

#define MAX 10010
#define INF (1 << 30)

using namespace std;

typedef pair <int, int> ii;

vector <ii> adj[MAX];
int dist[MAX];

void bfs(int idx){
    queue <int> q;

    memset(dist, INF, sizeof dist);

    dist[idx] = 0;
    q.push(idx);

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int i = 0; i < (int)adj[u].size(); i++){
            ii v = adj[u][i];
            if(dist[v.first] == INF){
                dist[v.first] = dist[u] + 1;
                q.push(v.first);
            }
        }
    }
}

int main(){
    return 0;
}

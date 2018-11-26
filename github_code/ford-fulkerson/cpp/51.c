int par[N], graph[N][N];
bool vis[N];
stack<int> stak;
vector<int> adj[N];
int source, sink;
vector< pair< pair<int, int> , int> > edges;

inline bool FindAugPath(){
    int u, v, i;
    memset(vis, false, sizeof(vis));

    stak.push(1);
    vis[1] = true;

    while(!stak.empty()){
        u = stak.top();
        stak.pop();

        if(vis[sink] == true){
            continue;
        }

        for(i = adj[u].size() - 1; i >= 0; i--){
            v = adj[u][i];
            if(vis[v] == false){
                if(graph[u][v] > 0){
                    par[v] = u;
                    vis[v] = true;
                    stak.push(v);
                }
            }
        }
    }

    if(vis[sink] == false){
        return false;
    }

    u = sink;
    while(u != source){
        graph[par[u]][u]--;
        graph[u][par[u]]++;
        u = par[u];
    }

    return true;
}

inline int MaxFlow(){
    int mf = 0;
    while(FindAugPath()){
        mf++;
    }
    return mf;
}

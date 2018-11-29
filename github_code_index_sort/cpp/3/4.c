/* a b g[a].push_back(b) , g1[b].push_back(a)*/
int n,cnt,verticesScc[MAX_N];
vector<int>g[MAX_N],g1[MAX_N],scc[MAX_N];
vector<int>topologicalSort;
bool mark[MAX_N];


void tSort(int v) {
    mark[v] = true;
    for(int i = 0 ; i < g[v].size() ; i++)
        if(!mark[g[v][i]])
            tSort(g[v][i]);
    topologicalSort.push_back(v);
}

void dfs(int v) {
    mark[v] = true;
    scc[cnt].push_back(v);
    verticesScc[v] = cnt;
    for(int i = 0 ; i < g1[v].size() ; i++)
        if(!mark[g1[v][i]])
            dfs(g1[v][i]);
}

void SCC() {
     for(int i = 1 ; i <= n ; i++)
            if(!mark[i])
                tSort(i);
    reverse(topologicalSort.begin(), topologicalSort.end());
    for(int i = 0 ; i < MAX_N ; i++)
        mark[i] = false;
    for(int i = 0 ; i < topologicalSort.size() ; i++) {
        if(!mark[topologicalSort[i]]) {
            cnt++;
            dfs(topologicalSort[i]);
        }
    }
}

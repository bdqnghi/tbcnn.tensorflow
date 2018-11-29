// booleans are 1 to n
//~i = i+n

int n,m,cnt = 1,verticesScc[MAX_N];
vector<int>g[MAX_N],g1[MAX_N],scc[MAX_N];
vector<int>topologicalSort;
bool mark[MAX_N],ans[MAX_N],satisfy = true;

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
    cnt--;
}

int inverse(int t) {
    if(t <= n)
        return t+n;
    return t-n;
}

bool check() {
    for(int i = 1 ;  i<= n ; i++)
        if(verticesScc[i] == verticesScc[i+n])
            return false;
    return true;
}
//one of the expressions are (x or y)
void addExpresion(int x,int y) {
    g[inverse(x)].push_back(y);
    g[inverse(y)].push_back(x);
    g1[y].push_back(inverse(x));
    g1[x].push_back(inverse(y));
}

void twoSat() {
    n *= 2;
    SCC();
    n/=2;
    if(!check()) {
        satisfy = false;
        return;
    }
    for(int i = 0  ; i < MAX_N ; i++)
        mark[i] = false;
    reverse(topologicalSort.begin(),topologicalSort.end());
    for(int i = 0 ; i < topologicalSort.size() ; i++) {
        int f = topologicalSort[i];
        if(f <= n && !mark[f]) {
            mark[f] = true;
            ans[f] = true;
        }
        if(f > n && !mark[f-n])
            mark[f-n] = true;
    }
}

Weight ford_dfs(Graph &g, int v, int t, Weight f, vector<int> &used){
    if(v == t) return f;
    used[v] = true;
    EACH(i, g[v]){
        if(!used[i -> to] && i -> weight > 0){
            Weight d = ford_dfs(g, i -> to, t, min(f, i -> weight), used);
            if(d > 0){
                i -> weight -= d;
                g[i -> to][i -> rev].weight += d;
                return d;
            }
        }
    }
    return 0;
}
Weight ford_fulkerson(Graph &g, int s, int t){
    vector<int> used(g.size());
    Weight flow = 0;
    for(;;){
        fill(ALL(used), 0);
        int f = ford_dfs(g, s, t, INF, used);
        if(f == 0) return flow;
        flow += f;
    }
    return flow;
}

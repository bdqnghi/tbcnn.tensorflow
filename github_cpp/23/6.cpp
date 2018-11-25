






typedef int ff_t;


struct edge {ff_t to, cap, rev;};


const ff_t MAX_V = ;

const ff_t FF_INF = ;

vector<edge> G[MAX_V];

bool used[MAX_V];


void add_edge(ff_t from, ff_t to, ff_t cap){
    G[from].push_back((edge){to, cap, G[to].size()});
    G[to].push_back((edge){from, 0, G[from].size()-1});
}


ff_t ff_dfs(ff_t v, ff_t t, ff_t f){
    if(v==t) return f;
    used[v]=true;

    for(ff_t i=0; i<G[v].size(); ++i){
        edge &e=G[v][i];
        if(!used[e.to] && e.cap>0){
            ff_t d = ff_dfs(e.to, t, min(f,e.cap));
            if(d>0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }

  return 0;
}


ff_t max_flow(ff_t s, ff_t t){
    ff_t flow=0;
    for(;;){
        memset(used,0,sizeof(used));
        ff_t f = ff_dfs(s,t,FF_INF);
        if(f==0) return flow;
        flow+=f;
    }
}



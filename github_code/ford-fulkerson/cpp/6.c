/******************************
 FordFulkerson.cpp  START
******************************/

/******************************
 Ford-Fulkerson法
 DFSにより最大流を求める
******************************/

//SETTING

//型設定(int?long?ll?)
typedef int ff_t;

//辺を表す構造体(行き先、容量。逆辺)
struct edge {ff_t to, cap, rev;};

//ノードの数
const ff_t MAX_V = ;
//LIMIT
const ff_t FF_INF = ;
//グラフの隣接リスト表現
vector<edge> G[MAX_V];
//DFSですでに調べたかのフラグ
bool used[MAX_V];

//fromからtoへ向かう容量capの辺をグラフに追加する
void add_edge(ff_t from, ff_t to, ff_t cap){
    G[from].push_back((edge){to, cap, G[to].size()});
    G[to].push_back((edge){from, 0, G[from].size()-1});
}

//増加パスを探す
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

//sからtへの最大流を求める
ff_t max_flow(ff_t s, ff_t t){
    ff_t flow=0;
    for(;;){
        memset(used,0,sizeof(used));
        ff_t f = ff_dfs(s,t,FF_INF);
        if(f==0) return flow;
        flow+=f;
    }
}

/******************************
 FordFulkerson.cpp  END
******************************/

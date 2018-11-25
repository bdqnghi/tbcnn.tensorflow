#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define PB push_back
const int INF = 0x3f3f3f3f;
const int maxn = 205;

int n,m;
struct Edge{
    int to,cap,idx;
    Edge(){}
    Edge(int to,int cap,int idx):to(to),cap(cap),idx(idx){}
};
vector<Edge> V[maxn];
bool vis[maxn];

void add_edge(int u,int v,int w)
{
    V[u].PB(Edge(v,w,V[v].size()));
    V[v].PB(Edge(u,0,V[u].size()-1));
}

int dfs(int s,int t,int f)
{
    if(s==t) return f;
    vis[s]=true;
    for(int i=0;i<V[s].size();i++)
    {
        Edge &cur = V[s][i];
        if(!vis[cur.to] && cur.cap>0)
        {
            int tmp = dfs(cur.to,t,min(f,cur.cap));
            if(tmp>0)
            {
                cur.cap -= tmp;
                V[cur.to][cur.idx].cap += tmp;
                return tmp;
            }
        }
    }
    return 0;
}

int Ford-Fulkerson(int s,int t)
{
    int res = 0;
    while(true)
    {
        memset(vis,false,sizeof(vis));
        int flow = dfs(s,t,INF);
        if(flow==0) return res;
        res += flow;
    }
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=1;i<=m;i++) V[i].clear();
        int u,v,w;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w);
        }
        printf("%d\n",Ford-Fulkerson(1,m));
    }
    return 0;
}

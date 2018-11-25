#include <cstdio>
#include <algorithm>
#include <vector>
#define MAXM 212345
#define MAXN 112345
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;

const int INF = 0x3f3f3f3f;

struct edge{
    int to, f, c;
}  e[MAXM];

graph g;

int TC=0, cur = 0, seen[MAXN];
void addge(int a , int b, int cp, int rc)
{
    e[cur].to = b, e[cur].f  = 0, e[cur].c = cp;
    g[a].push_back(cur++);
    e[cur].to = a, e[cur].f = 0, e[cur].c = rc;
    g[b].push_back(cur++);
}

int dfs(int s, int t, int flow)
{
    if(s==t) return flow;

    seen[s] = TC;
    int resf, v;
    for(int i : g[s])
    {
        v = e[i].to;
        resf = e[i].c-e[i].f;
        if(seen[v]<TC && resf>0)
        {
            if(resf = dfs(v,t, min(resf, flow)))
            {
                e[i].f+=resf;
                e[i^1].f-=resf;
                return resf;
            }
        }
    }

    return 0;
}

int maxflow(int s, int t)
{
    int flow = 0, a;
    ++TC;
    while(a = dfs(s,t,INF))
    {
        flow+=a;
        ++TC;
    }

    return flow;
}


int main()
{
    int n, m,u,v,w,s,t;
    scanf("%d %d", &n, &m);
    g.assign(n+1, vi());

    while(m--)
    {
        scanf("%d %d %d", &u, &v, &w);
        addge(u,v,w, 0);
    }
    scanf("%d %d", &s, &t);

    m = maxflow(s,t);

    printf("%d\n", m);
}

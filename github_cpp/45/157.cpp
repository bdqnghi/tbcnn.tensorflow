// 最大流(ford fulkerson法)
#include<vector>
#include<cstring>

using namespace std;

#define INF 0x7fffffff
#define MAX_V 112345

struct edge
{
  int to;
  int cap;
  int rev;
};

vector<edge> G[MAX_V];
bool used[MAX_V];

// fromからtoへの容量capの辺を追加
void add_edge(int from,int to,int cap)
{
  G[from].push_back((edge){to,cap,(int)G[to].size()});
  G[to].push_back((edge){from,0,(int)G[from].size()-1}); 
}

int dfs(int v,int t,int f)
{
  if(v==t)
    return f;
  used[v]=true;
  for(int i=0;i<(int)G[v].size();i++)
    {
      edge &e=G[v][i];
      if(!used[e.to]&&e.cap>0)
	{
	  int d=dfs(e.to,t,min(f,e.cap));
	  if(d>0)
	    {
	      e.cap-=d;
	      G[e.to][e.rev].cap+=d;
	      return d;
	    }
	}
    }
  return 0;
}

int ford_fulkerson(int s,int t)
{
  int flow=0;
  for(;;)
    {
      memset(used,0,sizeof(used));
      int f=dfs(s,t,INF);
      if(f==0)
	return 0;
      flow+=f;
    }
}

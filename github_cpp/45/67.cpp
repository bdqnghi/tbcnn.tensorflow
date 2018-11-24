/* Ford-Fulkerson O((E+V)F*) time
O(E) memory
*/
#include<bits/stdc++.h>


using namespace std;
const int maxN=1e3+10;

int n,st,fn,m;
bool mark[maxN];
int cap[maxN][maxN];
vector<int> g[maxN],path;
#define PB push_back
/*

4 5
1 3

1 2 5
1 4 3
2 4 2
2 3 3
4 3 5
*/

void input()
{
  cin>>n>>m;
  cin>>st>>fn;
  for(int i=1;i<=m;i++)
    {
      int k1,k2,val;
      cin>>k1>>k2>>val;
      g[k1].push_back(k2);
      g[k2].push_back(k1);
      cap[k1][k2]=val;
    }
}
bool dfs(int v)
{
  mark[v]=true;
  path.PB(v);
  if(v==fn)
    return true;
  for(auto u : g[v])
    if(!mark[u] && cap[v][u]>0 )
      {
	if(dfs(u)==true)
	  return true;
      }
  path.pop_back();
  return false;
}
int Ford_Fulkerson()
{
  int MaxFlow=0;
  while(dfs(st))
    {
      int minCap=INT_MAX;
      for(int i=1;i<path.size();i++)
	minCap=min(minCap,cap[path[i-1]][path[i]]);
      for(int i=1;i<path.size();i++)
	{
	  cap[path[i-1]][path[i]]-=minCap;
	  cap[path[i]][path[i-1]]+=minCap;
	}
      MaxFlow+=minCap;
      path.clear();
      memset(mark,0,sizeof(mark));
    }
  return MaxFlow;
}
int main()
{
  input();
  int ans=Ford_Fulkerson();
  cout<<ans<<endl;
  
  return 0;
}

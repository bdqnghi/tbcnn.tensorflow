#include<iostream>
#include<vector>
#include<climits>
//Bellman Ford O(VE)

using namespace std;
const int maxN=100;
const int INF=INT_MAX/2;

vector<pair<int,int> > g[maxN];
int n,m,source;
int dist[maxN];





void input()
{
  cin>>n>>m>>source;
  for(int i=1;i<=m;i++)
    {
      int k1,k2,val;
      cin>>k1>>k2>>val;
      g[k1].push_back(make_pair(k2,val));
           g[k2].push_back(make_pair(k1,val));
      
    }
}

bool negativeCycle()
{
  for(int v=1;v<=n;v++)
    for(int i=0;i<g[v].size();i++)
      if(dist[g[v][i].first]>dist[v]+g[v][i].second)
	return true;
  return false;
}

void show()
{
  for(int i=1;i<=n;i++)
    cout<<dist[i]<< " ";
}
int main()
{
  input();
  fill(dist,dist+n+10,INF);
  dist[source]=0;
  for(int i=1;i<=n-1;i++)
    for(int v=1;v<=n;v++)
      for(int j=0;j<g[v].size();j++){
	pair<int,int> u=g[v][j];
	dist[u.first]=min(dist[u.first],dist[v]+u.second);
      }
  if(negativeCycle())
    cout<<"Negative Cycle "<<endl;
  else
    cout<<"No negative cycle"<<endl;
  
  show();
  
  return 0;
 
}

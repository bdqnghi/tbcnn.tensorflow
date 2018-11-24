#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define fore(i,n) for(int i=0;i<n;i++)
#define DFS_WHITE -1
#define DFS_GRAY 0
#define DFS_BLACK 1
vector<vii> AdjList;
vi dfs_num;
//DFS
void dfs(int u)
{
  cout<<"Node Visited"<<u<<endl;
  dfs_num[u]=DFS_BLACK;
  fore(i,AdjList[u].size())
  {
    ii v=AdjList[u][i];
    if(dfs_num[v.first]==DFS_WHITE)
    {
      dfs(v.first);
    }
  }
}

int main()
{
  int V,E,a,b;
  cin>>V>>E;
  AdjList.assign(V,vii());
  dfs_num.assign(V,DFS_WHITE);
  fore(i,E)
  {
    cin>>a>>b;
    AdjList[a].push_back(ii(b,0));
    AdjList[b].push_back(ii(a,0));
  }
  cout<<"Select the source"<<endl;
  int s;
  cin>>s;
  dfs(s);
}

#include<bits/stdc++.h>
using namespace std;
int n,m;
bool visited[100005]= {false};
vector< pair<int, int> >nodes[100005];

int min_key(bool mstset[], int n, int key[], int n )
{

  int index;
  int min_val = INT_MAX;
  for(int i=1;i<=n;i++)
  {
    if(!mstset[i]&&key[i]!=INT_MAX)
    {
      if(min_val>key[i])
      {
        min_val = key[i];
        index  = i;
      }
    }
  }
  return index;
}

void primMst()
{
    bool mstset[n+1];
    memset(mstset,false,sizeof(mstset));
    int key[n+1];
    int parent[n+1];

    memset(key,INT_MAX,sizeof(key));
    key[1] =0;
    parent[1]  = -1;
    for(int i=0;i<n-1;i++)
    {
      int u = min_key(mstset, n, key, n);
      mstset[u] = true;
      for(int j=0;j<nodes[v].size();j++)
      {
        if(!mstset[nodes[u][j]] &&  nodes[u][j].second<key[nodes[u][j]])
        {
          key[nodes[u][j]] = nodes[u][j].second;
          parent[nodes[u][j]] = u;
        }
      }
    }
    for(int i=1;i<=n;i++)
    {
      cout<<parent[i]<<"  "<<i<<"  "<<nodes[i].second<<endl;
    }
}


int main()
{
    cin>>n>>m;
  for(int i=0;i<m;i++)
  {
    int x,y,w;
    cin>>x>>y>>w;
    nodes[x].push_back(make_pair(y,w));
    nodes[y].push_back(make_pair(x,w));
  }
  primMst();

}

#include<bits/stdc++.h>
using namespace std;
int vis[1000];
vector<int>adj[10000],topo;
void topologicalsort(int source)
{
    int i;
    for(i=0;i<adj[source].size();i++)
    {
        int cur=adj[source][i];
        if(!vis[cur])
        {
            vis[cur]=1;
            topologicalsort(cur);
           topo.push_back(cur);
        }
    }
}
void clear_()
{
    memset(vis,0,sizeof(vis));
    for(int i=0;i<10000;i++)
    adj[i].clear();
    topo.clear();
}

int main()
{
    int t,n,e,u,v,i,j,k;
    cin>>t;
    for(k=1;k<=t;k++)
    {
        cin>>n>>e;
        for(j=0;j<e;j++)
        {
            cin>>u>>v;
            adj[u].push_back(v);
        }
        for(i=0;i<n;i++)
        {
            if(!vis[i])
            {
                topologicalsort(i);
                topo.push_back(i);
            }
        }
        reverse(topo.begin(),topo.end());
        for(i=0;i<n;i++)
        {
            cout<<" "<<topo[i];
        }
    }






}

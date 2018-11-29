#include<bits/stdc++.h>
using namespace std;
stack<int> s;
bool visited[10004];
vector<int> adj[10004];
int nodes,edges;
void dfs(int u)
{
    visited[u]=true;
    for(int i=0;i<adj[u].size();i++)
    {
        if(!visited[adj[u][i]])
        {
            dfs(adj[u][i]);
        }
    }
    s.push(u);
}
void topologicalsort()
{
    for(int i=0;i<nodes;i++)
    {
        if(!visited[i])
        {
            dfs(i);
        }
    }
}
int main()
{
    int i,j,n,m;
    cin>>nodes>>edges;
    for(i=0;i<edges;i++)
    {
        cin>>n>>m;
        adj[n].push_back(m);
    }
    memset(visited,0,sizeof(visited));
    topologicalsort();
    while(!s.empty())
    {
        int temp=s.top();
        s.pop();
        cout<<temp<<" ";
    }
    return 0;
}

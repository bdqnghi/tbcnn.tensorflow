#include<bits/stdc++.h>
using namespace std;
void dfs(int s,vector<int> g[],bool vis[]);

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        bool vis[100001];
        vector<int> g[100001];
        memset(g,0,sizeof g);
        memset(vis,false,sizeof vis);
        int N;
        cin>>N;
        for(int i=0;i<N;i++)
        {
            int u,v;
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1,g,vis);
        cout<<endl;
    }
}

void dfs(int s, vector<int> g[], bool vis[])
{
    cout << s << ' ';
    vis[s] = true;
    for (int i = 0; i < g[s].size(); ++i) {
        if (vis[g[s][i]] == false) {
            dfs(g[s][i], g, vis);
        }
    }
}

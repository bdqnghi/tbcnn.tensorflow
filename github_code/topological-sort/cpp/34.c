#include <bits/stdc++.h>

using namespace std;

vector<int> g[300000];
vector<int> top;
bool w[300000];
void dfs(int v){
    w[v]=true;

    for(int i=0;i<g[v].size();++i){
        if(!w[g[v][i]]) dfs(g[v][i]);
    }

    top.push_back(v);
}

int main(void){
    int n,m;
    cin>>n>>m;

    for(int i=0;i<m;++i){
        int a,b;
        cin>>a>>b;
        a--;
        b--;
        g[a].push_back(b);
    }

    for(int i=0;i<n;++i){
        if(!w[i]) dfs(i);
    }

    for(int i=0;i<top.size();++i){
        cout<<top[i]<<" ";
    }
    cout<<endl;

    return 0;
}

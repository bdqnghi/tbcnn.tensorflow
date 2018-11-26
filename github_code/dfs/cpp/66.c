/*
Graph traversal by Depth-First Search.
*/
#include <bits/stdc++.h>
using namespace std;
vector<int> edges[100];
int visited[100]; 
void dfs(int source){
    visited[source]=1;
    cout<<source<<'\n';
    for(int i=0;i<edges[source].size();i++){
        int tmp=edges[source][i];
        if(visited[tmp]==0){ // if not visited run dfs on that node
            dfs(tmp);
        }
    }
}
int main(){
    int n,e;
    cin>>n>>e;
    for(int i=1;i<=e;i++){
        int x,y;
        cin>>x>>y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    dfs(2);
    return 0;
}

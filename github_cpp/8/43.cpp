#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN=100;
vector<pair<int ,int> > graph[MAXN];
bool visited[MAXN]={0};
vector<int> tpl;

void dfs2(int src){
    visited[src]=true;
    for(auto a:graph[src]){
        if(!visited[a.first])
            dfs2(a.first);
    }
    tpl.push_back(src);
}



















int main() {
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;

        graph[x].push_back(make_pair(y,w));
    }
    for (int i = 1; i <= n; ++i) {
        if(!visited[i])
            dfs2(i);
    }
    reverse(tpl.begin(),tpl.end());
    cout<<"Topological Sort: ";
    for(auto a:tpl)
        cout<<a<<" ";
    return 0;
}
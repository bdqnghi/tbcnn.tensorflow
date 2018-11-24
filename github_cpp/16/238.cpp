//topological sort
#include <bits/stdc++.h>
using namespace std;
struct graph{
    int src, dest,wt;
};
void top_util(vector<vector<int> > &g,int visited[], stack<int> &us, stack<int> &vs){
    if(us.empty()) return;
    while(!us.empty()){
        int top = us.top();
        us.pop();
        for(int i = 0;i<g[top].size();i++){
            if(!visited[g[top][i]]){
                vs.push(g[top][i]);
                visited[g[top][i]] = 1;
            }
        }
    }
}
void top_sort(vector<vector<int> > &g, int n){
    int visited[1000];
    stack<int> us;
    stack<int> vs;
    for(int i=0;i<n;i++){
        visited[i] = 0;
        us.push(i);
    }
    top_util(g,visited,us,vs);
    // while(!us.empty()){
    //     int top = us.top();
    //     us.pop();
    // }
}
int main(){
    int v,e,src,dest,wt;
    vector<vector<int> > g;
    cin>>v>>e;
    g.resize(v+1);
    //vertex start from 0
    for(int i=0;i<e;i++){
        cin>>src>>dest;
        v[src].push_back(dest);
    }
    top_sort(g,v);
    return 0;
}

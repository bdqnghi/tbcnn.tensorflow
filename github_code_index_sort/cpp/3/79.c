// Problem Link: https://practice.geeksforgeeks.org/problems/topological-sort/1

#include<bits/stdc++.h>
using namespace std;
vector<int> graph[10001];
int * topoSort(vector<int> graph[],int N);
int main(){
  int T;
  cin>>T;
  while(T--){
      memset(graph,0,sizeof graph);
      int N,E;
      cin>>E>>N;
      for(int i=0;i<E;i++)
      {
          int u,v;
          cin>>u>>v;
          graph[u].push_back(v);
      }
      int *res = topoSort(graph,N);
      bool valid =true;
      for(int i=0;i<N;i++)
      {
          int n=graph[res[i]].size();
          for(int j=0;j<graph[res[i]].size();j++)
          {
              for(int k=i+1;k<N;k++)
              {
                  if(res[k]==graph[res[i] ] [j] )
                      n--;
              }
          }
          if(n!=0)
          {
              valid =false;
              break;
          }
      }
      if(valid==false)
          cout<<0<<endl;
      else
          cout<<1<<endl;
  }
}

void dfs_topo(int s,vector<int>g[],int vis[],queue<int> &q){
    vis[s] = 1;
    for(int i=0;i<g[s].size();i++){
        if(vis[g[s][i]]==0)
            dfs_topo(g[s][i],g,vis,q);
    }
    q.push(s);
}

int * topoSort(vector<int> g[], int N){
    queue<int>q;
    int vis[N];
    for(int i=0;i<N;i++)    
        vis[i] = 0;
    for(int i=0;i<N;i++){
        if(vis[i]==0)
            dfs_topo(i,g,vis,q);
    }
    int *a = new int[N];
    for(int i=N-1;i>=0;i--){
        a[i] = q.front();
        q.pop();
    }
    return a;
}

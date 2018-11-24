#include<iostream>
#include<vector>
#include<stdio.h>
using namespace std;

vector<int> adj[10000];
int  ti, dis[10000], fin[10000], color[10000];

void dfs(int source)
{
    int u = source;
    ti = ti + 1;
    dis[u] = ti;
    color[u] = 1;
    for(int i=0;i<adj[u].size();i++){
        int v = adj[u][i];
        if(color[v]==0){
            printf("%d ",v);
            dfs(v);
        }
    }
    color[u] = 2;
    ti = ti + 1;
    fin[u] = ti;
}

int main()
{
    int i, j, k, n, e, u, v, source;
    printf("Please Enter number of vertices: ");
    scanf("%d",&n);
    printf("Please Enter number of edges: ");
    scanf("%d",&e);
    printf("Please Enter the edges:\n");
    for(i=0;i<e;i++){
        scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    printf("Please Enter the source: ");
    scanf("%d",&source);

    printf("Visited nodes are %d ",source);
    dfs(source);

    return 0;

}



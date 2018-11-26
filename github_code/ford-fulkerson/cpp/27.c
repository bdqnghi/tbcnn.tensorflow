#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
#define MAX_NODES 5005
#define INF 1000000007
using namespace std;
vector< vector<int> > adjList(MAX_NODES, vector<int>());
queue<int>nextNodes;
int cap[MAX_NODES][MAX_NODES];
bool visited[MAX_NODES];
int getFlow(int curr, int sink, int fl)
{
    visited[curr]=true;
    if(curr==sink)
        return fl;
    for(int i=0; i<adjList[curr].size(); i++)
    {
        if(!visited[adjList[curr][i]] && cap[curr][adjList[curr][i]]!=0)
        {
            int c=getFlow(adjList[curr][i], sink, min(fl, cap[curr][adjList[curr][i]]));
            if(visited[sink])
            {
                cap[curr][adjList[curr][i]]-=c;
                cap[adjList[curr][i]][curr]+=c;
                return c;
            }
        }
    }
}

int FordFulkerson(int source, int sink, int nodes)
{
    if(source==sink)
        return 0;
    int maxFlow=0, c=0;
    do{
        c=getFlow(source, sink, INF);
        maxFlow+=c;
        memset(visited, 0, sizeof(visited));
    }while(c!=0);
    return maxFlow;
}

int main()
{
    int n, m, source, sink;
    cin>>n>>m;
    source=1; sink=n;
    for(int i=0; i<m; i++)
    {
        int x, y, w;
        cin>>x>>y>>w;
        if(cap[x][y]==0 && cap[y][x]==0){
            adjList[x].push_back(y);
            adjList[y].push_back(x);
        }
        cap[x][y]+=w;
    }
    int maxFlow=FordFulkerson(source, sink, n);
    cout<<maxFlow<<endl;
}
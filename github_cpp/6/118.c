#include<iostream>
#include<vector>
using namespace std;
void dfs(vector<int>[],int ,int );
void dfsearch(vector<int>[],int ,int[]);
int main()
{
int n;
cin>>n;
int x,y;
vector<int>graph[n];
for(int i=0;i<6;i++)
    {
        cin>>x>>y;
        graph[x].push_back(y);
    }
int s;
cin>>s;
dfs(graph,s,n);
}
void dfs(vector<int>graph[],int s,int n)
{
 int color[n];
 for(int i=0;i<n;i++)
    color[i]=0;
    dfsearch(graph,s,color);
}
void dfsearch(vector<int>graph[],int s,int color[])
{
    color[s]=1;
    cout<<s<<"->";
    for(int i=0;i<graph[s].size();i++)
    {
        if(color[graph[s][i]]==0)
            dfsearch(graph,graph[s][i],color);
    }
}

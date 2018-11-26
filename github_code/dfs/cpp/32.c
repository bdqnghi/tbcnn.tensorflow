/*
* Author: Jony Roy
* Date: 25-06-2016
* Contact: jonyroyice@gmail.com
*/
#include <bits/stdc++.h>
#define PI              3.1415926535897932384
#define EulerConstant   0.5772156649015328606
#define CountBit(a)     __builtin_popcount(a)
#define p_b(x)          push_back(x)
#define m_p(x)          make_pair(x)
#define ft              first
#define sd              second
using namespace std;
typedef double                   ddd;
typedef long long int            llint;
typedef unsigned long long int   ullint;
typedef long int                 lint;
typedef unsigned int             uint;
typedef unsigned long int        ulint;
typedef pair<int,int>            pint;
typedef pair<lint,lint>          plint;
typedef pair<llint,llint>        pllint;

#define CNT 1005

llint bigMod(llint a,llint b,llint MOD)
{
    if(b==0)
        return 1;
    llint temp=bigMod(a,b>>1,MOD);
    temp=(temp*temp)%MOD;
    if(b&1)
        temp= (a*temp)%MOD;
    return temp;
}

vector<int> adj[CNT];
int visited[CNT];
int edge_id[CNT];
int parent[CNT];
int depthFirstSearch(int source,int nodes)
{
    int cnt=0;
    parent[source]=0;
    for(int i=1;i<=nodes;i++)
    {
        edge_id[i]=0;
        visited[i]=0;
    }
    stack<int> S;
    visited[source]=1;
    S.push(source);
    cout<<source<<" ";
    cnt++;
    while(!S.empty())
    {
        int u=S.top();
        S.pop();
        while(edge_id[u]<adj[u].size())
        {
            int v=adj[u][edge_id[u]];
            edge_id[u]++;
            if(visited[v]==0)
            {
                cnt++;
                cout<<v<<" ";
                parent[v]=u;
                visited[v]=1;
                S.push(u);
                S.push(v);
                break;
            }
        }
    }
    return cnt;
}
int ParentPrint(int n)
{
    if(parent[n]==0)
        return 0;
    int v=parent[n];
    ParentPrint(parent[v]);
    cout<<v<<" ";
}
int main(int argc, char *argv[])
{
   int n,edge;
   cin>>n>>edge;
   for(int i=1;i<=edge;i++)
   {
       int u,v;
       cin>>u>>v;
       adj[u].push_back(v);
   }
   int m=100000;
   for(int i=1;i<=n;i++)
   {
           for(int j=1;j<=n;j++)
           parent[j]=0;
           int k=depthFirstSearch(i,n);
           cout<<endl;
           if(m>k)
           {
               m=k;
           }
   }
   cout<<m<<endl;
   return 0;
}


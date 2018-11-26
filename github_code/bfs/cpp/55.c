#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
#include<vector>
#include<queue>
#include<stack>
#include<bitset>
#include<utility>
#include<limits.h>

#define v2d(a,n,m) vector< vector<int> > a(n,vector<int>(m,0))
#define v1d(a,n) vector<int> a(n,0)
#define ve(a) vector<int> a
#define v2e(a) vector< vector<int> > a
#define frl(i,n,m) for(int i=n;i<m;i++)
#define frl1(i,n,m) for(int i=n;i<=m;i++)
#define testcase int t;cin>>t;while(t--)
using namespace std;
typedef pair<int,int> pi;
int level[1000];
bool visited[1000];
int n,m,x,y,s;
void bfs(int node,vector<int> graph[])
{
    queue<int> q;
    q.push(node);
    //visted[s]=true;
    level[node]=0;
    while(!q.empty())
    {
        int p=q.front();
        q.pop();
        if(visited[p]==false)
        {
            visited[p]=true;
            frl(i,0,graph[p].size())
            {
             //   cout<<graph[p][i]<<" ";
                if(visited[graph[p][i]]==false);
                {
                    q.push(graph[p][i]);

                    if(level[graph[p][i]]==-1)
                        level[graph[p][i]]=level[p]+1;
                }
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);

    testcase
    {
        cin>>n>>m;
        vector<int> node[n];

        frl(i,0,m)
        {
            cin>>x>>y;
            node[x-1].push_back(y-1);
            node[y-1].push_back(x-1);
        }
        cin>>s;
        s--;
        memset(level,-1,sizeof(level));
        memset(visited,false,sizeof(visited));

        bfs(s,node);
        frl(i,0,n)
        {
            if(level[i]==-1)
                cout<<-1<<" ";
            else if(i!=s)
                cout<<level[i]*6<<" ";
        }
        cout<<endl;
    }
    return 0;
}

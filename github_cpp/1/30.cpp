




vector <int> v[10] ;   
int level[10]; 
bool vis[10]; 
void bfs(int s) {
    queue <int> q;
    q.push(s);
    level[ s ] = 0 ;  
    vis[ s ] = true;
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        for(int i = 0;i < v[ p ].size() ; i++)
        {
            if(vis[ v[ p ][ i ] ] == false)
            {
        
                level[ v[ p ][ i ] ] = level[ p ]+1;                 
                 q.push(v[ p ][ i ]);
                 vis[ v[ p ][ i ] ] = true;
  }
        }
    }
}




void bfs (int start)
{
            deque <int > Q;     
            Q.push_back( start); 
            distance[ start ] = 0;       
            while( !Q.empty ())
            {
                int v = Q.front( );
                Q.pop_front(); 
                for( int i = 0 ; i < edges[v].size(); i++)
               {


  


                    if(distance[ edges[ v ][ i ].first ] > distance[ v ] + edges[ v ][ i ].second ) 
                {

                    distance[ edges[ v ][ i ].first ] = distance[ v ] + edges[ v ][ i ].second;

                

                    if(edges[ v ][ i ].second == 0)
                    {
                        Q.push_front( edges[ v ][ i ].first);
                    }
                    else
                    {
                            Q.push_back( edges[ v ][ i ].first);

                    }
                }
              }
           }
    }




#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define N 100001
vector<int>adj[N];
bool visited[N];
int level[N];
int counter[N];

void bfs(int s) 
{
    queue <int> q;
    q.push(s);
    level[ s ] = 0 ;
    visited[ s ] = true;
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        for(int i = 0; i < adj[ p ].size() ; i++)
        {
            if(!visited[ adj[ p ][ i ] ])
            {
                level[ adj[ p ][ i ] ] = level[ p ]+1;                 
                q.push(adj[ p ][ i ]);
                visited[ adj[ p ][ i ] ] = true;
            }
        }
    }
}

int main()
{
    memset(visited,false,sizeof(visited));
    memset(counter,0,sizeof(counter));
    int n,val;
    cin>>n;
    for(int i=0;i<n-1;i++)
    {
        int x,y;cin>>x>>y;
        x--;y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    cin>>val;
    bfs(0);
    for(int i=0;i<n;i++)
    {
        counter[level[i]]++;
    }
    cout<<counter[val-1];
    return 0;
}

// Breadth First Search

// 1. How to determine the level of each node in the given tree?


vector <int> v[10] ;   //Vector for maintaining adjacency list explained above
int level[10]; //To determine the level of each node
bool vis[10]; //Mark the node if visited 
void bfs(int s) {
    queue <int> q;
    q.push(s);
    level[ s ] = 0 ;  //Setting the level of the source node as 0
    vis[ s ] = true;
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        for(int i = 0;i < v[ p ].size() ; i++)
        {
            if(vis[ v[ p ][ i ] ] == false)
            {
        //Setting the level of each node with an increment in the level of parent node
                level[ v[ p ][ i ] ] = level[ p ]+1;                 
                 q.push(v[ p ][ i ]);
                 vis[ v[ p ][ i ] ] = true;
  }
        }
    }
}


// 2. 0-1 BFS 

void bfs (int start)
{
            deque <int > Q;     //Double-ended queue
            Q.push_back( start); 
            distance[ start ] = 0;       
            while( !Q.empty ())
            {
                int v = Q.front( );
                Q.pop_front(); 
                for( int i = 0 ; i < edges[v].size(); i++)
               {


/* if distance of neighbour of v from start node is greater than sum of distance of v from start node and edge weight between v and its neighbour (distance between v and its neighbour of v) ,then change it */  


                    if(distance[ edges[ v ][ i ].first ] > distance[ v ] + edges[ v ][ i ].second ) 
                {

                    distance[ edges[ v ][ i ].first ] = distance[ v ] + edges[ v ][ i ].second;

                /*if edge weight between v and its neighbour is 0 then push it to front of
        double ended queue else push it to back*/

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


// Level Nodes 

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

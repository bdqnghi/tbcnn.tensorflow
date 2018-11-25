#include <bits/stdc++.h>

using namespace std;

#define  DFS_BLACK  1
#define  DFS_WHITE  0

const int maxn = 105;
vector <int> Ts, graph[maxn];
bool used[maxn];

void dfs( int v );
void reset( int n );

int main()
{
    int nodes, edges, u, v;

    while( scanf("%d %d", &nodes, &edges) == 2 )
    {
        reset( nodes );
        Ts.clear();
        memset( used, 0, sizeof used );

        for( int i = 0; i < edges; i++ )
        {
            scanf("%d %d", &u, &v);
            graph[u].push_back( v );
        }

        for( int i = 1; i <= nodes; i++ )
        {
            if( used[i] == false )
            {
                dfs(i);
            }
        }

        reverse( Ts.begin(), Ts.end() );

        printf("%d", Ts[0] );
        for( int i = 1; i < Ts.size(); i++ )
        {
            printf(" %d", Ts[i] );
        }
        cout << endl;
    }
    return 0;
}

void dfs( int u )
{
    used[u] = DFS_BLACK;

    for( auto child: graph[u] )
    {
        if( used[ child ] == DFS_WHITE )
        {
            dfs( child );
        }
    }
    Ts.push_back( u );
}

void reset( int n )
{
    for( int i = 1; i <= n; i++ )
    {
        graph[i].clear();
    }
}

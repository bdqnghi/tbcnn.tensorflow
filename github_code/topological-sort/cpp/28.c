//
//  topologicalsort.cpp
//  Codeforces
//
//  Created by Vishal Patel on 22/12/2014.
//  Copyright (c) 2014 Vishal Patel. All rights reserved.
//


#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef vector<string> vs;

// Basic macros
#define st          first
#define se          second
#define ALL(x)      (x).begin(), (x).end()
#define ini(a, v)   memset(a, v, sizeof(a))
#define re(i,s,n)  	for(int i=s;i<(n);++i)
#define rep(i,s,n)  for(int i=s;i<=(n);++i)
#define fr(i,n)     re(i,0,n)
#define repv(i,f,t) for(int i = f; i >= t; --i)
#define rev(i,f,t)  repv(i,f - 1,t)
#define frv(i,n)    rev(i,n,0)
#define pu          push_back
#define mp          make_pair
#define sz(x)       (int)(x.size())

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define CLR(a) a.clear()
#define SET(a,b) memset(a,b,sizeof(a))
#define LET(x,a) __typeof(a) x(a)
#define TR(v,it) for( LET(it,v.begin()) ; it != v.end() ; it++)
#define FORi(i,a,b) for(LET(i,a) ; i<b; i++)
#define repi(i,n) FORi(i,(__typeof(n))0,n)
#define FOR(i,a,b) for(i=a ; i<b; i++)
#define si(n) scanf("%d",&n)
#define sll(n) scanf("%lld",&n)
#define pi(n) printf("%d",n)
#define piw(n) printf("%d ",n)
#define pin(n) printf("%d\n",n)
#define sortv(a) sort(a.begin(),a.end())
#define DRT()  int t; cin>>t; while(t--)
#define DRI(n)  int n; cin>>n;
#define DRII(n,m)  int n,m; cin>>n>>m;

const int oo = 2000000009;
const double eps = 1e-9;

#ifdef TRACE
#define trace1(x)                cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
#define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;

#else

#define trace1(x)
#define trace2(x, y)
#define trace3(x, y, z)
#define trace4(a, b, c, d)
#define trace5(a, b, c, d, e)
#define trace6(a, b, c, d, e, f)

#endif
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int , ii> iii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef vector<vector<int > > vvi;
typedef vector<string> vs;
#define VISITED 1

#define fin cin

namespace TopologicalSort {
    
    class Graph{
        
        list<int> *adj;
        int V;
        
    public:
        
        Graph (int v)
        {
            V = v;
            adj = new list<int>[V];
        }
        
        void addEdge(int v, int w)
        {
            adj[v].push_back(w);
        }
        
        void topologicalSortUtil(int v, bool visited[] , stack<int> &Stack)
        {
            visited[v] = true;
            for (auto i = adj[v].begin() ; i != adj[v].end() ; ++i )
            {
                if ( !visited[*i] )
                {
                    topologicalSortUtil(*i, visited, Stack);
                }
            }
            
            Stack.push(v);
        }
        
        
        void topologicalSort()
        {
            
            stack<int> Stack;
            bool *visited = new bool[V];
            for (int i = 0; i < V; i++)
                visited[i] = false;
            
            
            for ( int i = 0 ; i < V ; i++ )
            {
                if ( visited[i] == false)
                {
                    topologicalSortUtil(i, visited, Stack);
                }
            }
            
            
            while ( !Stack.empty() ) {
                
                cout << Stack.top() << " ";
                Stack.pop();
            }
            
        }
        
    };
}

int main_topsort    ()
{
    fstream fin("/Users/Shared/codeforces/codeforces/uva/topologicalsort.txt");
    
    int V;
    cin >> V;
   
    TopologicalSort::Graph g(V);
    
    int edges;
    cin >> edges;
    for ( int i = 0 ; i < edges ; i++ )
    {
        int v,w;
        cin >> v >> w;
        g.addEdge(v, w);
    }

    g.topologicalSort();
    
    return 0;
}



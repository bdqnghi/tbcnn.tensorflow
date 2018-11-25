#ifndef fordfulkerson_h
#define fordfulkerson_h

#include "data-structures/vector.h"
#include "data-structures/graph.h"
typedef long long ll;

class FordFulkerson {

    public:
        FordFulkerson(Graph g);
        
        
        ll max();
    
    private:
        
        ll n,m;
        
        Graph g;
        
        void dfs(ll node, vector<bool> &visited);
        
        vector<ll> lastPath;
        
        ll maxFlow;
};

#endif
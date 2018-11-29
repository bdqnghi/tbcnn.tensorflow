#include <topological_sort.h>

#include <limits>
#include <set>
#include <stack>

using namespace std;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    TopologicalSort::TopologicalSort(const IGraph &rG) :
        _marked          (rG.vertices(), false),
        _reversePost     ()
    {
        for(int v = 0; v < rG.vertices(); ++v)
            dfs(rG, v);
    }

    //--------------------------------------------------------------------------
    TopologicalSort::~TopologicalSort()
    {}

    //--------------------------------------------------------------------------
    void TopologicalSort::dfs(const IGraph &rG, int v)
    {
        _marked[v] = true;
        
        const IGraph::container_t & rAdjList = rG.adjacent(v);
        
        for(IGraph::const_iterator it = rAdjList.begin(); it != rAdjList.end(); ++it)
        {
            if(!_marked[*it])
                dfs(rG, *it);

            _reversePost.push(v);            
        }
        
    }

    //--------------------------------------------------------------------------
    bool TopologicalSort::hasPathTo(int v)
    { 
        return _marked[v];
    }

    //--------------------------------------------------------------------------
    void TopologicalSort::pathTo(stack<int> &rPath, int v)
    {
        rPath = _reversePost;
    }

}

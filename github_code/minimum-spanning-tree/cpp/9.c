#include <minimum_spanning_tree.h>
#include <quick_union_find.h>

using namespace std;
using namespace UnionFind;

namespace Graph
{
    //==========================================================================
    //--------------------------------------------------------------------------
    MinimumSpanningTree::MinimumSpanningTree(const EdgeWeightedGraph &rG) :
        _rG            (rG),
        _kruskalMST    (),
        _primMST       ()
    {
        kruskalMST();
        primMST();
    }

    //--------------------------------------------------------------------------
    MinimumSpanningTree::~MinimumSpanningTree()
    {}

    //--------------------------------------------------------------------------
    const EdgeWeightedGraph & MinimumSpanningTree::graph()
    {
        return _rG;
    }

    //--------------------------------------------------------------------------
    const queue<Edge> & MinimumSpanningTree::KruskalMST()
    {
        return _kruskalMST;
    }

    //--------------------------------------------------------------------------
    const queue<Edge> & MinimumSpanningTree::PrimMST()
    {
        return _primMST;
    }

    //============================================================================
    //Running time : Kruskal's MST
    //Build PQ   : ElgE
    //Delete Min : ElgE
    //Union      : Vlg*V
    //Connected  : Elg*V
    //Total time : ElgE
    //--------------------------------------------------------------------------
    void MinimumSpanningTree::kruskalMST()
    { 
        EdgeWeightedGraph::edge_container_t edges;

        _rG.edges(edges);
        
        priority_queue<Edge, vector<Edge>, greater<Edge> > pq(edges.begin(), edges.end());
        
        QuickUnionFind quf(_rG.vertices());

        //An MST is acyclic so it contains no more than V-1 edges
        while(!pq.empty() && static_cast<int>(_kruskalMST.size()) < _rG.vertices() - 1)
        {
            const Edge & top = pq.top();
            
            int v = top.either(), w = top.other(v);

            //Adding edge with least weight does not form cycle
            if(!quf.connected(v, w))
            {
                quf.make_union(v, w);
                _kruskalMST.push(top);
            }
            
            pq.pop();
        }
        
    }

    //============================================================================
    //Running time : Prim's MST (Lazy implementation)
    //Build PQ   : ElgE
    //Delete Min : ElgE
    //Total time : ElgE
    //--------------------------------------------------------------------------
    void MinimumSpanningTree::primMST()
    { 
        vector<bool> marked(_rG.vertices(), false);

        priority_queue<Edge, vector<Edge>, greater<Edge> > pq;
        
        //Add all edges from source to PQ
        visit(marked, 0, pq);

        //An MST is acyclic so it contains no more than V-1 edges        
        while(!pq.empty() && static_cast<int>(_primMST.size()) < _rG.vertices() - 1)
        {
            const Edge & top = pq.top();
            
            int v = top.either(), w = top.other(v);
            
            //Both vertices of this edge are part of MST
            if(marked[v] && marked[w])
            {
                pq.pop();
                continue;
            }
            else
            {
                _primMST.push(top);
                pq.pop();                

                if(!marked[v])
                    visit(marked, v, pq);
                
                if(!marked[w])
                    visit(marked, w, pq);
            }
        }
    }

    //--------------------------------------------------------------------------    
    void MinimumSpanningTree::visit(vector<bool> &rMarked, int v,
                                    priority_queue<Edge, vector<Edge>, greater<Edge> > &rPQ)
    {
        rMarked[v] = true;

        for(EdgeWeightedGraph::edge_const_iterator it = _rG.adjacent(v).begin(); 
            it != _rG.adjacent(v).end(); ++it)
        {
            if(!rMarked[it->other(v)])
                rPQ.push(*it);
        }
        
    }
    
}

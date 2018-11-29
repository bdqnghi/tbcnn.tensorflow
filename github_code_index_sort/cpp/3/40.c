//**************************************************************
//                  Topological Sort
//**************************************************************

#ifndef TOPOLOGICALSORT_H
#define TOPOLOGICALSORT_H

#include "Digraph.h"
#include "DirectedCycle.h"
#include "DepthFirstOrder.h"
#include "EdgeWeightedDirectedCycle.h"
#include "EdgeWeightedDigraph.h"

class TopologicalSort
{
public:
    TopologicalSort(Digraph& g)
    {
        DirectedCycle dc(g);
        bool hasCycle = dc.HasCycle();
        if (!hasCycle)
        {
            DepthFirstOrder dfo(g);
            stack<int> reversePostOrder = dfo.ReversePostOrder();
            while (!reversePostOrder.empty())
            {
                int v = reversePostOrder.top();
                order.push_back(v);
                reversePostOrder.pop();
            }
        }
    }

    // Extend topologicalSort for Edge-weighted Digraph.
    TopologicalSort(EdgeWeightedDigraph& g)
    {
        EdgeWeightedDirectedCycle dc(g);
        bool hasCycle = dc.HasCycle();
        if (!hasCycle)
        {
            DepthFirstOrder dfo(g);
            stack<int> reversePostOrder = dfo.ReversePostOrder();
            while (!reversePostOrder.empty())
            {
                int v = reversePostOrder.top();
                order.push_back(v);
                reversePostOrder.pop();
            }
        }
    }

    ~TopologicalSort()
    {
    }

    // only graph is DAG(which has no cycle) can have topo-order.
    bool IsDAG()
    {
        return !order.empty();
    }

    // vertices in topological order.
    vector<int> Order()
    {
        return order;
    }

private:
    vector<int> order;
};

#endif

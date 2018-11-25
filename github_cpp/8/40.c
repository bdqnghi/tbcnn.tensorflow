



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

    
    bool IsDAG()
    {
        return !order.empty();
    }

    
    vector<int> Order()
    {
        return order;
    }

private:
    vector<int> order;
};

#endif

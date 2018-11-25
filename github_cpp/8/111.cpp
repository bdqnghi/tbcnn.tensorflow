#include "TopologicalSort.h"

int TopoLogicalSort::EdgeClassification(int x, int y)
{
    return 0;
}

void TopoLogicalSort::TopoSort()
{

    for (int i = 1; i <= m_g->nvertices; i++)
    {
        if (discovered[i] == false)
        {
            DepthFirstSearch(i);
        }
    }

    while (!m_stack.empty())
    {
        cout << m_stack.top() << " ";
        m_stack.pop();
    }

}

void TopoLogicalSort::ProcessVertexLate(int v)
{
    m_stack.push(v);
}

void TopoLogicalSort::ProcessEdge(int x, int y)
{
    
}



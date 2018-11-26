//
//  DepthFirstSearch.cpp
//  DailyCoding
//
//  Created by limingding on 11/13/16.
//  Copyright © 2016 limingding. All rights reserved.
//

#include "DepthFirstSearch.h"
#include "Graph.h"
#include <assert.h>

DepthFirstSearch::DepthFirstSearch(Graph graph, int s):
m_nCount(0)
{
    for (int i = 0; i < graph.GetVertexesCount(); ++i)
    {
        m_vMarked.push_back(false);
    }
    Dfs(graph, s);
}

DepthFirstSearch::~DepthFirstSearch()
{
    
}

bool DepthFirstSearch::IsMarked(int w)
{
    assert(w >= 0 && w < m_vMarked.size());
    return  m_vMarked[w];
}

int DepthFirstSearch::Count()
{
    return m_nCount;
}

void DepthFirstSearch::Dfs(Graph graph, int v)
{
    m_vMarked[v] = true;
    m_nCount++;

    int w = 0;
    for (int i = 0; i < graph.Adjacent(v).size(); ++i)
    {
        w = graph.Adjacent(v)[i];
        if (!IsMarked(w))
        {
            Dfs(graph, w);
        }
    }
}

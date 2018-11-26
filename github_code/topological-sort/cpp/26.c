#include "TopologicalSort.h"

#include <algorithm> // std::reverse

std::vector<int> TopologicalSort::m_res;
std::vector<char> TopologicalSort::m_vis;
std::vector<std::vector<int> > TopologicalSort::m_g;

std::vector<int> TopologicalSort::Sort(int n, std::vector<std::vector<int> > g)
{
    m_g = g;
    m_vis = std::vector<char> (n);
    m_res.clear();

    for (int i = 0; i < n; ++i)
    {
        if (!m_vis[i])
        {
            TopologicalSort::dfs(i);
        }
    }
    std::reverse(m_res.begin(), m_res.end());
    return m_res;
}

void TopologicalSort::dfs(int v)
{
    m_vis[v] = true;
    for (const auto& i: m_g[v])
    {
        if (!m_vis[i])
        {
            TopologicalSort::dfs(i);
        }
    }
    m_res.push_back(v);
}
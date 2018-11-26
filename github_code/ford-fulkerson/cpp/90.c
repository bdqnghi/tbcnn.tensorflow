/*
 * FordFulkersonSolver.cpp
 *
 *  Created on: Nov 14, 2018
 *      Author: daniel
 */

#include <algorithm>
#include <stack>
#include <sstream>

#include "FordFulkersonSolver.h"
#include "Graph.h"

FordFulkersonSolver::FordFulkersonSolver()
{
	 m_max_flow = 0;
}

FordFulkersonSolver::~FordFulkersonSolver()
{

}

void FordFulkersonSolver::solveMaxFlow(const Graph& G, const int s, const int t)
{
	int u, v;

	// Graph is a V x V matrix)
	const int V = G.size();

	std::vector<int> path;
	path.reserve(V);

	// create residual graph and populate with original capacities
	Graph G_f;

	G_f = G;


	// DFS finds all augmenting paths
	while(DFS(G_f, s, t, path))
	{
		int path_flow = std::numeric_limits<int>::max();
		for(v = t; v != s; v = path[v])
		{
			u = path[v];
			path_flow = std::min(path_flow, G_f[u][v]);
		}
		std::stringstream ss;

		for(v = t; v != s; v = path[v])
		{
			u = path[v];
			G_f[u][v] -= path_flow;
			G_f[v][u] += path_flow;
			ss << v << ",";
		}
		std::string path_string = ss.str();
		path_string.pop_back();
		std::reverse(path_string.begin(), path_string.end());
		std::cout << path_string << std::endl;

		m_max_flow += path_flow;
	}
}

bool FordFulkersonSolver::DFS(const Graph& G_f, const int s, const int t, std::vector<int>& path)
{
	// Graph is V x V matrix
	const unsigned int V = G_f.size();

	std::vector<bool> visited;
	std::stack<int> stack;

	visited.reserve(V);

	// initialize all vertices as not visited
	for(unsigned int ii = 0; ii < V; ++ii)
	{
		visited[ii] = false;
	}
	stack.push(s);

	// DFS loop
	while(!stack.empty())
	{
		const int u = stack.top();
		stack.pop();
		if(!visited[u])
		{
			visited[u] = true;
			for(unsigned int v = 0; v < V; ++v)
			{
				if(!visited[v] && G_f[u][v] > 0)
				{
					stack.push(v);
					path[v] = u;
				}
			}
		}

	}
	return visited[t];


}



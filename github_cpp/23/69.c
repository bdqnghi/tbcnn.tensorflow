#include "FordFulkerson.h"
#include <limits>
#include <algorithm>
#include <queue>

bool FordFulkerson::hasAugumentingPath(int s, int t)
{
	marked = std::vector<bool>(fNet.getVertexCount(), false);
	edgeTo = std::vector<FlowEdge>(fNet.getVertexCount(), FlowEdge(0, 0, 0));
	std::queue<int> q;
	q.push(s);
	marked[s] = true;

	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		FlowNetwork::EdgesList adjList = fNet.getAdjacentVertex(v);
		for (auto i = adjList.begin(); i != adjList.end(); ++i)
		{
			int w = i->other(v);
			if (!marked[w] && i->getResidualCapacityTo(w) > 0)
			{
				edgeTo[w] = *i;
				marked[w] = true;
				q.push(w);
			}
		}
	}

	return marked[t];
}

void FordFulkerson::dfs(int v)
{
	marked[v] = true;
	minCut.push_back(v);
	FlowNetwork::EdgesList adjList = fNet.getAdjacentVertex(v);
	for (auto i = adjList.begin(); i != adjList.end(); ++i)
	{
		if (marked[i->other(v)])
			continue;
		if ( (i->from() == v) && (i->getFlow() != i->getCapacity()) )
			dfs(i->to());
		else if ( (i->to() == v) && (i->getFlow() != 0) )
			dfs(i->from());
	}
}

FordFulkerson::FordFulkerson(const FlowNetwork& flowNet, int s, int t) : MaxFlow(0), fNet(flowNet)
{
	while (hasAugumentingPath(s, t))
	{
		int minFlowToAdd = std::numeric_limits<int>::max();
		for (int v = t; v != s; v = edgeTo[v].other(v))
			minFlowToAdd = std::min(minFlowToAdd, edgeTo[v].getResidualCapacityTo(v));
		
		for (int v = t; v != s; v = edgeTo[v].other(v))
			fNet.addFlow(edgeTo[v].from(), edgeTo[v].to(), minFlowToAdd);
		
		MaxFlow += minFlowToAdd;
	}

	marked = std::vector<bool>(fNet.getVertexCount(), false);
	dfs(s);
} 

int FordFulkerson::getMaxFlow()
{
	return MaxFlow;
}

FordFulkerson::MinCutVertecies FordFulkerson::getMinCutVertecies()
{
	return minCut;
}
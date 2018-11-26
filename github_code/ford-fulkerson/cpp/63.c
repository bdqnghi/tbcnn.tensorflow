#include "fordfulkerson.h"

#include <vector>
#include <iostream>
#include <queue>


bool FordFulkerson::augmentingPathExists (int source, int sink, Graph& g, std::vector<Node>& path)
{
	std::queue <int> q;
	std::vector <bool> visited (g.size(), false);
	path = std::vector <Node> (g.size(), {-1, nullptr});
	visited[source] = true;

	q.push (source);
	bool reachedSink = false;
	while (!q.empty() && !reachedSink)
	{
		int c = q.front(); q.pop();

		for (int i = 0; i < g[c].size(); ++i)
		{
			// if the residual capacity is more than 0 there is a path
			if (g[c][i] -> getResidualCapacity (c) > 0)
			{
				int to = g[c][i] -> getTo();	
				int from = g[c][i] -> getFrom();	

				int a = (c == from) ? to : from;

				// if the sink is reached
				if (a == sink)
				{
					path[a].parent = c;
					path[a].edge   = g[c][i];
					reachedSink = true;
					break;
				}

				if (!visited[a])
				{
					visited[a] = true;
					q.push (a);
					path[a].parent = c;
					path[a].edge   = g[c][i];
				}
			}
		}
	}

	return reachedSink;
}

int FordFulkerson::findBottleNeck (int sink, Graph& g, std::vector<Node>& path)
{
	int bottleneck = 200000;
	int i = sink;
	while (path[i].parent != -1)
	{
		int from = path[i].parent;
		bottleneck = std::min (bottleneck, path[i].edge -> getResidualCapacity (from));
		i = from;
	}

	return bottleneck;
}

void FordFulkerson::augmentPath (int sink, Graph& g, std::vector<Node>& path, int p_flow)
{
	int i = sink;
	while (path[i].parent != -1)
	{
		int from = path[i].parent;
		path[i].edge -> addFlow (p_flow, from);
		i = from;
	}
}

int FordFulkerson::computeMaxFlow (int source, int sink, FlowNetwork& fn)
{
	fn.initializeFlowToZeroOnAllEdges();
	Graph& g = fn.getGraph();

	std::vector <Node> path; 


	while (augmentingPathExists (source, sink, g, path))
	{
		int bottleneck = findBottleNeck (sink, g, path);
		augmentPath (sink, g, path, bottleneck);
	}


	int maxFlow = 0;
	for (int i = 0; i < g[source].size(); ++i)
	{
		maxFlow += g[source][i] -> getFlow();	
	}
	return maxFlow;
}

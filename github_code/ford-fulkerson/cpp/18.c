#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <queue>

#include "FordFulkerson.hpp"

void algorithms::FordFulkerson::run()
{
	int maxFlow = this->fordFulkerson(this->source, this->target);

	std::stringstream stream;
	stream << "Fluxo máximo\n";
	stream << maxFlow << "\n";

	this->result += stream.str();
}

void algorithms::FordFulkerson::showResults()
{
	std::cout << this->result;
}

int algorithms::FordFulkerson::fordFulkerson(int source, int target)
{
	int u, v;
	int vertices = this->graph.getVertices();

	Matrix residualGraph(vertices, VecInt(vertices));

	// init with capacities, or 0, if there aren't edges between vertices
	for (int u = 0; u < vertices; ++u)
	{
		for (int v = 0; v < vertices; ++v)
		{
			residualGraph[u][v] = this->graph(u, v) > 0 ? this->graph(u, v) : 0;
		}
	}

	VecInt parent(vertices);

	int maxFlow = 0;

	while (this->bfs(residualGraph, source, target, parent))
	{
		int pathFlow = std::numeric_limits<int>::max();
		for (v = target; v != source; v = parent[v])
		{
			u = parent[v];
			pathFlow = std::min(pathFlow, residualGraph[u][v]);
		}

		for (v = target; v != source; v = parent[v])
		{
			u = parent[v];
			residualGraph[u][v] -= pathFlow;
			residualGraph[v][u] += pathFlow;
		}

		maxFlow += pathFlow;
	}

	return maxFlow;
}

bool algorithms::FordFulkerson::bfs(const Matrix & residualGraph, int s, int t, VecInt & parent)
{
	int size = residualGraph[0].size();
	std::vector<bool> visited(size);

	std::queue<int> q;
	q.push(s);

	visited[s] = true;
	parent[s] = -1;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		for (int v = 0; v < size; ++v)
		{
			if (!visited[v] && residualGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return visited[t];
}

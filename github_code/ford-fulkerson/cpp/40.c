#include "stdafx.h"
#include "iostream"
#include "SelfStudyFunctions.h"
#include "list"
#include <limits>
#include <map>
#include <limits>
#include <string>

FordFulkerson::FordFulkerson() {}

FordFulkerson::FordFulkerson(int s) {
	this->graph.resize(s);
	this->size = s;
	for (int idx = 0; idx < size; idx++) {
		graph[idx].resize(s, 0);
	}
}

bool FordFulkerson::getBFSPath(int start, int end, std::vector<int> &parent, std::vector<std::vector<int>> rGraph) {
	std::list<int> queue;
	queue.push_back(start);
	std::vector<bool> visited(this->size, false);
	parent[start] = start;
	bool pathFound = false;
	while (queue.size() > 0 && !pathFound) {
		int node = queue.front();
		visited[node] = true;
		queue.pop_front();
		for (int i = 0; i < this->size; i++) {
			if (rGraph[node][i] > 0 && !visited[i]) {
				parent[i] = node;
				queue.push_back(i);
				if (i == end) {
					pathFound = true;
					break;
				}
			}
		}
	}
	return pathFound;
}

int FordFulkerson::getMaxFlow(int start, int end) {
	std::vector<std::vector<int>> rGraph = this->graph;
	std::vector<int> parent(this->size, -1);
	int maxFlow = 0;
	while (getBFSPath(start, end, parent, rGraph)) {
		int child = end;
		int par = -1;
		int minFlowForPath = std::numeric_limits<int>::max();
		//Loop to find min flow
		while (par != start) {
			par = parent[child];
			minFlowForPath = (rGraph[par][child] < minFlowForPath) ? rGraph[par][child] : minFlowForPath;
			child = par;
		}
		//Loop to update residual graph
		par = -1;
		child = end;
		while (par != start) {
			par = parent[child];
			rGraph[par][child] -= minFlowForPath;
			rGraph[child][par] += minFlowForPath;
			child = par;
		}
		maxFlow += minFlowForPath;
	}
	return maxFlow;
}

void FordFulkerson::testGetMaxFlow() {
	FordFulkerson ff(6);
	ff.graph[0][1] = 16;
	ff.graph[1][3] = 12;
	ff.graph[3][5] = 20;
	ff.graph[0][2] = 13; 
	ff.graph[2][4] = 14; 
	ff.graph[4][5] = 4; 
	ff.graph[1][2] = 10; 
	ff.graph[2][1] = 4;
	ff.graph[3][2] = 9;
	ff.graph[4][3] = 7;
	std::cout << "Max flow = " << ff.getMaxFlow(0, 5);
}
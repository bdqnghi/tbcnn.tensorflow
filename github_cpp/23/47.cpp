







#include "FordFulkersonAlgorithm.h"
#include <limits.h>
#include <algorithm>
#include <iostream>

FordFulkersonAlgorithm::FordFulkersonAlgorithm(int graph[VERTEX_COUNT][VERTEX_COUNT]) {
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			this->residualGraph[i][j] = graph[i][j];
		}
	}
	
	this->bfsAlgorithm = new BFSAlgorithm();
}

int FordFulkersonAlgorithm::maximumFlowForVertices(int source, int sink) {
	this->source = source;
	this->sink = sink;
	int maxFLow = 0;
	
	while (bfsAlgorithm->bfs(residualGraph, source, sink)) {
		
		int pathFlow = this->minimumFlowAlongBSFPath();
		
		this->updateValuesInResidualGraphByFlow(pathFlow);
		maxFLow += pathFlow;		
	}
	
	return maxFLow;
}

int FordFulkersonAlgorithm::minimumFlowAlongBSFPath() {
	int minimumFlow = INT_MAX;
	int parent;
	for (int vertex = sink; vertex != source; vertex = bfsAlgorithm->parent[vertex]) {
		parent = bfsAlgorithm->parent[vertex];
		minimumFlow = std::min(minimumFlow, residualGraph[parent][vertex]);
	}
	return minimumFlow;
}

void FordFulkersonAlgorithm::updateValuesInResidualGraphByFlow(int flow) {
	int parent;
	for (int vertex = sink; vertex != source; vertex = bfsAlgorithm->parent[vertex]) {
		parent = bfsAlgorithm->parent[vertex];
		residualGraph[parent][vertex] -= flow;
		residualGraph[vertex][parent] += flow;
	}
}
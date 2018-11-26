#ifndef _L_FORDFULKERSON_H
#define _L_FORDFULKERSON_H

#include "l.h"
#include "l_flownetwork.h"

class FordFulkerson{
	vector<bool> marked;
	vector<FlowEdge*> edgeTo;
	double max_flow;
	FlowNetwork* G;

	// use bfs to find the shortest augmenting path
	bool hasAugmentingPath(FlowNetwork*g, int s, int t) {
		
		for (int v = 0; v < g->V(); ++v) {
			marked[v] = false;
			edgeTo[v] = NULL;
		}
		queue<int> queue;

		marked[s] = true;
		queue.push(s);

		while (!queue.empty()) {
			int v = queue.front();
			queue.pop();

			for (FlowEdge* e : g->adj(v)) {
				int w = e->other(v);
				if (!marked[w] && e->residualCapacityTo(w) > 0) {
					edgeTo[w] = e;
					marked[w] = true;
					queue.push(w);
				}
			}
		}
		return marked[t];
	}

public:
	FordFulkerson(FlowNetwork* g, int s, int t): G(g) {
		max_flow = 0.0;
		for (int v = 0; v < g->V(); ++v) {
			marked.push_back(false);
			edgeTo.push_back(NULL);
		}

		while (hasAugmentingPath(g, s, t)) {
			double bottle = numeric_limits<double>::max();
			// find max residual flow
			for (int v = t; v != s; v = edgeTo[v]->other(v)) bottle = min(bottle, edgeTo[v]->residualCapacityTo(v));
			// add residual flow to each edge of augmenting path
			for (int v = t; v != s; v = edgeTo[v]->other(v)) edgeTo[v]->addResidualFlowTo(v, bottle);
			max_flow += bottle;
		}
	}
	~FordFulkerson() {

	}

	double maxFlow() {
		return max_flow;
	}

	vector<FlowEdge*> flowNetwork() {
		vector<FlowEdge*> result;
		for (int v = 0; v < G->V(); ++v) {
			for (auto e : G->adj(v))
				if (e->from() == v) result.push_back(e);
		}
		return result;
	}

};
#endif // !_L_FORDFULKERSON_H

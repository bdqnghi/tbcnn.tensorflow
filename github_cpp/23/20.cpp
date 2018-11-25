#include "FordFulkerson.h"

bool FordFulkerson::hasAugmentingPath(FlowNetwork& G, int s, int t){
	std::queue<int> q;
	edgeTo.clear();
	edgeTo.resize(G.getV());
	marked.clear();
	marked.resize(G.getV(),false);
	q.push(s);
	marked[s] = true;
	while(!q.empty() && !marked[t]){
		int v = q.front();
		q.pop();
		std::vector<FlowEdge>* adj = G.getAdj(v);
		for(int i = 0; i<(int)(adj->size());++i){
			int w = adj->at(i).other(v);
			if(adj->at(i).residualCapacityTo(w) > 0 && !marked[w]){
				edgeTo[w] = &(adj->at(i));
				marked[w] = true;
				q.push(w);
			}
		}
	}
	return marked[t];
}

FordFulkerson::FordFulkerson(FlowNetwork& G, int s, int t){
	value = 0.0;
	while(hasAugmentingPath(G,s,t)){
		double bottle = std::numeric_limits<double>::max();
		for(int v = t; v!=s; v= edgeTo[v]->other(v)){
			bottle = std::min(bottle,edgeTo[v]->residualCapacityTo(v));
		}
		for(int v = t; v!=s; v= edgeTo[v]->other(v)){
			edgeTo[v]->addResidualFlowTo(v, bottle);	
		}
		value += bottle;
	}
}
double FordFulkerson::getValue(){
	return value;
}

bool FordFulkerson::inCut(int vertex){
	return marked[vertex];
}

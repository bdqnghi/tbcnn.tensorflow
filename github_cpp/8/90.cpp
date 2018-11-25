#include "TopologicalSort.h"

TopologicalSort::TopologicalSort(Digraph &g) : 
	visited(g.V(), WHITE),
	hasCycle(false) {

	g.iter([&](int v) {
		if(this->hasCycle)
			return;
		if(this->getColor(v) == WHITE) {
			this->tsort(g, v);
			if(this->hasCycle)
				return;
		}
	});
}

TopologicalSort::~TopologicalSort() {

}

void TopologicalSort::tsort(Digraph &g, int v) {

	this->setColor(v, GREY);

	g.adj(v, [&](Edge &e) {
		
		if(this->hasCycle)
			return;

		int adjVertex = e.getDestination();
		
		if(this->getColor(adjVertex) == WHITE) {
		
			this->tsort(g, adjVertex);
		
		} else if(this->getColor(adjVertex) == GREY) {
		
			this->hasCycle = true;
			return;
		
		}
	});

	s.push_front(v);
	this->setColor(v, BLACK);

}

vector<int> TopologicalSort::getTopolicalSort() {
	vector<int> ts;
	std::copy(this->s.begin(), this->s.end(), std::back_inserter(ts));
	return ts;	
}

TopologicalSort::Color TopologicalSort::getColor(int v) {
	return this->visited[v];
}

void TopologicalSort::setColor(int v, Color color) {
	this->visited[v] = color;
}

bool TopologicalSort::getHasCycle() {
	return this->hasCycle;
}
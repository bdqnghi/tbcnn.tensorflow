#include "header.hpp"

using namespace std;

#define V 6

enum Status {not_visited, visiting, visited};

struct GraphVertex {
	int id;
	Status status = not_visited;
	struct Edge {
		GraphVertex *v;
		int weight;
	};
	GraphVertex(int i) : id(i) {}
	vector<Edge> edges;
};

void addEdge(GraphVertex *u, GraphVertex *v, int weight) {
	u->edges.emplace_back(GraphVertex::Edge{v, weight});
}

void createGraph(vector<GraphVertex*> *gptr) {
	vector<GraphVertex*> &Graph = *gptr;
	addEdge(Graph[5], Graph[2], 1);
	addEdge(Graph[5], Graph[0], 1);
	addEdge(Graph[4], Graph[0], 1);
	addEdge(Graph[4], Graph[1], 1);
	addEdge(Graph[2], Graph[3], 1);
	addEdge(Graph[3], Graph[1], 1);
}


void dfs(GraphVertex* u, stack<int> *order) {

	if (u->status==visiting) return;

	u->status = visiting;
	
	for (int i=0; i<u->edges.size(); ++i) {
		
		GraphVertex *v = u->edges[i].v;
		if (v->status != visited) {	// if the vertext is not visited
			dfs(v, order);
		}
	}

	// when all the adjacent vertices are visited
	order->emplace(u->id);	

	u->status = visited;
}

vector<int> topologicalSort(vector<GraphVertex*> Graph) {
	
	stack<int> order;	// store order to all the vertices
	vector<int> result;

	// start from each node to store the order
	for (int i=0; i<V; ++i) {
		if (Graph[i]->status == not_visited) {
			dfs(Graph[i], &order);
		}
	}

	while(!order.empty()) {
		result.emplace_back(order.top());
		order.pop();
	}

	return result;
}

int main() {

	vector<GraphVertex*> Graph(V);

	
	for (int i=0; i<V; ++i) {
		Graph[i] = new GraphVertex(i);
	}

	createGraph(&Graph);

	vector<int> order;
	order = topologicalSort(Graph);
	cout << "Topological Sorted Order : "<<endl;
	for (int i=0; i<V; ++i) {
		cout << order[i] << " --> ";
	}
	cout << endl;

	return 0;
}

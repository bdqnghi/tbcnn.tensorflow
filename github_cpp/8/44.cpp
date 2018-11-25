#include "topological_sort.h"
#include "log.h"

TopologicalSort::TopologicalSort(Graph *graph, graph_info& info)
	: m_graph(graph)
	, m_info(info)
{}

TopologicalSort::~TopologicalSort()
{

}

void TopologicalSort::sort()
{
	int source = m_info.source;
	int nodes = m_graph->getNodeCount();
	bool *visited = new bool [nodes];

	for (int i = 0; i < nodes; ++i) {
		visited[i] = false;
	}
	
    for (int i = 0; i < nodes; ++i) {
    	if (!visited[i]) {
        	sortUtil(i, visited);
    	}
    }

	delete [] visited;
}

void TopologicalSort::sortUtil(int vertice, bool *visited)
{
	visited[vertice] = true;
	Node *it = m_graph->getNode(vertice);
	for ( ; it != NULL; it = it->next) {
		if (!(visited[it->destination()])) {
			sortUtil(it->destination(), visited);
		}
	}
    m_stack.push(vertice);
}

void TopologicalSort::print()
{
	while (!m_stack.empty()) {
		LOG(m_stack.top());
		m_stack.pop();
	}
}

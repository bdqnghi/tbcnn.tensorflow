#include "TopologicalSort.h"

TopologicalSort::TopologicalSort(int vertices_amount) : vertex_condition_(vertices_amount, NOT_PROCESSED) {}

void TopologicalSort::StartProcessingVertex(int vertex) {
	vertex_condition_[vertex] = IN_PROCESSING;
}

void TopologicalSort::ProcessingEdge(int vertex, int incident_vertex) {
	try {
	    if (vertex_condition_[incident_vertex] == IN_PROCESSING) 
		throw std::logic_error("Error:: There is a circle");
    } catch (const std::exception& ex) {
        throw std::logic_error(std::string(ex.what()));
    }
}

void TopologicalSort::LeaveVertex(int vertex) {
	if (vertex_condition_[vertex] == PROCESSED) return;
	vertex_condition_[vertex] = PROCESSED;
	reversed_topological_order_.push_back(vertex);
}

std::vector<int> TopologicalSort::GetTopologicalOrder() const {
	std::vector<int> topological_order(reversed_topological_order_.begin(), reversed_topological_order_.end());
	reverse(topological_order.begin(), topological_order.end());
	return topological_order;
}

std::vector<int> GetTopologicallyOrderedVerties(const std::vector<Edge> &list_of_edges, int vertices_amount) {
    auto graph = MakeCompactGraph(list_of_edges, vertices_amount);
    TopologicalSort topological_sort(vertices_amount);
    DFS(*graph, topological_sort);

    return topological_sort.GetTopologicalOrder();
}



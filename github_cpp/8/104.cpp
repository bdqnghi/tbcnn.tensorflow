



#ifndef EXPLORING_CPP_2E_TOPOLOGICAL_SORT_H
#define EXPLORING_CPP_2E_TOPOLOGICAL_SORT_H

#include <deque>
#include <stdexcept>







template<class Graph, class Nodes>
void topsort_clean_graph(Graph& graph, Nodes& nodes) {
    for (auto iter(graph.begin()), end(graph.end()); iter != end;) {
        if (iter->second.empty()) {
            nodes.push_back(iter->first);
            graph.erase(iter++);            
        } else {
            ++iter;
        }
    }
};










template<class Graph, class OutIterator>
void topological_sort(Graph graph, OutIterator sorted) {
    std::deque<typename Graph::key_type> nodes{};
    
    topsort_clean_graph(graph, nodes);

    while (not nodes.empty()) {
        
        
        typename Graph::key_type n{nodes.front()};
        nodes.pop_front();
        *sorted = n;
        ++sorted;

        
        for (auto& node : graph) {
            node.second.erase(n);
        }
        
        topsort_clean_graph(graph,nodes);
    }

    if (not graph.empty()) {
        throw std::invalid_argument("Dependency graph contains cycles");
    }
};

#endif 

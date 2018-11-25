

#include "FordFulkerson.h"
#include <iostream>

FordFulkerson::FordFulkerson() {
}

FordFulkerson::FordFulkerson(const FordFulkerson& orig) {
}
int FordFulkerson::run(graph &grafo, int s, int t){
    
    BFS bfs;
    graph rGraph(grafo.get_size());
    for (int i = 0; i < grafo.get_size(); ++i) {
        for (int j = 0; j < grafo.get_size(); ++j) {
            
            if (grafo.has_edge(i,j)) {
                rGraph.add_edge(j, i);
                rGraph.add_edge(i, j);
                rGraph.set_capacity(i,j,grafo.get_capacity(i, j));
            }
        }
    }
   
  
    int parent[grafo.get_size()];
    int max_flow = 0;
    while(bfs.search(rGraph, s, t, parent)) {
        
        int flow = std::numeric_limits<int>::max();
        int u;
        
        for (int node = t; node != s; ) {
            u = parent[node];
            
            
            flow = std::min(flow, rGraph.get_capacity(u, node));
            node = u;
        }
        
        for (int node = t; node != s; ) {
            u = parent[node];
            rGraph.set_capacity(u, node, rGraph.get_capacity(u, node)-flow);
            rGraph.set_capacity(node, u, rGraph.get_capacity(node, u)+flow);
            if (grafo.has_edge(u, node))
                grafo.set_flux(u, node, grafo.get_flux(u, node)+flow);
            else
                grafo.set_flux(node, u, grafo.get_flux(node, u)-flow);
            node = u;
        }
       
    }
    int sat = 0;
    std::list<int> vecinos_s = grafo.get_neighbours(s);
    for (std::list<int>::iterator it = vecinos_s.begin(); it != vecinos_s.end(); it++) {
        max_flow += grafo.get_flux(s, (*it));
        sat += grafo.get_capacity(s, (*it));
    }
    
    
    if (max_flow == sat) {
        return max_flow;
    }
    else return -1;
}
FordFulkerson::~FordFulkerson() {
}


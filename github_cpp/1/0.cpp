#include "breadthfirstsearch.h"
#include <algorithm>
#include <iostream>
#include <omp.h>

std::vector<std::pair<int, int>> BreadthFirstSearch::MinimumSpanningTree(int vertices, const Graph& adjacencylist) {
    visited = std::vector<bool>(vertices, false);
    int startvertex = std::uniform_int_distribution<int>(0, vertices - 1)(generator);
    currentlevel.push_back(startvertex);
    visited[startvertex] = true;
    minimumspanningtree.clear();
    while (!currentlevel.empty()) {
        
        #pragma omp parallel for
        
        for (unsigned int i = 0; i < currentlevel.size(); i++) {
            auto vertex = currentlevel[i];
            for (unsigned int j = 0; j < adjacencylist[vertex].size(); j++) {
                const auto& edge = adjacencylist[vertex][j];
                int nextvertex = edge.first;
                if (nextvertex < 0 or visited[nextvertex]) continue;
                visited[nextvertex] = true;
                
                #pragma omp critical
                {
                    minimumspanningtree.push_back({vertex, nextvertex});
                    nextlevel.push_back(nextvertex);
                }
            }
        }
        currentlevel.clear();
        swap(currentlevel, nextlevel);
        shuffle(currentlevel.begin(), currentlevel.end(), generator);
    }
    return minimumspanningtree;
}

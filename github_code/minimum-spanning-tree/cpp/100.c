// This file is a part of Project project.
// Copyright (c) 2016 Aleksander Gajewski <adiog@brainfuck.pl>.

#ifndef PROJECT_MINIMUMSPANNINGTREE_H
#define PROJECT_MINIMUMSPANNINGTREE_H

#include <queue>
#include <utility>
#include "erange.h"
#include "common/GraphTypes.h"
#include "../common/WeightedGraph.h"
namespace algorithm {

class MinimumSpanningTree {
  public:
    MinimumSpanningTree(WeightedGraph weightedGraph) : graph(weightedGraph) {}

    void print() {
        std::priority_queue<WeightedEdge, std::vector<WeightedEdge>,
                            WeightedEdgeCompare>
            heap;
        std::vector<bool> visited(graph.size(), false);

        for (auto arrow : graph.getEdges()[0]) {
            heap.push(WeightedEdge{{0, arrow.first},
                                   arrow.second});
        }
        visited[0] = true;

        uint remainingEdges = graph.size() - 1;

        while (!heap.empty()) {
            WeightedEdge weightedEdge = heap.top();
            heap.pop();

            Edge currentEdge = weightedEdge.first;
            Vertex previousVertex = currentEdge.first;
            Vertex currentVertex = currentEdge.second;
            uint distanceToCurrent = weightedEdge.second;

            if (visited[currentVertex] && visited[previousVertex]) {
                continue;
            }

            std::cout << currentVertex+1 << " " << previousVertex+1 << " "
                      << distanceToCurrent << std::endl;

            if (--remainingEdges == 0) {
                break;
            };

            for (auto vertex : {currentVertex, previousVertex}) {
                if (!visited[vertex]) {
                    for (auto arrow : graph.getEdges()[vertex]) {
                        heap.push(WeightedEdge{{vertex, arrow.first},
                                               arrow.second});
                    }
                    visited[vertex] = true;

                }
            }
        }
    }

  private:
    WeightedGraph graph;
};
}

#endif  // PROJECT_MINIMUMSPANNINGTREE_H

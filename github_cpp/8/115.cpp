#ifndef TOPOLOGICALSORT_H
#define TOPOLOGICALSORT_H

#include "DirectedGraphAdjMatrix.h"

namespace ycg {

class TopologicalSort {
public:
    TopologicalSort(const DirectedGraphAdjMatrix* graph);
    ~TopologicalSort();
    void sort();
    int sequenceAt(int i) const;
    bool isDAG() const;
private:
    void dfs();
    void visit(int u);
private:
    enum COLOR {
        WHITE, BLACK, GRAY
    };
    const DirectedGraphAdjMatrix* graph;
    int *color;
    int *sequence, nsequence;
    bool acyclic;
};

inline bool TopologicalSort::isDAG() const {
    return acyclic;
}

inline int TopologicalSort::sequenceAt(int i) const {
    return sequence[i];
}

} 

#endif 

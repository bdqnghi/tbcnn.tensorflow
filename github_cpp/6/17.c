

#include "depthfirstsearch.h"

#include "graph/digraph.h"

#include "property/propertymap.h"

#ifdef DEBUG_DFS
#include <iostream>
#define PRINT_DEBUG(msg) std::cout << msg << std::endl;
#define IF_DEBUG(cmd) cmd;
#else
#define PRINT_DEBUG(msg)
#define IF_DEBUG(cmd)
#endif

namespace Algora {

void dfs(DiGraph *g, Vertex *v, int &depth, PropertyMap<DFSResult> &pm,
         PropertyMap<bool> &discovered, bool ignoreDirection);

DepthFirstSearch::DepthFirstSearch()
    : startVertex(0), maxDfsNumber(-1), ignoreArcDirections(false)
{

}

DepthFirstSearch::~DepthFirstSearch()
{

}

bool DepthFirstSearch::prepare()
{
    return PropertyComputingAlgorithm<int, DFSResult>::prepare()
            && (startVertex == 0 || diGraph->containsVertex(startVertex));
}

void DepthFirstSearch::run()
{
    if (startVertex == 0) {
        startVertex = diGraph->getAnyVertex();
    }

    int nextDepth = 0;
    PropertyMap<DFSResult> &pm = *propertyMap;
    PropertyMap<bool> discovered(false);
    dfs(diGraph, startVertex, nextDepth, pm, discovered, ignoreArcDirections);
    maxDfsNumber = nextDepth - 1;
}

int DepthFirstSearch::deliver()
{
    return maxDfsNumber + 1;
}

void dfs(DiGraph *g, Vertex *v, int &depth, PropertyMap<DFSResult> &pm,
         PropertyMap<bool> &discovered, bool ignoreDirection) {

    discovered[v] = true;
    DFSResult &cur = pm[v];
    cur.dfsNumber = depth;
    cur.lowNumber = depth;
    depth++;
    PRINT_DEBUG(v << " : low = " << cur.lowNumber)

    auto vm = [&](Vertex *v, Vertex *u) {
        PRINT_DEBUG("Considering child " << u)
        if (!discovered(u)) {
            pm[u] = DFSResult(v);
            PRINT_DEBUG("Set parent of " << u << " to " << pm(u).parent)
            dfs(g, u, depth, pm, discovered, ignoreDirection);
            if (pm(u).lowNumber < cur.lowNumber) {
                PRINT_DEBUG("Updating low from " << cur.lowNumber << " to " << pm(u).lowNumber)
                cur.lowNumber = pm(u).lowNumber;
                PRINT_DEBUG("Low is now " << pm(v).lowNumber)
            }
        } else if (cur.parent != u && pm(u).dfsNumber < cur.lowNumber) {
            PRINT_DEBUG("Updating low from " << cur.lowNumber << " to " << pm(u).dfsNumber)
            cur.lowNumber = pm(u).dfsNumber;
            PRINT_DEBUG("Low is now " << pm(v).lowNumber)
        }
    };
    g->mapOutgoingArcs(v, [&](Arc *a) { vm(v, a->getHead()); });
    if (ignoreDirection) {
        g->mapIncomingArcs(v, [&](Arc *a) { vm(v, a->getTail()); });
    }
}

}

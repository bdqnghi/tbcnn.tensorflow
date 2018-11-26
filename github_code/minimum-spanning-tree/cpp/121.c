// File: kruskal.h
// Desc: Implementation of Kruskal's minimum-spanning-tree algorithm
//

#include "graph.h"
#include "pq.h"
#include "uf.h"
#include <vector>
#include <memory>

using namespace std;

// Class to find minimum-spanning-tree (MST) on a
// weighted undirected graph.
//
class Mst {
public:
  // Construct an instance of MST
  //
  Mst(Graph *graph) {

    const unique_ptr<MinPq<Edge>> pq(new MinPq<Edge>());
    for (Edge e : graph->Edges()) {
      pq->Insert(e);
    }

    // For checking if min edge from pq is safe
    // to add to the MST.
    UnionFind uf(graph->V());

    //
    while ((!pq->IsEmpty()) &&
           (mst.size() < static_cast<unsigned int>(graph->V() - 1))) {
      Edge edge = pq->RemoveMin();
      int v = edge.v;
      int w = edge.w;

      // Check if adding edge into MST would create cycle.
      if (!uf.IsConnected(v, w)) {
        mst.push_back(edge);
        uf.Union(v, w);
        cost += edge.distance;
      }
    }
  }

  // Return sum of distance from all edges in the MST.
  //
  double Cost() { return cost; }

  // Return list of edges of the MST.
  vector<Edge> Edges() { return mst; }

private:
  // Total Mst cost. Sum of weights of all edges of the MST.
  //
  double cost;

  // List of edges of the MST.
  //
  vector<Edge> mst;
};

// Implement the output operator for the MST.
ostream &operator<<(ostream &os, Mst &mst) {
  for (Edge edge : mst.Edges()) {
    os << edge << endl;
  }
  os << "MST cost: " << mst.Cost() << endl;
  return os;
}

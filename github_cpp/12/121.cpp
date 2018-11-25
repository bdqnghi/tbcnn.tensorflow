



#include "graph.h"
#include "pq.h"
#include "uf.h"
#include <vector>
#include <memory>

using namespace std;




class Mst {
public:
  
  
  Mst(Graph *graph) {

    const unique_ptr<MinPq<Edge>> pq(new MinPq<Edge>());
    for (Edge e : graph->Edges()) {
      pq->Insert(e);
    }

    
    
    UnionFind uf(graph->V());

    
    while ((!pq->IsEmpty()) &&
           (mst.size() < static_cast<unsigned int>(graph->V() - 1))) {
      Edge edge = pq->RemoveMin();
      int v = edge.v;
      int w = edge.w;

      
      if (!uf.IsConnected(v, w)) {
        mst.push_back(edge);
        uf.Union(v, w);
        cost += edge.distance;
      }
    }
  }

  
  
  double Cost() { return cost; }

  
  vector<Edge> Edges() { return mst; }

private:
  
  
  double cost;

  
  
  vector<Edge> mst;
};


ostream &operator<<(ostream &os, Mst &mst) {
  for (Edge edge : mst.Edges()) {
    os << edge << endl;
  }
  os << "MST cost: " << mst.Cost() << endl;
  return os;
}

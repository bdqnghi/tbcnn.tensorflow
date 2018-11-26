#include <queue>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Graph.hpp>

namespace algo {
namespace mst {

struct Graph: public GenericGraph<WeightedEdge, false>
{
  Graph(size_t s): GenericGraph(s) {}

  int prim()
  {
    auto comp = [](const EdgeType* e1, const EdgeType* e2) {
      return e1->weight > e2->weight;
    };
    std::priority_queue<const EdgeType*, std::vector<const EdgeType*>, decltype(comp)> queue(comp);

    // Pick arbitrary vertice
    int s=0;
    for(const EdgeType& e: adjacency[s]) {
      queue.push(&e);
    }

    Flags inMst(size, false);
    inMst[s] = true;
    int mstSize = 1;
    int mstWeight = 0;
    while(mstSize < size && !queue.empty()) {
      const EdgeType* minEdge = queue.top();
      queue.pop();
      int v = minEdge->to;
      if(!inMst[v]) {
        inMst[v] = true;
        mstWeight += minEdge->weight;
        ++mstSize;
        for(const EdgeType& e: adjacency[v]) {
          queue.push(&e);
        }
      }
    }
    return mstWeight;
  }

  int kruskal()
  {
    struct Link { 
      int from; 
      int to; 
      int weight;
      bool operator<(const Link& rhs) const {
        return weight < rhs.weight;
      }
    };

    std::vector<Link> links;
    for(int u=0; u<size; ++u) {
      for(const EdgeType& e: adjacency[u]) {
        links.push_back({u, e.to, e.weight});
      }
    }
    std::sort(links.begin(), links.end());

    VerticeList component(size);
    for(int i=0; i<size; ++i) {
      component[i] = i;
    }
    int mstWeight = 0;
    for(const Link& link: links) {
      int c1 = component[link.from];
      int c2 = component[link.to];
      if(c1 != c2) {
        mstWeight += link.weight;
        for(int i=0; i<size; ++i) {
          if(component[i] == c2) {
            component[i] = c1;
          }
        }        
      }
    }
    return mstWeight;
  }
};

TEST(MinimumSpanningTree, Prim1) 
{
  Graph g(5);
  g.connect(0,2,2);
  g.connect(0,4,1);
  g.connect(1,3,4);
  g.connect(1,4,5);
  g.connect(2,4,4);
  g.connect(3,4,2);

  EXPECT_EQ(g.prim(), 9);
}

TEST(MinimumSpanningTree, Kruskal1)
{  
  Graph g(5);
  g.connect(0,2,2);
  g.connect(0,4,1);
  g.connect(1,3,4);
  g.connect(1,4,5);
  g.connect(2,4,4);
  g.connect(3,4,2);

  EXPECT_EQ(g.kruskal(), 9);
}

} // namespace mst
} // namespace algo
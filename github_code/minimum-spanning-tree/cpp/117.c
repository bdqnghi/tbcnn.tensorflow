#pragma once
#include "graph.h"
#include "template.h"
#include "../DataStructure/union_find.h"

template <typename T>
class Kruskal {
 private:
  int V;  // 頂点数
  Edges<T> edges;
  AdjList<T> minimumSpanningTree;

 public:
  explicit Kruskal(int n);
  void AddEdge(int from, int to, T cost);
  T Run();
  AdjList<T> GetMinimumSpanningTree();
};

template <typename T>
Kruskal<T>::Kruskal(int n) : V(n), minimumSpanningTree(n) {}

template <typename T>
void Kruskal<T>::AddEdge(int from, int to, T cost) {
  edges.push_back(Edge<T>(from, to, cost));
}

template <typename T>
T Kruskal<T>::Run() {
  sort(edges.begin(), edges.end(),
       [](const Edge<T> &a, const Edge<T> &b) { return a.cost < b.cost; });
  UnionFind tree(V);
  T total = 0;

  for (auto &e : edges) {
    if (!tree.Same(e.src, e.to)) {
      tree.Unite(e.src, e.to);
      total += e.cost;
      minimumSpanningTree[e.src].push_back(Edge<T>(e.to, e.cost));
      minimumSpanningTree[e.to].push_back(Edge<T>(e.src, e.cost));
    }
  }

  return total;
}

template <typename T>
AdjList<T> Kruskal<T>::GetMinimumSpanningTree() {
  return minimumSpanningTree;
}

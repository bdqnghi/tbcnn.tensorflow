#ifndef DWARF_GRAPH_BREADTH_FIRST_SEARCH_H_
#define DWARF_GRAPH_BREADTH_FIRST_SEARCH_H_

#include "dwarf.h"
#include "shared/list.h"
#include "shared/queue.h"

namespace dwarf {

template <typename TGraph>
class BreadthFirstSearch : public GraphSearch {
  public:
    BreadthFirstSearch(const TGraph& graph);
    virtual ~BreadthFirstSearch();
    virtual BOOL Find();
    virtual const List<int>& GetPath();
    virtual void Clear();

  private:
    typedef typename TGraph::NodeType Node;
    typedef typename TGraph::EdgeType Edge;
    typedef typename TGraph::EdgeIterator GraphEdgeIterator;
    enum { VISITED, UNVISITED, NO_PARENT_ASSIGNED };
    const TGraph& graph_;
    List<int>* visited_;
    List<int>* route_;
    List<int>* path_;
    Queue<const Edge*>* queue_;
    void Initialize();
    void Cleanup();
    void PushUnvisitedEdgesToQueue(int index);
};

template <typename TGraph>
inline BreadthFirstSearch<TGraph>::BreadthFirstSearch(const TGraph& graph)
    : graph_(graph) {
  Initialize();
}

template <typename TGraph>
inline BreadthFirstSearch<TGraph>::~BreadthFirstSearch() {
  Cleanup();
}

template <typename TGraph>
inline BOOL BreadthFirstSearch<TGraph>::Find() {
  if (graph_.HasNode(source()) && graph_.HasNode(target())) {
    const Edge* edge;
    visited_->Set(source(), VISITED);
    PushUnvisitedEdgesToQueue(source());
    while (!queue_->IsEmpty()) {
      edge = queue_->Pop();
      route_->Set(edge->to(), edge->from());
      if (edge->to() == target()) {
        set_found(true);
        break;
      } else {
        PushUnvisitedEdgesToQueue(edge->to());
      }
    }
    if (found()) {
      int index = target();
      path_->Add(index);
      while (index != source()) {
        index = route_->Get(index);
        path_->Insert(0, index);
      }
    }
  }
  return found();
}

template <typename TGraph>
inline const List<int>& BreadthFirstSearch<TGraph>::GetPath() {
  return *path_;
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::Clear() {
  GraphSearch::Clear();
  Cleanup();
  Initialize();
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::Initialize() {
  int nodeCount = graph_.NodeCount();
  visited_ = new List<int>(nodeCount);
  for (int i = 0; i < nodeCount; ++i) {
    visited_->Add(UNVISITED);
  }
  route_ = new List<int>(nodeCount);
  for (int i = 0; i < nodeCount; ++i) {
    route_->Add(NO_PARENT_ASSIGNED);
  }
  path_ = new List<int>(nodeCount);
  int edgeCount = graph_.EdgeCount();
  queue_ = new Queue<const Edge*>(edgeCount);
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::Cleanup() {
  delete visited_;
  delete route_;
  delete path_;
  delete queue_;
}

template <typename TGraph>
inline void BreadthFirstSearch<TGraph>::PushUnvisitedEdgesToQueue(int index) {
  GraphEdgeIterator iterator(graph_, index);
  while (iterator.HasNext()) {
    Edge& edge = iterator.Next();
    if (visited_->Get(edge.to()) == UNVISITED) {
      queue_->Push(&edge);
      visited_->Set(edge.to(), VISITED);
    }
  }
}

}

#endif
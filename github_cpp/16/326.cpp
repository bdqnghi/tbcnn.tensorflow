// Topological sort algorithm, assuming the graph has no circle.
//
// Run:
//  g++ -std=c++11 topological-sort.cpp
//  ./a.out

#include<iostream>
#include <set>
#include <stack>
#include <vector>
using namespace std;


class Graph {
public:
  explicit Graph(int size) {
    graph_.clear();
    graph_.resize(size);
  }

  bool AddEdge(int from, int to) {
    if (from < 0 || from >= graph_.size() ||
	to < 0 || to >= graph_.size()) {
      // invalid vertex.
      return false;
    }
    graph_[from].insert(to);
    return true;
  }

  void TopologicalSort() {
    // like DFS
    vector<bool> visited(graph_.size(), false);
    stack<int> s;
    for (int i = 0; i < graph_.size(); ++i) {
      Visit(i, &visited, &s);
    }

    while (!s.empty()) {
      cout << s.top() << endl;
      s.pop();
    }
  }

private:
  void Visit(int i, vector<bool>* visited, stack<int>* s) {
    if ((*visited)[i]) {
      return;
    }
    (*visited)[i] = true;
    
    for (int v : graph_[i]) {
      Visit(v, visited, s);
    }

    s->push(i);
  }

  vector<set<int> > graph_;
};

int main() {
  // A graph like below:
  //
  //     5    1
  //    /  \ / |
  //   2    0  |
  //    \  /   |
  //     3     |
  //      \    |
  //       --- 4

  Graph g(6);
  g.AddEdge(5, 2);
  g.AddEdge(5, 0);
  g.AddEdge(1, 0);
  g.AddEdge(1, 4);
  g.AddEdge(2, 3);
  g.AddEdge(3, 4);
  g.AddEdge(0, 3);

  g.TopologicalSort();
  
  return 0;
}


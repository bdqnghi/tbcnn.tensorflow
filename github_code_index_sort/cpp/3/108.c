// The algorithm below is DFS with an extra stack. 
// So time complexity is same as DFS which is O(V+E).
// 该算法如何判断图是否可拓扑排序？
#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph {
public:
  Graph(int V);
  void addEdge(int v, int w);
  void topologicalSort();
private:
  int V;
  list<int> *adj;
  void topologicalSort(int v, bool visited[], stack<int>& s);
};

Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
}

void Graph::topologicalSort() {
  stack<int> s;

  bool *visited = new bool[V];
  for (int i = 0; i < V; ++i) visited[i] = false;

  for (int i = 0; i < V; ++i)
    if (!visited[i])
      topologicalSort(i, visited, s);

  while (!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
}

void Graph::topologicalSort(int v, bool visited[], stack<int>& s) {
  visited[v] = true;

  for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
    if (!visited[*it])
      topologicalSort(*it, visited, s);

  s.push(v);
}

int main()
{
  Graph g(6);
  g.addEdge(5, 0);
  g.addEdge(5, 2);
  g.addEdge(4, 0);
  g.addEdge(4, 1);
  g.addEdge(2, 3);
  g.addEdge(3, 1);
  g.topologicalSort();
  return 0;
}

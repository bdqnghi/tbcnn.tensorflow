
#include<iostream>
#include <list>
#include <stack>
#include <queue>
#include <vector>
using namespace std;
 

class Graph
{
    int V;    
 
    
    list<int> *adj;
 
    
    
    
    void topologicalSortUtil(int v, bool visited[], queue<int> &Stack);
    void helper(int v, vector<bool>& visited, queue<int> &ss);
public:
    Graph(int V);   
 
     
    void addEdge(int v, int w);
 
    
    void topologicalSort();
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); 
}



void Graph::helper(int i, vector<bool>& visited, queue<int>& ss) {
  visited[i] = true;
  list<int>::iterator it;
  for (it = adj[i].begin(); it != adj[i].end(); it++) {
    if (!visited[*it])
      helper(*it, visited, ss);
  }
  ss.push(i);
}

void Graph::topologicalSort() {
  
  queue<int> ss;
  vector<bool> visited(V, false);
  
  for (int i = 0; i != V; i++) {
    if (!visited[i]) {
      helper(i, visited, ss);
    }
  }

  while (!ss.empty()) {
    
    cout << ss.front() << " ";
    ss.pop();
  }
}


 

int main()
{
    
    Graph g(6);

    g.addEdge(2, 3);
    g.addEdge(0, 3);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(1, 2);

    cout << "Following is a Topological Sort of the given graph \n";
    g.topologicalSort();
    cout << endl;
 
    return 0;
}

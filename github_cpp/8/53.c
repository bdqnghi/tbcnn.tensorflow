


#include<iostream>
#include <list>
#include <stack>

class Graph
{
private:
    
    int V;    
 
    
    std::list<int> *adj;
 
    
    void topologicalSortUtil(int, bool[], std::stack<int>&);

public:
    Graph(int);
    ~Graph();
 
     
    void addEdge(int, int);
 
    
    void topologicalSort();
};
 
Graph::Graph(int x)
{
    this->V = x;
    adj = new std::list<int>[x];
}

Graph::~Graph(){
    delete[] adj;
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}
 

void Graph::topologicalSortUtil(int v, bool visited[], std::stack<int> &Stack)
{
    
    visited[v] = true;
 
    
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){
        if (!visited[*i]){
            topologicalSortUtil(*i, visited, Stack);
        }
    }
 
    
    Stack.push(v);
}
 


void Graph::topologicalSort()
{
    std::stack<int> Stack;
 
    
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++){
        visited[i] = false;
    }
 
    
    
    for (int i = 0; i < V; i++){
        if (visited[i] == false){
            topologicalSortUtil(i, visited, Stack);
        }
    }
 
    
    while (!Stack.empty())
    {
        std::cout << Stack.top() << "\n";
        Stack.pop();
    }
}
 

int main()
{
    
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
 
    std::cout << "Following is a Topological Sort of the given graph" << "\n";
    g.topologicalSort();
 
    return 0;
}
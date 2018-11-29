// A C++ program to print topological sorting of a DAG
// http://www.geeksforgeeks.org/topological-sorting/

#include<iostream>
#include <list>
#include <stack>

class Graph
{
private:
    // No. of vertices'
    int V;    
 
    // Pointer to an array containing adjacency listsList
    std::list<int> *adj;
 
    // A function used by topologicalSort
    void topologicalSortUtil(int, bool[], std::stack<int>&);

public:
    Graph(int);
    ~Graph();
 
     // function to add an edge to graph
    void addEdge(int, int);
 
    // prints a Topological Sort of the complete graph
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
 
// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[], std::stack<int> &Stack)
{
    // Mark the current node as visited.
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){
        if (!visited[*i]){
            topologicalSortUtil(*i, visited, Stack);
        }
    }
 
    // Push current vertex to stack which stores result
    Stack.push(v);
}
 
// The function to do Topological Sort. It uses recursive 
// topologicalSortUtil()
void Graph::topologicalSort()
{
    std::stack<int> Stack;
 
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++){
        visited[i] = false;
    }
 
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++){
        if (visited[i] == false){
            topologicalSortUtil(i, visited, Stack);
        }
    }
 
    // Print contents of stack
    while (!Stack.empty())
    {
        std::cout << Stack.top() << "\n";
        Stack.pop();
    }
}
 
// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram
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
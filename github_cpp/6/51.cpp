

#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;


class Graph {
    
    vector<list<int> > edges;

    
    void dfsRecursiveUtil(int vertex, vector<bool>& visited);
public:

    
    Graph(int vertices) : edges(vertices) {};

    
    void addEdge(int startVertex, int endVertex);

    
    void dfsRecursive(int vertex);

    
    void dfsIterative(int vertex);
};

int main(void) {
    Graph g(10);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Recursive DFS starting from vertex 2: ";
    g.dfsRecursive(2);

    cout << "\nIterative DFS starting from vertex 2: ";
    g.dfsIterative(2);

    return 0;
}

void Graph::addEdge(int startVertex, int endVertex) {
    edges[startVertex].push_back(endVertex);
}


void Graph::dfsRecursive(int vertex) {
    vector<bool> visited(edges.size(), false);

    dfsRecursiveUtil(vertex, visited);
}


void Graph::dfsRecursiveUtil(int vertex, vector<bool>& visited) {
    visited[vertex] = true;
    cout << vertex << ' ';

    for(list<int>::iterator ix = edges[vertex].begin(); ix != edges[vertex].end(); ++ix)
        if(!visited[*ix])
            dfsRecursiveUtil(*ix, visited);
}


void Graph::dfsIterative(int vertex) {
    vector<bool> visited(edges.size(), false);
    stack<int> Stack;
    Stack.push(vertex);

    while(!Stack.empty()) {
        int currVertex = Stack.top();
        Stack.pop();

        if(!visited[currVertex]) {
            cout << currVertex << ' ';
            visited[currVertex] = true;
        }

        for(list<int>::iterator ix = edges[currVertex].begin(); ix != edges[currVertex].end(); ++ix)
            if(!visited[*ix])
                Stack.push(*ix);
    }

    cout << endl;
}

/* Depth First Search (DFS) traversal in graph */

#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;

/* Graph is declared as a class */
class Graph {
    /* Edges are stored as vector of list */
    vector<list<int> > edges;

    /* dfsRecursiveUtil takes in the vertex and the visited map, to check if the
    given vertex has been visited previously or not */
    void dfsRecursiveUtil(int vertex, vector<bool>& visited);
public:

    /* Initialize the graph with the given number of vertices */
    Graph(int vertices) : edges(vertices) {};

    /* Procedure to fill in the edge values */
    void addEdge(int startVertex, int endVertex);

    /* A recursive approach for DFS */
    void dfsRecursive(int vertex);

    /* A iterative approach to DFS */
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

/* The below function initializes a vector of boolean value to keep
 * track of visited vertices. It then invokes the dfsRecursiveUtil
 * method to print the path.
 */
void Graph::dfsRecursive(int vertex) {
    vector<bool> visited(edges.size(), false);

    dfsRecursiveUtil(vertex, visited);
}

/* This method takes in the current visiting vertex and a boolean map of
 * vertices indicating if they have been visited or not. For each vertices
 * attached to the current visiting vertex, if it has not been visited,
 * it marks as visited.
 */
void Graph::dfsRecursiveUtil(int vertex, vector<bool>& visited) {
    visited[vertex] = true;
    cout << vertex << ' ';

    for(list<int>::iterator ix = edges[vertex].begin(); ix != edges[vertex].end(); ++ix)
        if(!visited[*ix])
            dfsRecursiveUtil(*ix, visited);
}

/* This method takes in the current vertex and employs a stack */
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

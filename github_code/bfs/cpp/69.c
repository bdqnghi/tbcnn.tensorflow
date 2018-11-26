/* Breadth First Search (BFS) in a graph */

#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

/* Class declaration for Graphs */
class Graph {
    vector<list<int> > edges;
public:
    Graph(int vertices) : edges(vertices) {};
    inline void addEdge(int startVertex, int endVertex);
    void bfs(int vertex);
};

int main(void) {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "BFS starting at 2: ";
    g.bfs(2);

    return 0;
}

inline void Graph::addEdge(int startVertex, int endVertex) {
    edges[startVertex].push_back(endVertex);
}

/* BFS Implementation */
void Graph::bfs(int vertex) {
    vector<bool> visited(edges.size(), false);
    visited[vertex] = true;

    queue<int> Q;
    Q.push(vertex);

    while(!Q.empty()) {
        int currVertex = Q.front();
        Q.pop();
        cout << currVertex << ' ';

        for(list<int>::iterator ix = edges[currVertex].begin(); ix != edges[currVertex].end(); ++ix)
            if(!visited[*ix]) {
                visited[*ix] = true;
                Q.push(*ix);
            }
    }

    cout << endl;
}

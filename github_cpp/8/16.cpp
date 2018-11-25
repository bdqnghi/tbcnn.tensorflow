



#include <iostream>
#include <vector>
#include <list>

using namespace std;

typedef vector<vector<int>> graph;

void visit(int v, const graph &g, vector<int> &visited, list<int> &order) {
    visited[v] = true;
    for(int w : g[v]) {
        if(!visited[w]) visit(w, g, visited, order);
    }
    order.push_front(v);
}

list<int> topologicalSort(const graph &g) {
    vector<int> visited(g.size(), false);
    list<int> order;

    for(int v = 0; v < g.size(); v++) {
        if(!visited[v]) visit(v, g, visited, order);
    }

    return order;
}

int main() {
    
    
    
    
    
    
    
    
    
    graph g {{1, 7},
             {2, 7},
             {5},
             {2, 4},
             {5},
             {},
             {7},
             {},
             {}};

    list<int> order = topologicalSort(g);

    cout << "Topological sort order: ";
    for(int v : order) cout << v << " ";
    cout << endl;

    return 0;
}
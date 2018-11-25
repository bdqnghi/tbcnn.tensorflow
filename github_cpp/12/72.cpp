



#include <stdio.h>
#include <limits.h>
#include <vector>
#include <iostream>

class Graph{
private:
    int V;
    std::vector<std::vector<int> > graph;

    int min_key(std::vector<int>, std::vector<bool>);

public:
    Graph(int);
    void add_edge(int, int, int);
    void delete_edge(int, int);
    void print_graph();

    void prim_mst();
    void printMST(std::vector<int>);
};


Graph::Graph(int i) {
    this->V = i;
    std::vector<int> temp (i, 0);
    for(int k=0; k<i; k++)
        graph.push_back(temp);

    for(int k=0; k<i; k++)
        graph[k][k] = 0;
}

void Graph::print_graph() {
    for(int i = 0; i<V; i++) {
        for (int k = 0; k < V; k++)
            std::cout << graph[i][k] << " ";
    std::cout << std::endl;
    }
}

void Graph::add_edge(int v1, int v2, int weight) {
    if (v1 == v2)
        return;

    graph[v1][v2] = weight;
    graph[v2][v1] = weight;
}

void Graph::delete_edge(int v1, int v2) {
    if (v1 == v2)
        return;

    graph[v1][v2] = 0;
    graph[v2][v1] = 0;
}


int Graph::min_key(std::vector<int> key, std::vector<bool> mstSet) {
    
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] <= min)
            min = key[v], min_index = v;

    return min_index;
}

void Graph::printMST(std::vector<int> parent) {
    printf("Edge   Weight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}

void Graph::prim_mst() {
    
    std::vector<int> parent(V);

    
    std::vector<int> key(V);

    
    std::vector<bool> mstSet(V);

    
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    
    
    key[0] = 0;

    
    parent[0] = -1;

    
    for (int count = 0; count < V-1; count++)
    {
        
        
        int u = min_key(key, mstSet);

        
        mstSet[u] = true;

        
        
        
        for (int v = 0; v < V; v++)

            
            
            
            if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
                parent[v]  = u, key[v] = graph[u][v];
    }

    
    printMST(parent);
}

int main()
{
    Graph g(5);

    g.add_edge(0,1,2);
    g.add_edge(0,3,6);
    g.add_edge(1,2,3);
    g.add_edge(1,3,8);
    g.add_edge(1,4,5);
    g.add_edge(2,4,7);
    g.add_edge(3,4,9);

    g.print_graph();
    g.prim_mst();

    return 0;
}
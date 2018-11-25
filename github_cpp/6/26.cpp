#include<iostream>
#include<list>

class Graph
{
    int V;
    list<int> *adj;
    int time ;
public:

    Graph::Graph(int V);
    void addEdge(int u, int v);
    void dfs();
    void dfs_visit(int u);
};

Grap::Graph(int V)
{
    this->V = V;
    this->time = 0;
    adj = new list<int>[V];
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void dfs()
{
    int color[V];
    int parent[V];
    for(int i = 0; i<V ; i++)
    {
        color[i] = 0;
        parent[i] = NULL;
    }

    for

}

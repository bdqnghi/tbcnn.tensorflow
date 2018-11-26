#include <iostream>
#include <vector>
#include <list>

using namespace std;

#define BLACK true
#define WHITE false

class Graph
{
    vector< list<int> > adj;
    vector<bool> color;
    vector<int> parent;
    int type;
    int V;
    // 0 -> directed
    // 1 -> undirected
    int find(int p, vector<int> &components);
public:

    Graph(int n, int t);
    void addEdge(int v, int w);
    void DFS_visit(int u);
    void DFS();
    vector<int> DFS_components();
    void display();

};

Graph::Graph(int n, int t = 0)
{
    adj.resize(n);
    color.resize(n);
    parent.resize(n);
    type = t;
    V = n;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    if (type)
        adj[w].push_back(v);
}

void Graph::DFS_visit(int u)
{
    color[u] = BLACK;
    for (list<int>::iterator v = adj[u].begin(); v != adj[u].end(); v++)
    {
        if (color[*v] == WHITE)
        {
            parent[*v] = u;
            DFS_visit(*v);
        }
    }
}

void Graph::DFS()
{
    for(int i = 0; i < V; i++)
    {
        parent[i] = i;
        color[i] = WHITE;
    }

    for (int u = 0; u < V; u++)
    {
        if (color[u] == WHITE)
        {
            DFS_visit(u);
        }
    }
}

void Graph::display()
{
    cout << "\n\n GRAPH";
    for (int u = 0; u < V; u++)
    {
        cout << "\n " << u << " -> ";
        for (list<int>::iterator v = adj[u].begin(); v != adj[u].end(); v++)
        {
            cout << *v << " -> ";
        }
        cout << "/";
    }
}

vector<int> Graph::DFS_components()
{
    vector<int> components = parent;
    for (int i = 0; i < V; i++)
    {
        find(i, components);
    }
    return components;
}

int Graph::find(int p, vector<int> &components)
{
    int root = p;
    while (root != components[root])
        root = components[root];
    while (p != root)
    {
        int newp = components[p];
        components[p] = root;
        p = newp;
    }
    return root;
}

int main()
{
    int n, t, type;
    cin >> n >> t >> type;
    Graph G(n,type);
    while (t--)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        G.addEdge(u,v);
    }
    G.display();
    G.DFS();
    vector<int> components = G.DFS_components();
    cout << "\n\n DFS components ==> ";
    for (int i = 0; i < n; i++)
    {
        cout << components[i] << " ";
    }
    cout << "\n\n";
    return 0;
}
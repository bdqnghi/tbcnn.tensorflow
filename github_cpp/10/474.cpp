#include<iostream>
#include<list>
using namespace std;

class Graph
{
    int V;
    list<int> *adj;
    void DFSutill(int v,bool *visited);
public:
    Graph(int V);
    void addNode(int v,int e);
    void DFS(int v);
};

Graph :: Graph(int V)
{
    this->V=V;
    adj=new list<int>[V];
}
 void Graph::addNode(int v,int e)
 {
     adj[v].push_back(e);
 }
void Graph :: DFS(int v)
{
    bool *visited=new bool[v];
    for(int i=0;i<v;i++)
    {
        visited[i]=false;
    }

    DFSutill(v,visited);
}

void Graph::DFSutill(int v,bool *visited)
{
    visited[v]=true;
    cout<<v<<" " ;

    list<int> :: iterator i;
    for(i=adj[v].begin();i!=adj[v].end();i++)
    {
        if(!visited[*i])
        {
            visited[*i]=true;
            DFSutill(*i,visited);
        }
    }
}

int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addNode(0, 1);
    g.addNode(0, 2);
    g.addNode(1, 2);
    g.addNode(2, 0);
    g.addNode(2, 3);
    g.addNode(3, 3);

    cout << "Following is Depth First Traversal (starting from vertex 2) \n";
    g.DFS(2);

    return 0;
}

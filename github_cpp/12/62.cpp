#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <vector>
static bool  compareEdgeWeight(Edge e1, Edge e2)
{
    return e1.weight < e2.weight;
}

Graph::~Graph()
{
    for (int i = 0; i < this->vertexs; i++)
    {
        delete[] graph[i];
    }
    delete[] graph;
}

void Graph::genEedges()
{

    int k = 0;
    for (int i = 0; i<vertexs; i++)
    {
        for (int j = 0; j<vertexs; j++)
        {
            if (this->graph[i][j] > 0)
            {
                edges.push_back(Edge{ i,j,graph[i][j] });
                k++;
            }
        }
    }
}

void Graph::createGraph()   
{

    std::cout << "Input the number of vertex: ";
    std::cin >> this->vertexs;

    graph = new int*[this->vertexs];

    for (int i = 0; i < this->vertexs; i++)
    {
        graph[i] = new int[this->vertexs];
    }
    for (int i = 0; i < this->vertexs; i++)
    {
        for (int j = 0; j < this->vertexs; j++)
        {
            graph[i][j] = 0;
        }
    }
    std::cout << "\nInput the number of edges: ";
    std::cin >> this->nrOfEdge;
    for (int i = 0; i < vertexs; i++)
    {
        std::cout << "\nInput the " << i + 1 << " row of adjacency matrix with weight: ";
        for (int j = 0; j < vertexs; j++)
        {
            std::cin >> this->graph[i][j];
        }
    }
    this->genEedges();
    this->init();
}

int Graph::init()     
{
    std::sort(edges.begin(), edges.end(), compareEdgeWeight);
    this->unionFind = UnionFind();
    std::vector<UnionFind::Node*> nodes;
    for (int i = 0; i < this->vertexs; i++)
    {
        UnionFind::Node* n = new UnionFind::Node();
        n->data = i;
        n->rank = 0;

        unionFind.AddNode(n);
    }

    return 0;
}

void Graph::FindSpanningTree()
{
    init();
    for (auto it = this->edges.begin(); it != this->edges.end(); it++)
        
    {
        UnionFind::Node* u = unionFind.Nodes[it->s_v];
        UnionFind::Node* v = unionFind.Nodes[it->e_v];

        if (unionFind.Find(u) != unionFind.Find(v))     
        {
            Edge e = Edge{ it->s_v, it->s_v, it->weight };
            MinimumSpanningTree.push_back(e);
            unionFind.Union(u, v);             
        }

        if (unionFind.ClusterCount == 1) 
            break;
    }
}


long Graph::GetMinimumCost()  
{
    long totalCost = 0;

    for (auto it = MinimumSpanningTree.cbegin(); it != MinimumSpanningTree.cend(); it++)
    {
        totalCost += it->weight;
    }

    return totalCost;
}

vector<Edge> Graph::covMinimunSpanningTree()
{
    return this->MinimumSpanningTree;
}
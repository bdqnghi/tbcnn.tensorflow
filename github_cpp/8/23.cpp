




#include <iostream>
#include <stdexcept>
using namespace std;

#include "algraph.h"
#include "../ch03/sqqueue.h"





template <typename V, typename E, int M>
void TopologicalSort(const ALGraph<V, E, M> &G, int P[])
{
    
    int indegree[M] = {0}; 
    for (int v = 0; v < G.vexnum; v++)
        for (auto p = G.vexs[v].firstarc; p; p = p->nextarc)
            indegree[p->adjvex]++;

    
    SqQueue<int, M> Q;
    InitQueue(Q);
    
    for (int v = 0; v < G.vexnum; v++)
        if (indegree[v] == 0)
            EnQueue(Q, v);
    
    int count = 0;
    while (!QueueEmpty(Q))
    {
        
        auto v = DeQueue(Q);
        P[count++] = v;
        
        for (auto p = G.vexs[v].firstarc; p; p = p->nextarc)
        {
            int w = p->adjvex;
            indegree[w]--;
            if (indegree[w] == 0)
                EnQueue(Q, w);
        }
    }

    
    if (count < G.vexnum)
        throw logic_error("Graph has a cycle");
}

int main()
{
    
    
    ALGraph<char, int> G;
    
    InitGraph(G);
    
    auto a = AddVertex(G, 'A');
    auto b = AddVertex(G, 'B');
    auto c = AddVertex(G, 'C');
    auto d = AddVertex(G, 'D');
    auto e = AddVertex(G, 'E');
    
    AddEdge(G, a, b);
    AddEdge(G, a, c);
    AddEdge(G, b, d);
    AddEdge(G, b, e);
    AddEdge(G, c, d);
    AddEdge(G, c, e);
    AddEdge(G, d, e);

    
    int P[20];
    TopologicalSort(G, P);
    for (int i = 0; i < G.vexnum; i++)
        cout << G.vexs[P[i]].data;
    cout << endl;

    return 0;
}
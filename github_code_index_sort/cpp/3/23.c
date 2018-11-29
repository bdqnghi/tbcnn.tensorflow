///////////////////////////////////////
/// file: topological.cpp
/// Topological sort
///////////////////////////////////////

#include <iostream>
#include <stdexcept>
using namespace std;

#include "algraph.h"
#include "../ch03/sqqueue.h"

///
/// 拓扑排序
/// 结果保存在数组 P 中
///
template <typename V, typename E, int M>
void TopologicalSort(const ALGraph<V, E, M> &G, int P[])
{
    // 计算各个顶点的入度
    int indegree[M] = {0}; // 各顶点的入度，初始化为 0
    for (int v = 0; v < G.vexnum; v++)
        for (auto p = G.vexs[v].firstarc; p; p = p->nextarc)
            indegree[p->adjvex]++;

    // 利用队列进行拓扑排序
    SqQueue<int, M> Q;
    InitQueue(Q);
    //   所有入度为零的顶点入队列
    for (int v = 0; v < G.vexnum; v++)
        if (indegree[v] == 0)
            EnQueue(Q, v);
    //   逐个输出入度为零的顶点
    int count = 0;
    while (!QueueEmpty(Q))
    {
        // 出队列，保存结果
        auto v = DeQueue(Q);
        P[count++] = v;
        // 减少 v 的邻接点的入度，入度为 0 的顶点入队列
        for (auto p = G.vexs[v].firstarc; p; p = p->nextarc)
        {
            int w = p->adjvex;
            indegree[w]--;
            if (indegree[w] == 0)
                EnQueue(Q, w);
        }
    }

    // 若图中存在回路，则抛出异常
    if (count < G.vexnum)
        throw logic_error("Graph has a cycle");
}

int main()
{
    // 建立有向无环图
    // G = ({A,B,C,D,E}, {AB,AC,BD,BE,CD,CE,DE})
    ALGraph<char, int> G;
    // 初始化
    InitGraph(G);
    // 添加顶点
    auto a = AddVertex(G, 'A');
    auto b = AddVertex(G, 'B');
    auto c = AddVertex(G, 'C');
    auto d = AddVertex(G, 'D');
    auto e = AddVertex(G, 'E');
    // 添加边
    AddEdge(G, a, b);
    AddEdge(G, a, c);
    AddEdge(G, b, d);
    AddEdge(G, b, e);
    AddEdge(G, c, d);
    AddEdge(G, c, e);
    AddEdge(G, d, e);

    // 拓扑排序
    int P[20];
    TopologicalSort(G, P);
    for (int i = 0; i < G.vexnum; i++)
        cout << G.vexs[P[i]].data;
    cout << endl;

    return 0;
}
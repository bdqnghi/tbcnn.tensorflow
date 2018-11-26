/*! Author：qwchen
 *! Date  : 2016-11-6
 * 使用深度优先搜索判断单点连通性
 * 思想：使用深度优先搜索从图的顶点s出发，能被访问到的节点都是可达的节点
 */

#include <iostream>
#include <vector>
#include "../../DataStruct/Graph/Graph.h"

using namespace std;

class DepthFirstSearch{
public:
    DepthFirstSearch(Graph &G, int s);
    void dfs(Graph &G, int v); // 深度优先搜索
    bool marked(int v);        // 返回true，当从节点s到节点v可达时
    int count();               // 返回从节点s出发可达的结点数

private:
    vector<bool> marked_;      // 用来标记访问过的结点
    int count_;                // 计数，代表访问过的结点数
};

DepthFirstSearch::DepthFirstSearch(Graph &G, int s){
    marked_.assign(G.V(), false);
    count_ = 0;
    dfs(G, s);
}

void DepthFirstSearch::dfs(Graph &G, int v){
    marked_[v] = true;
    count_++;
    for (int w: G.adj(v)){
        if (!marked_[w]) dfs(G, w);
    }
}

bool DepthFirstSearch::marked(int v){
    return marked_[v];
}

int DepthFirstSearch::count(){
    return count_;
}

void testDepthFirstSearch(){
    int numberOfV = 6;
    Graph G(numberOfV);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 5);
    G.addEdge(1, 2);
    G.addEdge(2, 3);
    G.addEdge(2, 4);
    G.addEdge(3, 4);
    G.addEdge(3, 5);
    G.output();
    DepthFirstSearch dfs(G, 0);
    cout << "0 have " << dfs.count() << " reachable vertexes." << endl;
    for (int v = 0; v < numberOfV; v++){
        if (dfs.marked(v)){
            cout << "Reachable(0, " << v << ")" << endl;
        } else {
            cout << "UnReachable(0, " << v << ")" << endl;
        }
    }
}

int main(){
    testDepthFirstSearch();
    return 0;
}

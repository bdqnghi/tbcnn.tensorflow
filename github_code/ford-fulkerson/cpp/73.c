//
// Created by yuanh on 2018/6/10.
//

#ifndef ALGORITHMS_FORD_FULKERSON_H
#ifndef INF_INT
#define INF_INT 0x3fffffff
#endif

#include <algorithm>
#include <vector>
#include <cstring>

using std::min;
using std::vector;
using std::memset;

typedef struct ford_fulkerson_edge {
    int to;//终点
    int capacity;//容量
    int reverse;//反向边
} ff_edge;

/**
 * 通过dfs寻找増广路
 * @param G 图
 * @param used 是否被访问过
 * @param s 起点
 * @param t 终点
 * @param flow 流量
 * @return 増广路流量
 */
int dfs(int s, int t, int flow, vector<ff_edge> *G, bool *used) {
    if (s == t) {
        return flow;
    }
    used[s] = true;
    for (int i = 0; i < G[s].size(); ++i) {
        ff_edge &e = G[s][i];
        if (!used[e.to] && e.capacity > 0) {
            int d = dfs(e.to, t, min(flow, e.capacity), G, used);
            if (d > 0) {
                e.capacity -= d;
                G[e.to][e.reverse].capacity += d;
                return d;
            }
        }
    }
    return 0;
}

/**
 * ford_fulkerson最大流算法,注意G最后会被改变
 * @param G 图
 * @param V 边的数量
 * @param s 起点
 * @param t 终点
 * @return 最大流
 */
int ford_fulkerson(vector<ff_edge> *G, int V, int s, int t) {
    auto *used = new bool[V];
    int flow = 0;
    while (true) {
        memset(used, 0, sizeof(*used) * V);
        int f = dfs(s, t, INF_INT, G, used);
        if (f == 0) {
            delete[] used;
            return flow;
        }
        flow += f;
    }
}

void add_edge(vector<ff_edge> *G, int from, int to, int capacity) {
    G[from].emplace_back((ff_edge) {to, capacity, (int) G[to].size()});
    G[to].emplace_back((ff_edge) {from, 0, (int) G[from].size() - 1});
}

#define ALGORITHMS_FORD_FULKERSON_H

#endif //ALGORITHMS_FORD_FULKERSON_H

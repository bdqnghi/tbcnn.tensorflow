#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename CompT>
void scan(vector<pair<int, int> > *g, bool *marked,
          priority_queue<pair<int, int>, vector<pair<int, int> >, CompT> &pq, int s) {
    marked[s] = true;
    for (auto const &edge : g[s]) {
        if (!marked[edge.second]) {
            pq.push(edge);
        }
    }
}

template<typename CompT>
int prim(vector<pair<int, int> > *g, bool *marked,
         priority_queue<pair<int, int>, vector<pair<int, int> >, CompT> &pq, int s) {
    int result = 0;
    scan(g, marked, pq, s);
    while (!pq.empty()) {
        const pair<int, int> edge = pq.top();
        pq.pop();
        if (!marked[edge.second]) {
            result += edge.first;
            scan(g, marked, pq, edge.second);
        }
    }
    return result;
}

int spanningTree(vector<pair<int, int> > g[], int MAX) {
    auto cmp = [](pair<int, int> l, pair<int, int> r) { return l.first > r.first; };

    priority_queue<pair<int, int>, vector<pair<int, int> >, decltype(cmp)> pq(cmp);
    bool marked[MAX + 1];
    for (int i = 1; i <= MAX; i++) {
        marked[i] = false;
    }

    for (int i = 1; i <= MAX; i++) {
        if (!g[i].empty()) {
            return prim(g, marked, pq, i);
        }
    }

}


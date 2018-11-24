/*Ford fulkerson - DFS */
/*
7 9
1 7
1 2 2
1 3 7
2 4 3
3 4 5
3 5 5
4 6 4
5 6 1
5 7 2
6 7 6
ans 7
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct network_edge {
    int to, capacity, flow, residual_idx;
    network_edge() {}
    network_edge(int t, int c, int f, int r) {
        to = t;
        capacity = c;
        flow = f;
        residual_idx = r;
    }
};

int src, sink;
bool chk[101];
vector<network_edge> adj[101];

int find_path(int cur, int addible_flow) {
    if(cur == sink) return addible_flow;
    chk[cur] = true;

    for(int i = 0; i < adj[cur].size(); i++) {
        network_edge& edge = adj[cur][i];
        if(chk[edge.to] || edge.capacity - edge.flow == 0) continue;

        int added = find_path(edge.to, min(addible_flow, edge.capacity - edge.flow));
        if(added) {
            edge.flow += added;
            adj[edge.to][edge.residual_idx].flow -= added;
            return added;
        }
    }

    return 0;
}

int main() {
    int v, e;
    scanf("%d %d", &v, &e);
    scanf("%d %d", &src, &sink);

    for(int i = 0; i < e; i++) {
        int from, to, capacity;
        scanf("%d %d %d", &from, &to, &capacity);
        adj[from].push_back(network_edge(to, capacity, 0, adj[to].size()));
        adj[to].push_back(network_edge(from, 0, 0, adj[from].size() - 1));
        cout <<" asds" <<adj[to].size() << adj[from].size()-1 <<endl;
    
    }

    int ans = 0, added_flow;
    while(added_flow = find_path(src, 101)) {
        ans += added_flow;
        for(int i = 1; i <= v; i++) {
            chk[i] = 0;
        }
    }

    printf("%d\n", ans);
    return 0;
}

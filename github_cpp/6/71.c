#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

int dfs_c, dfs_root, root_c;
vector<vi> adj;
vi dfs_low, dfs_num, dfs_p;
vector<bool> articulation_vertex;

void articulation(int u) {
    dfs_low[u] = dfs_num[u] = dfs_c++;

    for (int v : adj[u]) {
        if (!dfs_num[v]) {
            dfs_p[v] = u;

            if (u == dfs_root) ++root_c;
            
            articulation(v);
            
            if (u != dfs_root && dfs_low[v] >= dfs_num[u])
                articulation_vertex[u] = true;
                
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_p[u])
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

int main() {
    int N;
    int u, v;
    while (cin >> N, N) {
        string s;

        dfs_c = 1;
        adj.assign(N + 1, vi());
        dfs_low.assign(N + 1, 0);
        dfs_num.assign(N + 1, 0);
        dfs_p.assign(N + 1, 0);
        articulation_vertex.assign(N + 1, false);

        while (getline(cin, s), s != "0") {
            stringstream ss(s);
            ss >> u;
            while (ss >> v) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }


        for (int i = 0; i <= N; i++) {
            if (!dfs_num[i]) {
                dfs_root = i, root_c = 0, articulation(i);
                articulation_vertex[dfs_root] = (root_c > 1);
            }
        }
        cout << count(articulation_vertex.begin(), articulation_vertex.end(), true) << endl;
    }

    return 0;
}
/*
 * Author: fatboy_cw
 * Created Time:  2014/4/26 10:32:36
 * File Name: B.cpp
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
const int maxint = -1u>>1;
template <class T> bool get_max(T& a, const T &b) {return b > a? a = b, 1: 0;}
template <class T> bool get_min(T& a, const T &b) {return b < a? a = b, 1: 0;}
const int maxn = 100 + 5;
int t, n, ca, f[maxn], s[maxn];
vector<int> adj[maxn], tree[maxn];
bool vis[maxn];

void buildTree(int u) {
    vis[u] = true;
    for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if(vis[v]) continue;
        tree[u].push_back(v);
        buildTree(v);
    }
}

void dfs(int u) {
    if(tree[u].size() == 0) {
        f[u] = 0;
        s[u] = 1;
        return;
    }
    vector<int> sons;
    for(int i = 0; i < tree[u].size(); i++) {
        int v = tree[u][i];
        dfs(v);
        s[u] += s[v];
        sons.push_back(f[v] - s[v]);
    }
    s[u]++;
    int tot = s[u] - 1;
    int ret = tot;
    if(sons.size() >= 2) {
        sort(sons.begin(), sons.end());
        get_min(ret, tot + sons[0] + sons[1]);
    }
    f[u] = ret;
}


int getRoot(int root) {
    for(int i = 0; i < n; i++) tree[i].clear();
    memset(vis, false, sizeof(vis));
    buildTree(root);
    memset(s, 0, sizeof(s));
    memset(f, -1, sizeof(f));
    dfs(root);
    return f[root];
}

int main() {
    freopen("B1.in", "r", stdin);
    freopen("B1.out", "w", stdout);
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) adj[i].clear();
        for(int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int res = maxint;
        for(int i = 0; i < n; i++) {
            get_min(res, getRoot(i));
        }
        printf("Case #%d: %d\n", ++ca, res);
    }
    return 0;
}


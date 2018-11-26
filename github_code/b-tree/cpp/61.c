/**
 * jerrym
 * B.cpp
 */

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <bitset>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef long long int lli;
typedef pair<int, int> pii;

int gInt () {
    int i;
    scanf("%d", &i);
    return i;
}

lli gLong () {
    lli i;
    scanf("%lld", &i);
    return i;
}

double gDouble () {
    double i;
    scanf("%lf", &i);
    return i;
}

void quit () {
    fflush(stdout);
    exit(0);
}

int n;

vector<int> edges[1005];
int minRem[1005];
int treeSize[1005];

int rec (int cur, int par) {
    int ans = minRem[cur] = 9999;
    int numChildren = 0;
    treeSize[cur] = 1;
    for (int i = 0; i < edges[cur].size(); ++i) {
        if (edges[cur][i] != par) {
  //          fprintf(stderr, "  %d %d\n", cur, edges[cur][i]);
            rec(edges[cur][i], cur);
            ++numChildren;
            treeSize[cur] += treeSize[edges[cur][i]];
        }
    }
    ans = min(ans, treeSize[cur] - 1);
    if (numChildren > 1) {
        for (int i = 0; i < edges[cur].size(); ++i) {
            int nodea = edges[cur][i];
            if (nodea == par) continue;
            for (int j = 0; j < i; ++j) {
                int nodeb = edges[cur][j];
                if (nodeb == par) continue;
                int cost = minRem[nodea] + minRem[nodeb] + treeSize[cur] - 1 - treeSize[nodea] - treeSize[nodeb];
                ans = min(ans, cost);
            }
        }
    }
    //fprintf(stderr, "%d %d %d\n", cur, ans, treeSize[cur]);
    return minRem[cur] = ans;
}

bool in[1005];

int goodRoot (int cur, int par) {
    if (!in[cur]) {
        return 0;
    }
    int numChildren = 0;
    int size = 1;
    for (int i = 0; i < edges[cur].size(); ++i) {
        int node = edges[cur][i];
        if (node == par) continue;
        int childSize = goodRoot(node, cur);
        size += childSize;
        if (childSize)
            ++numChildren;
    }
    if (numChildren != 2 && numChildren != 0) return 0;
    return size;
}

bool goodTree (int rem) {
    for (int i = 0; i < n; ++i) {
        if (goodRoot(i, -1) == n - rem) return true;
    }
    return false;
}

int rec2 (int cur, int rem) {
    if (cur == n) {
        return goodTree(rem) ? 0 : 1000;
    }
    in[cur] = true;
    int norem = rec2(cur + 1, rem);
    in[cur] = false;
    return min(norem, rec2(cur + 1, rem + 1) + 1);
}

void solve (int nC) {
    printf("Case #%d: ", nC + 1);
    n = gInt();
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 1; i < n; ++i) {
        int from = gInt() - 1, to = gInt() - 1;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    int ans = 9999;
    for (int i = 0; i < n; ++i) {
//    for (int i = 0; i < 1; ++i) {
        ans = min(ans, rec(i, -1));
//        fprintf(stderr, "%d %d\n", i, rec(i, -1));
    }
    printf("%d\n", ans);
}

int main (int argc, char ** argv) {
    int nC = gInt();
    for (int i = 0; i < nC; ++i) {
        solve(i);
    }
    quit();
}

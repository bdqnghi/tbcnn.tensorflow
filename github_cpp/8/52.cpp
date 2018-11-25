

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <stdio.h>
#include <queue>
#include <set>
#include <list>
#include <cmath>
#include <assert.h>
#include <bitset>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iomanip> 

#define mp make_pair
#define pb push_back
#define x first
#define y second
#define print(arr) for (auto it = arr.begin(); it != arr.end(); ++it) cout << *it << " "; cout << "\n";

typedef long long int ll;
typedef long double ld;
typedef std::pair <int, int> ii;
typedef std::vector <int> vi;
typedef std::vector <ll> vll;
const int INF = int(1e9);
const ll INF64 = ll(1e18);
const ld EPS = 1e-9, PI = 3.1415926535897932384626433832795;

using namespace std;

int main() {
    int N, M, a, b;
    bitset <20> viz;
    scanf("%d %d", &N, &M);
    vector <vi> graph(N+1);
    vi topo, indegree(N+1, 0);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        graph[a].pb(b);
        indegree[b] += 1;
    }
    queue <int> Q;
    for (int u = 1; u <= N; u++) {
        if (indegree[u] == 0) {
            Q.push(u);
            viz[u] = true;
        }
    }
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        topo.pb(u);
        for (int v : graph[u]) {
            if (!viz[v]) {
                indegree[v]--;
                viz[v] = true;
                Q.push(v);
            }
        }
    }
    print(topo);
}
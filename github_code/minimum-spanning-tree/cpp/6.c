#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'
#define MAX (int)1e4 + 5

// Referencias:
// https://www.hackerearth.com/notes/minimum-spanning-tree/

using namespace std;

vector <bool> visited(MAX, false);
vector < vector<pair<long long, int> > > G(MAX);

long long prim(int u) {
  priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
  long long ans = 0;
  pq.push(make_pair(0, u));

  while (!pq.empty()) {
    pair<long long, int> curr = pq.top();
    pq.pop();
    if (visited[curr.second]) continue;

    ans += curr.first;
    visited[curr.second] = true;

    for (int i = 0; i < G[curr.second].size(); i++) {
      int tmp = G[curr.second][i].second;
      if (!visited[tmp])
        pq.push(G[curr.second][i]);
    }
  }
  return ans;
}

int main() {
  fast;
  int nodes, edges, a, b;
  long long w;
  cin >> nodes >> edges;

  for (int i = 0; i < edges; i++) {
    cin >> a >> b >> w;
    a--;b--;
    G[a].push_back(make_pair(w, b));
    G[b].push_back(make_pair(w, a));
  }

  cout << prim(0) << endl;
  return 0;
}



#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int N;
int cost[10001];
int dep[10001];
vector<int> e[10001];
int sofar[10001];

int solve() {
  queue<int> q;
  int result = 0;
  for (int i=1; i<= N; i++) {
    if (dep[i] == 0) q.push(i);
  }
  while(!q.empty()) {
    int cur = q.front(); q.pop();
    if (e[cur].size() == 0) { 
      result = max(result, sofar[cur] + cost[cur]);
      continue;
    }
    for (int i=0; i<e[cur].size(); i++) {
      int &v = e[cur][i];
      sofar[v] = max(sofar[v], sofar[cur] + cost[cur]);
      dep[v]--;
      if (dep[v] == 0) q.push(v);
    }
  }
  return result;
}

int main () {
  scanf("%d", &N);
  for (int i=1; i<=N; i++) {
    scanf("%d%d", &cost[i], &dep[i]);
    for(int j=0; j<dep[i]; j++) {
      int v;
      scanf("%d", &v);
      e[v].push_back(i);
    }
  }
  cout << solve() << endl;
}
//topological sort sample
#include <bits/stdc++.h>
using namespace std;
//ios_base::sync_with_stdio(false);
#ifdef CORLEONE
  #define d(b) cerr<< #b << " " << b << endl
  #else
  #define d(b)
#endif

int n;
const int MAXN = 100;
vector<int> g[MAXN];
bool used[MAXN];
vector<int> ans;

void dfs(int v){
  used[v]=true;
  for(int i=0;i<g[v].size();i++){
    int to = g[v][i];
    if(!used[to]) dfs(to);
  }
  ans.push_back(v);
}

 void topological_sort(){
  for(int i=0; i<n; i++)
    used[i] = false;
  ans.clear();
  for(int i=0; i<n;i++){
    if(!used[i]) dfs(i);
  }
  reverse(ans.begin(), ans.end());
 }


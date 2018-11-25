#include <iostream>
#include <vector>
#include <stack>
using namespace std;
vector < vector < int > > g;

vector <int> used;
stack <int> ans;
int n, m;
int x, y;

void dfs(int v)
{
  used[v] = 1;
  for(size_t i = 0; i < g[v].size(); i++)
  {
    int u = g[v][i];
    if(!used[u])
      dfs(u);
  }
  ans.push(v);
}

void topologicalSort()
{
  for(size_t i = 0; i < n; i++)
    if(!used[i]) dfs(i);

  while(!ans.empty())
  {
    cout << ans.top() << endl;
    ans.pop();
  }
}

int main()
{
  cin >> n >> m;
  used.assign(n, 0);
  g.resize(n);

  for(int i = 0; i < m; i++)
  {
      cin >> x >> y;
      g[x - 1].push_back(y - 1);
  }

  topologicalSort();
  return 0;
}

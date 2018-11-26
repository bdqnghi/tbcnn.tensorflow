/*
 * CLRS Ch 26 The Ford-Fulkerson method
 * Using DFS
 */

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct edge {
   size_t v;
   int cap;
   size_t revIdx;
};

/*
 * Ford-Fulkerson
 * Complexity: O(|F||E|) ... can be bad
 * see Edmonds-Karps algorthm
 */

class Solution {

   vector<vector<edge>> g; // residue network
   vector<bool> visited;   // for dfs
   size_t s, t;            // source and sink

   // find augmenting path update residue network
   // on the fly
   int findAugmentingPath(size_t u, int delta) {
      if (u == t) {
         return delta;
      }

      cout << "at " << u << " with delta:" << delta << endl;

      for (auto& e : g[u]) {
         cout << "looking at:" << e.v << " with cap:" << e.cap << endl;
         if (visited[e.v] || e.cap == 0) continue;
         visited[e.v] = true;
         int ret = findAugmentingPath(e.v, min(delta, e.cap));
         if (ret > 0) {
            e.cap -= ret;
            g[e.v][e.revIdx].cap += ret;
            return ret;
         }
      }

      return 0;
   }

public:
   int maxFlow(const vector<vector<edge>> &g_, size_t s_, size_t t_) {
      s = s_;
      t = t_;

      // construct the residue with flow = 0
      g.resize(g_.size());
      visited.resize(g.size(), false);
      for (size_t i = 0; i < g_.size(); ++i) {
         for(size_t eIdx = 0; eIdx < g_[i].size(); ++eIdx) {
            auto &e = g_[i][eIdx];
            g[i].push_back(e);
            g[i].back().revIdx = g[e.v].size();
            g[e.v].push_back({i, 0, g[i].size() - 1});
         }
      }

      int flow = 0;
      while (true) {
         fill(visited.begin(), visited.end(), false);
         visited[s] = true;
         int d = findAugmentingPath(s, numeric_limits<int>::max());
         if (d == 0) return flow;
         cout << "get d:"<< d << endl;
         flow += d;
      }
   }
};

int main() {
   Solution s;
   cout << s.maxFlow(
         vector<vector<edge>> {
         {
           {1, 10, 0}, {2, 2, 0},
         },
         {
           {2, 6, 0}, {3, 6, 0},
         },
         {
           {4, 5, 0}
         },
         {
           {2, 3, 0}, {4, 8, 0}
         },
         {
         },
         },
         0, 4) << endl;
}

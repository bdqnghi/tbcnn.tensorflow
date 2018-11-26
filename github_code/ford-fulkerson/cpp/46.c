/*
  For personal practice. 
  Original source code comes from ISBN 978-89-6626-054-6
*/

/*
  Ford-Fulkerson's algorithm for Max Flow
  Edmund-Karp implementation of Ford-Fulkerson
*/
#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;


const int INF = 987654321;
const int MAX_V = 1000;

// capacity[i][j] = capacity from i to j 
// flow[i][j] = current flow from i to j
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int V; // # of vertices

int NF(int source, int sink)
{
  memset(flow, 0, sizeof(flow));
  int totalFlow = 0;

  while(true) {
    // find an augment path using BFS
    vector<int> parent(MAX_V, -1);
    queue<int> q;
    parent[source] = source;
    q.push(source);
    while(!q.empty() && parent[sink] == -1) {
      int here = q.front(); q.pop();
      for(int there=0;there<V;++there) {
        if(capacity[here][there] - flow[here][there] > 0 &&
           parent[there] == -1) {
          q.push(there);
          parent[there] = here;
        }
      }
      // exit if no augement path.
      if(parent[sink] == -1) break;

      // determine augement flow amount
      int amount =INF;
      for(int p=sink;p != source;p = parent[p]) {
        amount = min(capacity[parent[p]][p]-flow[parent[p]][p]
                     , amount );        
      }
      // add new flow
      for(int p=sink;p != source;p = parent[p]) {
        flow[parent[p]][p] += amount;
        flow[p][parent[p]] -= amount;
      }
      totalFlow += amount;
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  
  return 0;
}

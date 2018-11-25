


#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;


const int INF = 987654321;
const int MAX_V = 1000;



int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int V; 

int NF(int source, int sink)
{
  memset(flow, 0, sizeof(flow));
  int totalFlow = 0;

  while(true) {
    
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
      
      if(parent[sink] == -1) break;

      
      int amount =INF;
      for(int p=sink;p != source;p = parent[p]) {
        amount = min(capacity[parent[p]][p]-flow[parent[p]][p]
                     , amount );        
      }
      
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

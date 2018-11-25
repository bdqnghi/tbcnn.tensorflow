#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>
#include <set>
#include <deque>
#include <bitset>
#include <list>
#include <complex>
#include <assert.h>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;

static const double EPS = 1e-12;

static const int tx[] = {+0,+1,+0,-1};
static const int ty[] = {-1,+0,+1,+0};

class Edge{
public:
  int _to;
  int _capacity;
  int _reverse;
  Edge(int to,int capacity,int reverse) :
    _to(to), _capacity(capacity), _reverse(reverse) {}
};

class FordFulkerson {
private:
  int _n;
  bool *_used;
  vector<Edge>* _edges;
  void fill_used(){
    fill(_used,_used + _n ,false);
  }
public:
  ~FordFulkerson(){
    delete[] _edges;
    delete[] _used;
  }

  FordFulkerson(int n){
    _n = n;
    _edges = new vector<Edge>[n];
    _used = new bool[n]();
  }

  void add_edge(int from,int to,int capacity){
    _edges[from].push_back(Edge(to,capacity,_edges[to].size()));
    _edges[to].push_back(Edge(from,0,_edges[from].size()-1));
  }

  int dfs(int current,int sink,int flow){
    if(current == sink) return flow;
    _used[current] = true;
    for(int i=0;i<_edges[current].size();i++){
      Edge& e = _edges[current][i];
      int to = e._to;
      if(_used[to] || e._capacity <= 0) continue;

      int d = dfs(to,sink,min(flow,e._capacity));
      if(d <= 0) continue;
      
      e._capacity -= d;
      _edges[to][e._reverse]._capacity += d;
      return d;
    }
    
    return 0;
  }

  int compute_max_flow(int source,int sink){
    int res = 0;
    while(true){
      fill_used();
      int tmp = dfs(source,sink,INF);
      if(tmp == 0) break;
      res += tmp;
    }
    return res;
  }
};

int main(){
  int num_of_domes;
  int num_of_pipelines;
  int day_limit;

  while(~scanf("%d %d %d",&num_of_domes,&num_of_pipelines,&day_limit)){
    int dp[101][101];
    memset(dp,0x3f,sizeof(dp));

    for(int pipeline_i = 0; pipeline_i < num_of_pipelines; pipeline_i++){
      int from,to,cost;
      scanf("%d %d %d",&from,&to,&cost);
      from--; to--;
      dp[from][to] = cost;
      dp[to][from] = cost;
    }

    for(int from = 0; from < num_of_domes; from++){
      int to = from;
      dp[from][to] = 0;
    }

    for(int mid = 0; mid < num_of_domes; mid++){
      for(int from = 0; from < num_of_domes; from++){
	for(int to = 0; to < num_of_domes; to++){
	  dp[from][to] = min(dp[from][to], dp[from][mid] + dp[mid][to]);
	}
      }
    }

    FordFulkerson ford_fulkerson(num_of_domes * 2 + 2);
    for(int dome_i = 0; dome_i < num_of_domes; dome_i++){
      int current_reside_citizens;
      scanf("%d",&current_reside_citizens);
      ford_fulkerson.add_edge(num_of_domes * 2,dome_i,current_reside_citizens);
    }

    for(int dome_i = 0; dome_i < num_of_domes; dome_i++){
      int capacity;
      scanf("%d",&capacity);
      ford_fulkerson.add_edge(num_of_domes + dome_i,num_of_domes * 2 + 1,capacity);
    }

    for(int from = 0; from < num_of_domes; from++){
      for(int to = 0; to < num_of_domes; to++){
	if(dp[from][to] < day_limit){
	  ford_fulkerson.add_edge(from,num_of_domes + to,INF);
	}
      }
    }
    printf("%d\n",ford_fulkerson.compute_max_flow(num_of_domes * 2,num_of_domes * 2 + 1));
  }
}

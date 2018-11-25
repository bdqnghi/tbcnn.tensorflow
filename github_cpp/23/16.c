
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#define X first
#define Y second
#define LI long long
#define MP make_pair
#define PB push_back
#define SZ size()
#define SQ(a) ((a)*(a))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

using namespace std;

#define N 10000 

typedef pair<int,int> P;

int n;          
vector<P> A[N]; 
vector<P> C[N]; 





template<typename T> int bb(T t, vector<T> &v) {
  int a = 0, b = v.SZ;
  while (a < b) {
    int m = (a + b)/2;
    if (v[m] < t) a = m+1;  else b = m;
  }
  return a;
}



int BFS(int s, int t) {
  int k = 0, l[N], q[N], r[N], v[N];
  for (int i = 0; i < n; i++) v[i] = -1;
  v[s] = 1000000000;  l[k++] = s;
  for (int i = 0; i < k; i++)
    for (int j = 0; j < (int)C[l[i]].size(); j++) {
      P p = C[l[i]][j];
      if (p.Y > 0 && v[p.X] < 0) {
	l[k++] = p.X;
	v[p.X] = MIN(v[l[i]], p.Y);
	q[p.X] = l[i];  r[p.X] = j;
      }
    }
  if (v[t] < 0) return 0;
  for (int a = t; a != s; a = q[a]) {
    C[q[a]][r[a]].Y -= v[t];
    C[a][bb(MP(q[a], 0), C[a])].Y += v[t];
  }
  return v[t];
}

int maxflow(int s, int t) { 
  for (int i = 0; i < n; i++)
    sort(A[i].begin(), A[i].end());
  for (int i = 0; i < n; i++)
    for (int j = 0; j < (int)A[i].SZ; j++) {
      int x = A[i][j].X, y = bb(MP(i, 0), A[x]);
      if (y == A[x].SZ || i < A[x][y].X)
	C[x].PB(MP(i, 0));
    }
  for (int i = 0; i < n; i++) {
    C[i].insert(C[i].end(), A[i].begin(), A[i].end());
    sort(C[i].begin(), C[i].end());
  }
  int sum = 0;
  for (int inc = 1; inc > 0; sum += inc = BFS(s, t));
  return sum;
}

int main() {
  n = 6;
  A[0].PB(MP(1, 3)); 
  A[0].PB(MP(2, 3)); 
  A[1].PB(MP(2, 2)); 
  A[1].PB(MP(3, 3)); 
  A[2].PB(MP(4, 2)); 
  A[3].PB(MP(4, 4)); 
  A[3].PB(MP(5, 2)); 
  A[4].PB(MP(5, 3)); 
  cout << maxflow(0, 5) << "\n";      
}

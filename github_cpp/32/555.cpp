#include<bits/stdc++.h>
#define REP(i,a,b) for (int i = a; i < b; i++)
#define pb push_back
#define all(X) X.begin(), X.end()
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
vi pset(1000);
void initSet(int N){
  REP(i,0, N)
    pset[i] = i;
}
int findSet(int i){
  return (pset[i] == i) ? i : pset[i] = findSet(pset[i]);
}
void unionSet(int i, int j){
  pset[findSet(i)] = findSet(j);
}
int isSameSet(int i, int j){
  return findSet(i) == findSet(j);
}
/* XXX Kruskal implements on edgelist*/
vector< pair<int, ii> > EdgeList;
int Kruskal(){
  sort(all(EdgeList));
  int mst = 0;
  initSet(N);
  REP(i,0,EdgeList.size()){
    pair<int, ii> front = EdgeList[i];
    if (!isSameSet(front.second.first, front.second.second)){
      unionSet(front.second.first, front.second.second)
      mst += front.first;
    }
  }
  return mst;
}
int N, a, b, w;
int main(){
  while(scanf("%d\n", &N) == 1){
    EdgeList.clear();
    REP(i, 0 , N-1){
      scanf("%d %d %d\n",&a, &b, &w);
      EdgeList.pb(make_pair(w, ii(a-1, b-1)));
    }
    printf("%d\n", Kruskal());
  }
  return 0;
}

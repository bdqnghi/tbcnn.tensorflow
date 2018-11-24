/**  @Author: Thiago Henrique Neves Coelho
  *  Date: 09/25/2017
  *  Algorithm: Bellman-Ford Algorithm for minimun paths
  */

#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

typedef long long int ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

const int N = 10;
const int INF = 0x3f3f3f3f;

ll dist[N];
vii v[N];

ll bellman(int o, int dest, int n){
	memset(dist,INF,sizeof(ll)*(n+1));
	dist[o] = 0;
	for(int k = 0; k < n; k++){
		for(int i = 0; i < n; i++){
			for(int j=0; j < v[i].size(); j++){
				dist[v[i][j].f] = min(dist[v[i][j].f], dist[i] + v[i][j].s);
			}
		}
	}
	return dist[dest];
}

int main(void){

	return 0;
}

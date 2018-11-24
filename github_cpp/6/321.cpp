#include <bits/stdc++.h>
using namespace std;

const int MAX_INT = std::numeric_limits<int>::max();
const int MIN_INT = std::numeric_limits<int>::min();
const int INF = 1000000000;
const int NEG_INF = -1000000000;

#define max(a,b)(a>b?a:b)
#define min(a,b)(a<b?a:b)
#define MEM(arr,val)memset(arr,val, sizeof arr)
#define PI acos(0)*2.0
#define eps 1.0e-9
#define are_equal(a,b)fabs(a-b)<eps
#define LS(b)(b& (-b)) // Least significant bit
#define DEG_to_RAD(a)((a*PI)/180.0) // convert to radians

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,char> ic;
typedef pair<long,char> lc;
typedef vector<int> vi;
typedef vector<ii> vii;

int gcd(int a,int b){return b == 0 ? a : gcd(b,a%b);}
int lcm(int a,int b){return a*(b/gcd(a,b));}

int V, s;
vector<vii> adj;
int main(){
	vi dist(V, INF);
	dist[s] = 0;
	for (int i = 0; i < V-1; i++)	// relax all E edges V-1 times
		for (int u = 0; u < V; u++)	// these two loops = O(E), overall O(VE)
			for (int j = 0; j < (int)adj[u].size(); j++){
				ii v = adj[u][j];	// record SP spanning here if needed
				dist[v.first] = min(dist[v.first], dist[u] + v.second);	// relax
			}

	// after running the O(VE) Bellman Ford's algorithm shown above
	bool hasNegativeCycle = false;
	for (int u = 0; u < V; u++)	// one more pass to check
		for (int j = 0; j < (int)adj[u].size(); j++){
			ii v = adj[u][j];
			if (dist[v.first] > dist[u] + v.second)	// if this is still possible
				hasNegativeCycle = true;	// then negative cycle exists
		}
}

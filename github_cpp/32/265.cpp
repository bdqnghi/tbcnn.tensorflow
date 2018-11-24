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

class UnionFind{
private: vi p, rank;
public:
	UnionFind(int N){
		rank.assign(N, 0);
		p.assign(N, 0);
		for(int i = 0; i < N; i++)
			p[i] = i;
	}
	int findSet(int i){
		return (p[i] == i) ? i : (p[i] = findSet(p[i]));
	}
	bool isSameSet(int i, int j){
		return findSet(i) == findSet(j);
	}
	void unionSet(int i, int j){
		if (!isSameSet(i, j)){
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) p[y] = x;
			else {
				p[x] = y;
				if (rank[x] == rank[y]) rank[y]++;
			}
		}
	}
};

// inside int main()
int main(){
	int V;
	int u, v, w, E;
	vector< pair<int, ii> > EdgeList;
	for (int i = 0; i < E; i++){
		EdgeList.push_back(make_pair(w, ii(u, v)));
	}
	sort(EdgeList.begin(), EdgeList.end());	//sort by edge weight
	int mst_cost = 0;
	UnionFind UF(V); //all V are disjoint sets initially
	for (int i = 0; i < E; i++){
		pair<int, ii> front = EdgeList[i];
		if (!UF.isSameSet(front.second.first, front.second.second)){
			mst_cost += front.first; //add the weight of e to MST
			UF.unionSet(front.second.first, front.second.second); //link them
		}
	} //the number of disjoint sets must eventually be 1 for a valid MST
	return 0;
}

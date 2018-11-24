#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <memory>
#include <iomanip>
#include <functional>
#include <new>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <cctype>
#include <ctime>

#define REP(i, n) for((i) = 0; i < n; i++)
#define FOR(i, a, n) for((i) = a; i < n; i++)
#define FORR(i, a, n) for((i) = a; i <= n; i++)
#define for_each(q, s) for(typeof(s.begin()) q=s.begin(); q!=s.end(); q++)
#define sz(n) n.size()
#define pb(n) push_back(n)
#define all(n) n.begin(), n.end()

using namespace std;

typedef long long ll;
typedef long double ld;

#define MAXN 200000

ll INF = (ll) (1LL << 60LL);
pair<ll, ll> t[MAXN*4];
int n, v[MAXN+10];

void build(int a[], int v, int tl, int tr){
	if (tl == tr) t[v].first = a[tl];
	else {
		int tm = (tl + tr) >> 1;
		build (a, 2*v,tl,tm);
		build (a, 2*v+1,tm+1,tr);
		t[v].first = min (t[2*v].first,t[2*v+1].first);
	}
}

void update (int v, int tl, int tr, int l, int r, int value){
	if (l > r) return;
	if (tl == l && r == tr) {
		t[v].second += value;
	} else {
		int tm = (tl + tr) >> 1;
		update (2*v,tl,tm,l,min(tm,r),value);
		update (2*v+1,tm+1,tr,max(tm+1,l),r,value);
		t[v].first = min (t[2*v].first + t[2*v].second,t[2*v+1].first + t[2*v+1].second);
	}
}
ll rmq (int v, int tl, int tr, int l, int r){
	if (l > r) {
		return 9999999;
	}
	if (tl == l && tr == r) {
		return t[v].first + t[v].second;
	} else {
		int tm = (tl + tr) >> 1;
		t[v].first = min (t[2*v].first + t[2*v].second,t[2*v+1].first + t[2*v+1].second);
		return min(rmq(2*v,tl,tm,l,min(tm,r)),rmq(2*v+1,tm+1,tr,max(l,tm+1),r))+t[v].second;
	}
}

int main(void) {
	v[0]=0;v[1]=1;v[2]=2;v[3]=3;v[4]=4;v[5]=5;
	build(v,1,0,5);
	long long int z=rmq(1,0,5,3,5);
	printf("%lld\n",z);
//	build(v, 1, 0, n-1);
//	rmq(1, 0, n-1, 0, n-1);
	return 0;
}

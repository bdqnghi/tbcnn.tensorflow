#include <bits/stdc++.h>

#define FOR(i,n) for(int i=0;i<n;++i)
#define REP(i,s,n) for(int i=s;i<n;++i)
#define pb push_back
#define mp make_pair
#define Point pair<int,int>
#define xx first
#define yy second

using namespace std;

vector<Point> p;

int ori(Point p1, Point p2, Point p3){
	return (p3.yy-p2.yy)*(p2.xx-p1.xx)-(p2.yy-p1.yy)*(p3.xx-p2.xx); // if ori>0 then its a left turn
}

int main(){
	int n; cin >> n;
	
	FOR(i,n){
		int a,b; cin >> a >> b;
		p.pb(mp(a,b));
	}

	sort(p.begin(), p.end()); // sort lexicografically

	int k = 0;
	vector<pair<int,int> > H(2*n); // vector for maximally 2N points

	// upper hull
	FOR(i,n){
		while(ori(H[k-2],H[k-1],p[i]) >= 0 and k>1) --k; // if it is a left turn, delete k-1th point
		H[k] = p[i]; // rewrite it here
		++k; // increment k
	}

	// lower hull
	int t = k-1; // initialize t, so we dont rewrite the previously found upper hull
	for(int i=n-1;i>=0;--i){
		while(ori(H[k-2],H[k-1],p[i]) >= 0 and k-1>t) --k; // t therefore must be always smaller then k-1 (we rewrite the k-1th place over and over again)
		H[k] = p[i]; // rewrite
		++k; // increment
	}
	
	H.resize(k-1); // we have exactly k-1 elements (the kth is about to come - but it will never :D)

	FOR(i,H.size()) cout << H[i].xx << " " << H[i].yy << endl; // write them out
}

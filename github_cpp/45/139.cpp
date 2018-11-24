#include <bits/stdc++.h>
#define ADD(a, b) a = (a + (ll)b) % mod
#define MUL(a, b) a = (a * (ll)b) % mod
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define rer(i, a, b) for(int i = (a) - 1; i >= (b); i--)
#define all(a) (a).begin(), (a).end()
#define sz(v) (int)(v).size()
#define pb push_back
#define sec second
#define fst first
#define debug(fmt, ...) Debug(__LINE__, ":", fmt, ##__VA_ARGS__)
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<int, pi> ppi;
typedef vector<ll> vi;
typedef vector<vi> mat;
typedef complex<double> comp;
void Debug() {cout << '\n'; }
template<class FIRST, class... REST>void Debug(FIRST arg, REST... rest) { 
	cout << arg << " "; Debug(rest...); }
template<class T>ostream& operator<< (ostream& out, const vector<T>& v) {
	out << "[";if(!v.empty()){rep(i,0,sz(v)-1)out<<v[i]<< ", ";out<<v.back();}out << "]";return out;}
template<class S, class T>ostream& operator<< (ostream& out, const pair<S, T>& v) {
	out << "(" << v.first << ", " << v.second << ")";return out;}
const int MAX_N = 200010;
const double eps = 1e-6;
const ll mod = 1000000007;
const int inf = 1 << 30;
const ll linf = 1LL << 60;
const double PI = 3.14159265358979323846;
///////////////////////////////////////////////////////////////////////////////////////////////////


namespace MF { //init before you use it. when you use double, be careful. O(|F||E|)

	struct edge {int to; ll cap, rev; };

	vector<edge> G[MAX_N];
	bool used[MAX_N];

	void init(int n) {
		rep(i, 0, n) G[i].clear();
	}

	int add_edge(int from, int to, ll cap) {
		G[from].push_back((edge){to, cap, (int)G[to].size()});
		G[to].push_back((edge){from, 0, (int)G[from].size() - 1});
		return (int)G[from].size() - 1;
	}

	ll dfs(int v, int t, ll f, bool change = true) { //if you just want to dfs, change = false
		if(v == t) return f;
		used[v] = true;
		for(int i = 0; i < (int)G[v].size(); i++) {
			edge &e = G[v][i];
			if(!used[e.to] && e.cap > 0) {
				int d = dfs(e.to, t, min(f, e.cap), change);
				if(d > 0) {
					if(change) {
						e.cap -= d;
						G[e.to][e.rev].cap += d;
					}
					return d;
				}
			}
		}
		return 0;
	}

	ll get(int s, int t) {
		ll flow = 0;
		while(true) {
			memset(used, 0, sizeof(used));
			int f = dfs(s, t, inf);
			if(f == 0) return flow;
			flow += f;
		}
	}
}

void solve() {
	MF::add_edge(0, 1, 10);
	MF::add_edge(0, 2, 2);
	MF::add_edge(1, 2, 6);
	MF::add_edge(1, 3, 6);
	MF::add_edge(3, 4, 8);
	MF::add_edge(2, 4, 5);
	MF::add_edge(3, 2, 3);
	debug(MF::get(0, 4));
}

int main() {
#ifndef LOCAL
	ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    cout << fixed;
	cout.precision(20);
#ifdef LOCAL
    freopen("in.txt", "rt", stdin);
#endif	
	solve();
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}


 
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef string st;
typedef vector<int> vi;
#define rep(i, n) for(int i = 0; i < n; ++i)
#define fogg(i,a,b) for(int i = (a); i <= (b); ++i)
#define ford(i,a,b) for(int i = (a); i >= (b); --i)
#define test int test_case; cin >> test_case; while(test_case--)
#define debug(x) cout << '>' << #x << ':' << x << "\n";
#define endl '\n'
#define off ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define mxx (ll)1000000007

void solve(int n, char source, char helper, char dest) {
	if (n == 0)
		return;

	solve(n-1, source, dest, helper);

	cout << "Move " << n << "th disk from " << source << " to " << dest << endl;

	solve(n-1, helper, source, dest); 
}

int main() {
	off;
	ll n;
	cin >> n;

	solve(n, 'A', 'B', 'C');

  	return 0;
}
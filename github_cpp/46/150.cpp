#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define FAST_IO  ios_base::sync_with_stdio(false)
#define EPS 1e-8

int N, Q;

// This is azure97 (Kak Ayaz)'s implementation of SegmentTree 
struct SegmentTree {
    vi max_value;
    vi min_value;
    vi arr;
    int n;

    SegmentTree() {
    }

    void set_n(int _n) {
        n = _n;
        arr.resize(n+5);
        max_value.resize(n+5);
        min_value.resize(n+5);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            min_value[id] = arr[l];
            max_value[id] = arr[l];
        } else {
            int m = (l + r) / 2;
            int chld = id << 1;

            build(chld, l, m);
            build(chld + 1, m + 1, r);

            max_value[id] = max(max_value[chld], max_value[chld+1]);
            min_value[id] = min(min_value[chld], min_value[chld+1]);
        }
    }

    void build() {
        build(1, 1, n);
    }

    // query range(x, y)
    int query_min(int id, int l, int r, int x, int y) {
        if (x <= l && r <= y) {
            cerr << "return " << min_value[id] << '\n';
            return min_value[id];
        } else {
            int m = (l + r) / 2;
            int chld = id << 1;

            int ret = 1e9+1;
            if (x <= m) ret = min(ret, query_min(chld, l, m, x, y));
            if (y > m) ret = min(ret, query_min(chld+1, m+1, r, x ,y));
            cerr << "return bawah " << ret<< endl;
            return ret;
        }
    }

    int query_min(int l, int r) {
        int ret =  query_min(1, 1, n, l, r);
        cerr << "query min is " << ret << endl;
        return ret;
    }

    int query_max(int id, int l,  int r, int x, int y) {
        if (x <= l && r <= y) {
            cerr << "return " << max_value[id] << '\n';
            return max_value[id];
        } else {
            int m = (l + r) / 2;
            int chld = id << 1;

            int ret = -1e9-1;
            if (x <= m) ret = max(ret, query_max(chld, l, m, x, y));
            if (y > m) ret = max(ret, query_max(chld+1, m+1, r, x, y));

            return ret;
        }
    }

    int query_max(int l, int r) {
        return query_max(1, 1, n, l, r);
    }
};

int main() {
    // C++ Fast I/O
    FAST_IO;

    SegmentTree segment_tree;
    // N elements, Q queries
    cin >> N >> Q;

    segment_tree.set_n(N);
    
    for (int i = 1; i <= N; ++i) {
        cin >> segment_tree.arr[i]; 
    }

    segment_tree.build();
    
    for (int i = 0; i < Q; ++i) {
        int L, R;
        // Read Query here
        cin >> L >> R;
        // Do something here
    }

	return 0;
}

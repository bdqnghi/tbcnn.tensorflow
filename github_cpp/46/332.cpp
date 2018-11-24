#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct SegmentTree {
    ll value, push;
    SegmentTree *l, *r;

    inline SegmentTree () : value(0), push(-1), l(NULL), r(NULL) {}

	inline void shove (int l, int r) {
		if (this->l == NULL)
			this->l = new SegmentTree(), this->r = new SegmentTree();
		if (this->push == -1) {
			return;
		}
		this->value = (this->l->push = this->r->push = this->push) * (r - l + 1);
		this->push = -1;
	}

    inline ll get (int l, int r, int tl, int tr) {
        if (r < tl || l > tr)
            return 0;
		this->shove(l, r);
		if (tl <= l && r <= tr)
			return this->value;
		int md = (l + r) >> 1;
        return this->l->get(l, md, tl, tr) + this->r->get(md + 1, r, tl, tr);
    }

    inline ll upd (int l, int r, int tl, int tr, ll val) {
		this->shove(l, r);
        if (r < tl || l > tr)
            return this->value;
        if (tl <= l && r <= tr)
            return this->value = (this->push = val) * (r - l + 1);
        int md = (l + r) >> 1;
        return this->value = this->l->upd(l, md, tl, tr, val) + this->r->upd(md + 1, r, tl, tr, val);
    }
} *ST;

int n, k;

int main () {
    freopen("sum.in", "r", stdin); freopen("sum.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    ST = new SegmentTree();
    cin >> n >> k;
    while (k--) {
        char tpe;
        cin >> tpe;
        if (tpe == 'A') {
            int l, r, x;
			cin >> l >> r >> x;
			ST->upd(1, n, l, r, x);
		}
        else {
			int l, r;
			cin >> l >> r;
			cout << ST->get(1, n, l, r) << endl;
        }
    }
}

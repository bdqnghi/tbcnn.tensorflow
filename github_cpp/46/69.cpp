#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<int> vi;

int approxTwo(int n) {
  n = n - 1;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  return n + 1;
}

struct SegmentTree {
  vi tree;
  vi lazy;
  int N;
  int H;

  SegmentTree(vi &values) {
    N = approxTwo(values.size());
    H = 8 * sizeof(int) - __builtin_clz(N);

    tree.resize(N << 1);
    lazy.resize(N);
    for(int i = 0; i < values.size(); ++i) {
      tree[i+N] = values[i];
    }

    for(int i = N - 1; i >= 1; --i) {
      tree[i] = merge(tree[i<<1], tree[i<<1|1]);
    }
  }

  int merge(int a, int b) {
    return a + b;
  }

  void apply(int p, int value, int k) {
    tree[p] += value * k;
    if(p < N) lazy[p] += value;
  }

  void build(int p) {
    for(p >>= 1; p >= 1; p >>= 1) {
      tree[p] = merge(merge(tree[p<<1], tree[p<<1|1]), lazy[p]);
    }
  }

  void push(int p) {
    int k = N;
    for(int s = H; s > 0; --s, k >>= 1) {
      int i = p >> s;
      if(lazy[i]) {
        apply(i>>1,   lazy[i], k);
        apply(i>>1|1, lazy[i], k);
        lazy[i] = 0;
      }
    }
  }

  // update interval [l, r)
  void update(int l, int r, int value) {
    int l0 = (l += N);
    int r0 = (r += N);

    push(l0);
    push(r0-1);
    
    for(int k = 1; r > l; l >>= 1, r >>= 1, k <<= 1) {
      // l is the right child of the parent, so include l but not the parent
      if(l&1) {
        apply(l++, value, k);
      }
      // r is the right child of the parent, so include the left child but not the parent
      if(r&1) {
        apply(--r, value, k);
      }
    }

    build(l0);
    build(r0-1);
  }

  // query interval [l, r)
  int query(int l, int r) {
    push(l+N);
    push(r+N-1);

    int res = 0;
    for(l += N, r += N; r > l; l >>= 1, r >>= 1) {
      // l is the right child of the parent, so include l but not the parent
      if(l&1) {
        res = merge(res, tree[l++]);
      }
      // r is the right child of the parent, so include the left child but not the parent
      if(r&1) {
        res = merge(res, tree[--r]);
      }
    }
    return res;
  }
};

int main() {
  vi test({1, 2, 3, 4, 5, 6});
  SegmentTree tree(test);

  tree.update(1, 3, 2);
  cout << tree.query(2, 5) << endl;

  return 0;
}
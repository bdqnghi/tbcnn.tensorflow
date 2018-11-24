#include <cstdio>

//#include "z.h"

#define MX 100001
#define root(l, r) (~(l!=r-1)&(l+r))

long long sum[MX<<1];
long long cache[MX<<1];

void up(int l, int r);

void build(int l, int r) {
    int rt = root(l, r);
    if (l == r-1) {
        scanf("%lld", &sum[rt]);
        return;
    }
    int m = (l+r)>>1;
    build(l, m);
    build(m ,r);
    sum[rt] = sum[root(l,m)] + sum[root(m, r)];
}

void down(int l, int r) {
    int rt = root(l, r);
    int m = (l+r)>>1;
    if (cache[rt]) {
        cache[root(l, m)] += cache[rt];
        cache[root(m, r)] += cache[rt];
        cache[rt] = 0;
    }
}

void update(int l, int r, int s, int e, long long v) {
    int rt = root(l, r);
    if (s <= l && e >= r) {
        cache[rt] += v;
        return;
    }
    int m = (l+r)>>1;
    down(l, r);
    if (s < m && e > l) {
        update(l, m, s, e, v);
    }
    if (s < r && e > m) {
        update(m, r, s, e, v);
    }
    up(l, r);
}

long long query(int l, int r, int s, int e) {
    int rt = root(l, r);
    long long ret = 0;
    if (s <= l && e >= r) {
        ret = sum[rt] + cache[rt] * (r-l);
        return ret;
    }
    int m = (l+r)>>1;
    down(l, r);
    if (s < m && e > l) {
        ret += query(l, m, s, e);
    }
    if (s < r && e > m) {
        ret += query(m, r, s, e);
    }
    up(l, r);
    return ret;
}

void up(int l, int r) {
    int rt = root(l, r);
    int m = (l+r)>>1;
    sum[rt] = query(l, m, l, m) + query(m, r, m, r);
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    build(0, n);
    //AA(sum, n * 2);
    char op[2];
    int s, e, v;
    while (q--) {
        scanf("%s", op);
        if (op[0] == 'Q') {
            scanf("%d %d", &s, &e);
            printf("%lld\n", query(0, n, s-1, e));
        } else {
            scanf("%d %d %d", &s, &e, &v);
            update(0, n, s-1, e, v);
        }
    }
    return 0;
}


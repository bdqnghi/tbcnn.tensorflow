#include <cstdio>
#include <cstring>

//#include "z.h"

#define root(l, r) (~(l!=r-1)&(l+r))

#define MX 200010

int sum[MX<<1], cache[MX<<1];

inline int getvalue(int l, int r) {
    int rt = root(l, r);
    return cache[rt] >= 0 ? (r-l) * cache[rt]: sum[rt];
}

void update(int l, int r, int s, int e, int v) {
    int rt = root(l, r);
    //VV(rt, l, r, s, e, v);
    if (s <= l && e >= r) {
        cache[rt] = v;
        sum[rt] = v * (r-l);
        //VV(cache[rt], sum[rt]);
        return;
    }
    int m = (l+r)>>1;
    if (cache[rt] >= 0) {
        cache[root(l, m)] = cache[rt];
        cache[root(m, r)] = cache[rt];
        cache[rt] = -1;
    }
    if (s < m && e > l) {
        update(l, m, s, e, v);
    }
    if (s < r && e > m) {
        update(m, r, s, e, v);
    }
    sum[rt] = getvalue(l, m) + getvalue(m, r);
}

int main() {
    int n, q, T, x, y, c;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d %d", &n, &q);
        memset(sum, 0, sizeof(sum));
        memset(cache, 0xff, sizeof(cache));
        for (int i = 0; i < q; i++) {
            scanf("%d %d %d", &x, &y, &c);
            update(0, n, x-1, y, c-1);
        }
        printf("Case %d: The total value of the hook is %d.\n", t+1, sum[root(0, n)] + n);
    }
    return 0;
}


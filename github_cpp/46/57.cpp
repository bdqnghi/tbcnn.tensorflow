#include <cstdio>
#include <cstring>
#include <algorithm>

//#include "z.h"

using namespace std;

#define root(l, r) (~(l!=r-1)&(l+r))
#define MX 10005

int sum[MX<<2], all[MX<<1];
int st[MX], ed[MX];

void down(int l, int r) {
    int m = (l+r)>>1, rt = root(l, r);
    if (sum[rt] == r-l) {
        sum[root(l, m)] = m - l;
        sum[root(m, r)] = r - m;
    }
}

void update(int l, int r, int s, int e) {
    int rt = root(l, r);
    if (s <= l && e >= r) {
        sum[rt] = r - l;
        return;
    }
    down(l, r);
    int m = (l+r)>>1;
    if (s < m && e > l) {
        update(l, m, s, e);
    }
    if (s < r && e > m) {
        update(m, r, s, e);
    }
    sum[rt] = sum[root(l, m)] + sum[root(m, r)];
}

int query(int l, int r, int s, int e) {
    int rt = root(l, r);
    if (s <= l && e >= r) {
        return sum[rt];
    }
    int m = (l+r)>>1;
    down(l, r);
    int ret = 0;
    if (s < m && e > l) {
        ret += query(l, m, s, e);
    }
    if (s < r && e > m) {
        ret += query(m, r, s, e);
    }
    sum[rt] = sum[root(l, m)] + sum[root(m, r)];
    return ret;
}

int bi(int a[], int len, int v) {
    int i = 0, j = len, mi, m;
    while (i < j) {
        mi = (i+j)>>1;
        m = a[mi];
        if (m == v) return mi;
        if (m < v) {
            i = mi+1;
        } else {
            j = mi;
        }
    }
    return -1;
}

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int p = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", st+i, ed+i);
            st[i]--;
            all[p++] = st[i];
            ed[i];
            all[p++] = ed[i];
        }
        sort(all, all+p);
        int j = 1;
        for (int i = 1; i < p; i++) {
            if (all[i] - all[i-1]) {
                all[j++] = all[i];
            }
        }
        p = j;
        //AA(all, p);
        memset(sum, 0, sizeof(sum));
        int ans = 0;
        for (int i = n-1; i>=0; i--) {
            int left = bi(all, p, st[i]);
            int right = bi(all, p, ed[i]);
            //VV(left, right, st[i], ed[i]);

            if (query(0, p, left, right) < right - left) {
                ans++;
            }
            update(0, p, left, right);
        }
        printf("%d\n", ans);
    }
    return 0;
}


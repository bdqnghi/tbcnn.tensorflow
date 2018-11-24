#include <cstdio>

//#include "z.h"

#define root(l, r) (~(l!=r-1)&(l+r))
#define MX 500001

const int ap[]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,554400,665280};
const int fn[]={1,2,3,4,6,8,9,10,12,16,18,20,24,30,32,36,40,48,60,64,72,80,84,90,96,100,108,120,128,144,160,168,180,192,200,216,224}; 

char name[MX][11];
int next[MX];
int sum[MX<<1];

int update(int l, int r, int x) {
    int rt = root(l, r);
    if (l == r-1) {
        sum[rt] = 1;
        return l;
    }
    int m = (l+r)>>1;
    int ret;
    if (m - l - sum[root(l, m)] > x) {
        ret = update(l, m, x);
    } else {
        ret = update(m, r, x - (m - l - sum[root(l, m)]));
    }
    sum[rt] = sum[root(l, m)] + sum[root(m, r)];
    return ret;
}

int main() {
    int n, k;
    while (~scanf("%d %d", &n, &k)) {
        k--;
        for (int i = 0; i < n; i++) {
            scanf("%s %d", name[i], next+i);
        }
        int ans = 0, num = 0;
        for (int i = sizeof(ap)/sizeof(int)-1; i >= 0; i--) {
            if (ap[i] <= n) {
                num = ap[i];
                ans = fn[i];
                break;
            }
        }
        int order = 0, who = 0;
        for (int i = 0; i < num; i++) {
            order = ((order + k) % (n-i) + n-i) % (n-i);
            who = update(0, n, order);
            //VV(order, who, name[who]);
            k = next[who]-1;
            if (k < 0) k++;
        }
        printf("%s %d\n", name[who], ans);
    }
    return 0;
}

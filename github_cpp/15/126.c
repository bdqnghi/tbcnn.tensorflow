#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

#define MOD 321555123

using namespace std;
struct matrix {
    int M [100] [100], n, m;
    matrix () {}
    matrix (int _n, int _m) {n = _n; m = _m; for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) M [i] [j] = 0;}
    matrix operator * (const matrix & x) const {
        matrix ret = matrix ((*this).n, x.m);
        for (int i = 1; i <= (*this).n; i++)
            for (int j = 1; j <= x.m; j++)
                for (int k = 1; k <= (*this).m; k++)
                    ret.M [i] [j] += ((*this).M [i] [k] % MOD) * (x.M [k] [j] % MOD);
    }

    void operator *= (const matrix & x) {
        matrix ret = matrix ((*this).n, x.m);
        for (int i = 1; i <= (*this).n; i++)
            for (int j = 1; j <= x.m; j++)
                for (int k = 1; k <= (*this).m; k++)
                    ret.M [i] [j] += ((*this).M [i] [k] % MOD) * (x.M [k] [j] % MOD);
    }
};
int main () {
    return 0;
}

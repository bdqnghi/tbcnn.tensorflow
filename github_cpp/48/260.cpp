#include<algorithm>
#include<cctype>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<string>
#define lowbit(x) (x & (-x))
#define root 1, n, 1
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1  1
#define ll long long
#define pr(x) cout << #x << " = " << (x) << '\n';
using namespace std;

const int INF = 0x7f7f7f7f;
const int MAXN = 1e6 + 111;

char Ma[MAXN * 2];
int Mp[MAXN * 2], ans;

void Manacher(char s[], int len)
{
    int l = 0;
    Ma[l++] = '$'; Ma[l++] = '#';
    for (int i = 0; i < len; ++i)
    {
        Ma[l++] = s[i];
        Ma[l++] = '#';
    }
    Ma[l] = 0;

    int id = 0, mx = 0;

    for (int i = 0; i < l; ++i)
    {
        Mp[i] = mx > i ? min(mx - i, Mp[2 * id - i]) : 1;
        while (Ma[i + Mp[i]] == Ma[i - Mp[i]]) ++Mp[i];
        ans = max(ans, Mp[i] - 1);
        if (i + Mp[i] > mx)
        {
            mx = i + Mp[i];
            id = i;
        }
    }
    return;
}

char s[MAXN];

int main()
{
    int kase = 0;

    while (scanf("%s", &s))
    {
        if (strcmp(s, "END") == 0) break;
        ans = 0;
        Manacher(s, strlen(s));
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}

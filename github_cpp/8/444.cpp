#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long F[61];
long long LCA(long long a, long long b)
{
	int t1 = 59, t2 = 59;
    while (a != b)
    {
    	if (a < b) swap(a, b), swap(t1, t2);
    	while (t1 && F[t1] >= a) t1--;
    	a -= F[t1];
    }
    return a;
}
int main()
{
    int m;
    scanf ("%d", &m);
    F[1] = 1; F[2] = 1;
    for (int i = 3; i <= 60; i++)
        F[i] = F[i - 1] + F[i - 2];
    long long a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%lld%lld", &a, &b);
        printf ("%lld\n", LCA(a, b));
    }
}

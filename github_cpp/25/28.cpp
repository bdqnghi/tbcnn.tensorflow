#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <list>
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	while (x);
	do
	{
		putchar(buffer[--length]);
	}
	while (length);
	putchar('\n');
}

const INT mod = 998244353;
const INT maxn = 100005;
INT n;
INT a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	INT t[20];

	brute()
	{
		for(int i = 1; i <= n; i++)
			t[i] = i;
		INT ans = 0;
		do
		{
			bool bOk = true;
			for(int i = 1; i <= n; i++)
				if(a[i] && t[i] != a[i])
				{
					bOk = false;
					break;
				}
			if(!bOk) continue;

			for(int i = 1; i <= n; i++)
			{
				INT pos = i;
				INT step = 0;
				do
				{
					pos = t[pos];
					step++;
				}
				while(pos != i);
				if(step & 1)
				{
					bOk = false;
					break;
				}
			}
			if(!bOk) continue;
			ans++;
		}
		while(std::next_permutation(t + 1, t + 1 + n));
		printOut(ans);
	}
};
struct cheat
{
	cheat()
	{
		INT ret = 1;
		n /= 2;
		for(int i = 2; i <= n; i++)
		{
			INT mul = i * 2 - 1;
			mul = mul * mul % mod;
			ret = ret * mul % mod;
		}
		printOut(ret);
	}
};
struct work
{
	work()
	{
	}
};

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
		a[i] = readIn();
	if(n & 1)
	{
		printOut(0);
		return;
	}

	if(n <= 8)
		RunInstance(brute);
	else if(*std::max_element(a + 1, a + 1 + n) == 0)
		RunInstance(cheat);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("permutation.in", "r", stdin);
	freopen("permutation.out", "w", stdout);
#endif
	run();
	return 0;
}

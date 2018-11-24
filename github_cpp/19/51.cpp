#include<algorithm>
#include<assert.h>
#include<bitset>
#include<climits>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<deque>
#include<iostream>
#include<map>
#include<memory.h>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<string>
#include<utility>
#include<vector>

using namespace std;

#define LL long long int

typedef vector<int> VI;
typedef vector<LL> VLL;
typedef vector<double> VD;
typedef vector<string> VS;
typedef vector<VI> VVI;
typedef vector<VLL> VVLL;
typedef vector<VD> VVD;
typedef vector<VS> VVS;
typedef pair<int,int> PI;
typedef vector<pair<int,int> > VPI;
typedef pair<double,double> PD;

#define SI ({int _x; scanf("%d",&_x); _x;})
#define SC ({char _x; scanf("%c",&_x); _x;})
#define SLL ({LL _x; scanf("%lld",&_x); _x;})
#define SLF ({double _x; scanf("%lf",&_x); _x;})
#define PI(x) printf("%d",x)
#define PC(x) printf("%c",x)
#define PLL(x) printf("%lld",x)
#define PLF(x) printf("%lf",x)
#define PS(x) printf("%s",x)
#define P32() printf(" ")
#define P10() printf("\n")
#define lc(i) (i<<1)
#define rc(i) ((i<<1)+1)
#define iscan(n) scanf("%d",&n)
#define cscan(n) scanf("%c",&n)
#define llscan(n) scanf("%lld",&n)
#define lfscan(n) scanf("%lf",&n)
#define sscan(n) scanf("%s",n)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define FORD(i,a,b) for(int i=b-1;i>=a;--i)
#define REP(i,b) for(int i=0;i<b;++i)
#define REPD(i,b) for(int i=b-1;i>=0;--i)
#define MP(a,b) make_pair(a,b)
#define PB(a) push_back(a)
#define FILL(a,b) memset(a,b,sizeof a)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)<0?-(a):(a))
#define ALL(a) a.begin(),a.end()
#define SORT(a) sort(ALL(a))
#define TR(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++) 

char s[12345678];
int F[12345678];

void compute_failure_function(string &b)
{
	int l = b.length(), i = 2, j = 0;

	F[0] = -1;
	F[1] = 0;

	while(i < l)
	{
		if(b[i-1] == b[j])
		{
			++j;
			F[i] = j;
			++i;
		}
		else if(j > 0)
		{
			j = F[j];
		}
		else
		{
			F[i] = 0;
			++i;
		}
	}
}

void kmp(string &a, string &b)
{
	compute_failure_function(b);

	int la = a.length(), lb = b.length(), i = 0, j = 0;
	bool flag = false;
	while(i < la)
	{
		if(a[i] == b[j])
		{
			++j;

			if(j == lb) 
			{ 
				flag = true;
				printf("%d\n", i-lb+1); 
				j = F[lb-1];
			}
			else
			{
				++i;
			}
		}
		else if(j > 0)
		{
			j = F[j];
		}
		else
		{
			++i;
		}
	}

	if(!flag) { printf("\n"); }
}

int main()
{
	int N;
	while(iscan(N) != EOF)
	{
		string a, b;

		sscan(s); b = s;
		sscan(s); a = s;

		kmp(a, b);
	}

	return 0;
}

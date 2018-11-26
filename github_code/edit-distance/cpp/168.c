#include <bits/stdc++.h>
using namespace std;
#define f(i,n) for(int i=0;i<n;i++)
#define g(n) scanf("%d",&n)

char s1[2010], s2[2010];
int dp[2001][2001];
int compute(int i, int j)
{
	if(i==-1) return j+1;
	if(j==-1) return i+1;
	if(dp[i][j]!=-1)
		return dp[i][j];
	int m = 1+compute(i-1,j); //deleting from i
	m = min(m, 1+compute(i,j-1)); //inserting in i, so one char is matched
	int t = compute(i-1,j-1) + (s1[i]==s2[j] ? 0:1);
	m = min(m,t);
	dp[i][j] = m;
	return m;
}

int main()
{
	int t;
	g(t);
	while(t--)
	{
		scanf("%s",s1);
		scanf("%s",s2);
		int l1 = strlen(s1), l2 = strlen(s2);
		f(i,l1+1)
		{
			f(j,l2+1)
			{
				if(i==0)
					dp[i][j] = j;
				else if(j==0)
					dp[i][j] = i;
				else
				{
					int m = dp[i-1][j]+1;
					m = min(m, 1 + dp[i][j-1]);
					int t = dp[i-1][j-1] + (s1[i-1]==s2[j-1] ? 0:1);
					m = min(m,t);
					dp[i][j] = m;
				}
			}
		}
		printf("%d\n",dp[l1][l2]);
	}
	return 0;
}
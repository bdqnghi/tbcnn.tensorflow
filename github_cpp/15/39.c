

#include <bits/stdc++.h>
using namespace std;
#define all(c) c.begin(), c.end()
#define tr(container, it) for(auto it = container.begin(); it != container.end(); it++) 
#define debug(x) cerr<<"[DEBUG] "<<#x<<"="<<x<<endl
#define boostIO ios_base::sync_with_stdio(false)
#define ld long double
#define ll long long int
#define CLR(s) memset(&s, 0, sizeof(s))
#define scani(s) scanf("%d",&s)
#define pll pair<ll,ll>
#define pii pair<int,int>
#define pb push_back
#define mp make_pair
#define f0(i, n) for(int i=0; i<n; i++)
#define f1(i, n) for(int i=1; i<=n; i++)
#define F first
#define S second
#define endl '\n'
int n;
int a[1000]={0};
int as[1000]={0};
int dp[1000][1000];
int fn(int l, int r) {
	if(l==r) return 0;
	if(dp[l][r]!=-1) return dp[l][r];
	int mi=INT_MAX;
	for(int i=l; i<r; i++) {
		mi = min(mi, fn(l, i) + fn(i+1, r) + ((as[r]-as[i])%100)*((as[i]-as[l-1])%100));
	}
	return dp[l][r]=mi;
}

int main()
{
	
	
	while( scanf("%d",&n) > 0 ) {
		for(int i=0; i<=n; i++) {
			a[i]=0;
			as[i]=0;
			for(int j=0; j<=n; j++) {
				dp[i][j]=-1;
			}
		}
		f1(i, n) cin>>a[i];
		for(int i=1; i<=n; i++) {
			as[i]=as[i-1]+a[i];
		}
		cout<<fn(1, n)<<endl;
	}
	return 0;
}

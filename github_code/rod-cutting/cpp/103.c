#include <bits/stdc++.h>
using namespace std;
int solve(int l,int n,int a[],int dp[])
{
    int i;
    if(l==0)return 0;
    if(dp[l]>-1)return dp[l];
    for(i=1;i<=n;i++)
    {
        if(l-i>=0)
        {
            dp[l]=max(dp[l],solve(l-i,n,a,dp)+a[i]);
        }
    }
    return dp[l];
}

int main() {
	//code
	int t;
	cin>>t;
	while(t--)
	{
	    int n,i,ans;cin>>n;
	    int a[n+1];
	    for(i=1;i<=n;i++)cin>>a[i];
	    int dp[n+1];
	    for(i=0;i<=n;i++)dp[i]=-1;
	    ans=solve(n,n,a,dp);
	    cout<<ans<<endl;
	}
	return 0;
}

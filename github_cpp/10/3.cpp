#include<bits/stdc++.h>
using namespace std;
int dp[3000][3000];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {string s1,s2;
        cin>>s1>>s2;
        int sz1=s1.length();
        int sz2=s2.length();
        memset(dp,0,sizeof(dp[0][0]*(sz1+1)*(sz2+1)));
        for(int i=0;i<=s1.size();i++)
            dp[i][0]=i;
        for(int j=0;j<=s2.size();j++)
            dp[0][j]=j;
        for(int i=1;i<=sz1;i++)
        {
            for(int j=1;j<=sz2;j++)
            {
                if(s1[i-1]==s2[j-1])
                    dp[i][j]=dp[i-1][j-1];
                else
                    dp[i][j]=min(dp[i-1][j-1]+1,min(dp[i-1][j]+1,dp[i][j-1]+1));
            }
        }cout<<dp[sz1][sz2]<<endl;
    }return 0;
}

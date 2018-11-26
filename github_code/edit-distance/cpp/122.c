#include<iostream>
#include<string.h>
using namespace std;

int findsteps(string s1,string s2)
{

    int n=s1.length();
    int m=s2.length();

    int dp[n+1][m+1];
    memset(dp,0,sizeof(dp));

    for(int i=0;i<=n;i++)
    {
        dp[i][0]=i;
    }
    for(int i=1;i<=m;i++)
    {
        dp[0][i]=i;
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(s1[i-1]==s2[j-1])
            {
                dp[i][j]=dp[i-1][j-1];
            }
            else
            {
                dp[i][j]=1+min(dp[i][j-1],min(dp[i-1][j],dp[i-1][j-1]));
            }
        }
    }
    return dp[n][m];
}
int main()
{
    string s1="krishna";
    string s2="kamal";

     cout<<findsteps(s1,s2);
     return 0;
}

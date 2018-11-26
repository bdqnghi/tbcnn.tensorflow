//
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
void editdistance(string s,string t);
int dp[100][100]={0};
int main()
{
    editdistance("algorithm","altruistic");
}
void editdistance(string s,string t)
{
    int sorce = s.length();
    int target = t.length();
    for(int i = 1;i <= sorce;i++)
        dp[i][0] = i;
    for(int i = 1;i <= target;i++)
        dp[0][i] = i;
    for(int i  =1; i <= sorce;i++)
        for(int j = 1;j <= target;j++)
        {
            if(s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1];
            else 
                dp[i][j] = min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
        }
    cout << dp[sorce][target];
}
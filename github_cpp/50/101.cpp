#include <iostream>
#include <cstring>
#include <algorithm>

int knapsack(int W, int* wt, int* val, int n)
{
    int dp[n+1][W+1];
    memset(dp, 0, sizeof(dp));
    for( int i =1; i<=n; i++)
    {
        for( int w=1; w<=W; w++)
        {
            if(wt[i-1]<=w)
            {
                dp[i][w]=std::max(dp[i-1][w],dp[i-1][w-wt[i-1]]+val[i-1]);
            }
            else
            {
                dp[i][w]=dp[i-1][w];
            }
        }
    }
    return dp[n][W];
}
int main(){
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int  W = 50;
    int n = sizeof(val)/sizeof(val[0]);
    printf("\nValue = %d", knapsack(W, wt, val, n));
    return 0;
}
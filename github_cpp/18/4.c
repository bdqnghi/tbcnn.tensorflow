#include<iostream>
using namespace std;


int maxX(int a, int b, int c)
{
    int ans = max(a, b);
    return max(ans, c);
}

int maxProdCut(int N)
{
    
    int maxVal = 0;
    if(N==0 or N==1) return 0;
    else
    {
        for(int i=1; i<N; i++)
        {
            
            maxVal = maxX(maxVal, i*(N-i), i*maxProdCut(N-i));
        }
        return maxVal;
    }
}

int maXProdCutDynamic(int N)
{
    int dp[N+1];
    dp[0] = dp[1] = 0;
    int maxVal = 0;
    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<i; j++)
        {
            maxVal = maxX(maxVal, j*(i-j), j*dp[i-j]);
        }
        dp[i] = maxVal;
    }
    return dp[N];
}


int main()
{
    cout<<maXProdCutDynamic(8)<<endl;
    
return 0;
}

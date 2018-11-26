//https://practice.geeksforgeeks.org/problems/cutted-segments/0

#include <iostream>
#include <vector>
using namespace std;
int a[3];

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        cin>>a[0]>>a[1]>>a[2];

        vector <vector<int>> dp(4, vector <int> (n+1,0));
        for(int j=0;j<=3;j++)
            dp[j][0] = 1;
        int max_ = 0;
        for(int i=1;i<4;i++)
        {
            for(int j=1;j<=n;j++)
            {
                dp[i][j] = dp[i-1][j];
                if(j >= a[i-1])
                {
                    if(dp[i][j-a[i-1]] != 0)
                    dp[i][j] = max(dp[i][j], dp[i][j-a[i-1]] + 1);
                }
            }
        }
        for(int i=0;i<4;i++)
        {
            if(dp[i][n] > max_)
                max_ = dp[i][n];
        }

        cout<<max_-1<<endl;
    }
    return 0;
}
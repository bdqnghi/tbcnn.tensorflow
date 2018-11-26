
#include <bits/stdc++.h>

using namespace std;

const int NX = 100;

int dp[ NX ][ NX ], n, length[ NX ], profit[ NX ] , rod_length;


void Input()
{
    cin >> n ;
    for( int i = 1 ; i <= n ; i++ )
    {
        cin >> length[i] >> profit[i];
    }
    cin >> rod_length;

}


void Rod_cutting()
{
   for( int i = 1 ; i <= n ; i++ )
   {
       for( int j = 0 ; j <= rod_length ; j++ )
       {
           dp[i][j] = dp[i-1][j];
           if( j >= length[i] )
           {
               dp[i][j] = max( dp[i][j], dp[i][j-length[i]] + profit[i] );
           }
       }
   }

   cout << " Maximum Profit " << dp[n][rod_length] << endl;
}


int main()
{
    Input();
    Rod_cutting();
}

//Recursive Approach With Memoization
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll dp[1000];

ll find_max_sum(ll arr[], ll n)
{
    if (dp[n] != -1)
        return dp[n];
    if (n == 0)
        return 0;
    for (ll i = 1; i < n + 1; i++)
    {
        dp[n] = max(dp[n], arr[i] + find_max_sum(arr, n - i));
    }
    return dp[n];
}

int main()
{
    ll t, n, *arr;
    cin >> t;
    while (t--)
    {
        memset(dp, -1, sizeof(dp));
        cin >> n;
        arr = new ll[n + 1];
        for (int i = 1; i < n + 1; i++)
        {
            cin >> arr[i];
        }
        cout << find_max_sum(arr, n) << endl;
    }
}

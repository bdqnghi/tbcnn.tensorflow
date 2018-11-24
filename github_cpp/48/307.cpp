#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <cassert>
#include <stack>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <set>

using namespace std;

#define DEBUG 10

#define REP(i, a, b) for (long long i = (ll)a; i < (ll)b; i++)
#define REPE(i, a, b) for (long long i = (ll)a; i <= (ll)b; i++)
#define REPD(i, a, b) for (long long i = (ll)a; i >= (ll)b; i--)
#define ll long long
#define vl vector<long long>
#define vll vector<vector<long long>>
#define vi vector<int>
#define vii vector<vector<int>>

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long testcases = 1;
    // cin >> testcases;
    REP(testcase, 0, testcases)
    {
#if DEBUG == 1
        cout << "*********testcase " << testcase << " ************" << endl;
#endif
        int n;
        cin>>n;
        string s, t;
        cin >> s;
        t = s;
        int m = INT_MIN;
        n = s.length();
        reverse(t.begin(), t.end());
        vii dp(2, vi(n, 0));
// cout << s << "\t" << t << endl;
// REP(i, 0, n)
// dp[i][0] = s[0] == t[i] ? 1 : 0;
// REP(i, 0, n)
// dp[0][i] = t[0] == s[i] ? 1 : 0;

#if DEBUG == 1

#endif
        REP(i, 0, n)
        {
            dp[1][0] = max(dp[0][0],s[0] == t[i] ? 1 :0);
            REP(j, 1, n)
            {

                if (s[j] == t[i])
                {
                    // cout<<s[j]<<" ";
                    dp[1][j] = dp[0][j - 1] + 1;
                }
                else
                    dp[1][j] = max(dp[0][j], dp[1][j - 1]);
                m = max(dp[1][j], m);
            }
            dp[0] = dp[1];
            fill(dp[1].begin(), dp[1].end(), 0);
            // dp[1][0] = max(dp[0][0],s[i+1]==t[;
            // dp[1][0] = dp[0][0];

#if DEBUG == 1

            REP(j, 0, n)
                cout << dp[0][j] << "\t";
            cout << endl;
#endif
        }
        // cout<<endl;
        cout << n - m << endl;

#if DEBUG == 1
        // cout << s << endl;
        // REP(i, 0, n)
        // {
        //     REP(j, 0, n)
        //     cout << dp[0][j] << "\t";
        //     cout << endl;
        // }

        // cout << endl;
#endif
    }

    return 0;
}
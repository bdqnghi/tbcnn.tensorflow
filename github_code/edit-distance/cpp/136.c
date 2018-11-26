/**
* edit-distance.cpp
* https://oj.leetcode.com/problems/edit-distance/
*
*/
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int> > dp(n+1, vector<int>(m+1, -1));
        dp[0][0] = 0;
        for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j) {
            if (i > 0) update(dp[i][j], dp[i-1][j] + 1);
            if (j > 0) update(dp[i][j], dp[i][j-1] + 1);
            if (i > 0 && j > 0) update(dp[i][j], dp[i-1][j-1] + (word1[i-1] != word2[j-1]));
        }
        return dp[n][m];
    }
    void update(int &a, int b) {
        if (b < 0) return;
        if (a < 0 || a > b) a = b;
    }
};

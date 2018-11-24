class Solution {
public:
    /**
     * @param word1: A string
     * @param word2: A string
     * @return: The minimum number of steps.
     */
    int minDistance(string &word1, string &word2) {
        // write your code here
        if (word1.size() == 0) {
            return word2.size();
        }
        if (word2.size() == 0) {
            return word1.size();
        }
        int R = word1.size() + 1;
        int C = word2.size() + 1;
        
        vector<vector<int>> dp (R, vector<int> (C));
        for (int i = 0; i < R; ++i) {
            dp[i][0] = i;
        }
        for (int i = 0; i < C; ++i) {
            dp[0][i] = i;
        }
        for (int i = 1; i < R; ++i) {
            for (int j = 1; j < C; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    dp[i][j] = min(dp[i][j], min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
                }
            }
        }
        return dp[R - 1][C - 1];
    }
};

class Solution {
public:
    int minDistance(std::string word1, std::string word2) {
        int m = word1.size()+1;
        int n = word2.size()+1;
        int dp[m][n];
        
        for(int i=0; i<m; ++i) dp[i][0]=i;
        for(int j=0; j<n; ++j) dp[0][j]=j;
        
        for(int i=1; i<m; ++i) {
            for(int j=1; j<n; ++j) {
                dp[i][j] = std::min(std::min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+(word1[i-1]!=word2[j-1]?1:0));
            }
        }
        return dp[m-1][n-1];
    }
};

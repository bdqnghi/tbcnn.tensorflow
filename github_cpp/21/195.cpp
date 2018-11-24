//
// Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
//
//
//
// You have the following 3 operations permitted on a word:
//
//
//
// a) Insert a character
// b) Delete a character
// c) Replace a character
//


class Solution {
public:
    int minDistance(string word1, string word2) {
        int dp[word1.size()+1][word2.size()+1];
        int cost;
        dp[0][0]=0;
        for (int i=1; i<=word1.size(); i++) {
            dp[i][0]=i; 
        }
        for (int i=1; i<=word2.size(); i++) {
            dp[0][i]=i;
        }
        for (int i=1; i<=word1.size(); i++) {
            for (int j=1; j<=word2.size(); j++) {
                if (word1[i-1]==word2[j-1]) {
                    cost=0;
                }
                else {
                    cost=1;
                }
                dp[i][j]=min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]+cost);
            }
        }
        return dp[word1.size()][word2.size()];
    }
};

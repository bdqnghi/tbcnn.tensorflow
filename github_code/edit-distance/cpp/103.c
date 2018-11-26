class Solution {
public:    
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
    int minDistance(string word1, string word2) {
        // write your code here
        int m=word1.size();
        int n=word2.size();
        
        // new an array m+1 * n+1 size
        // dp[i][j] denotes the edit distance changing from
        // word1[0,i) to word2[0,j)
        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        
        for(int j=0; j<=n; j++){
            // from word1(len==0) to word2(len==j) add new element
            dp[0][j]=j;
        }
        
        for(int i=0; i<=m; i++){
            // from word1(len==i) to word2(len==0) delete element
            dp[i][0]=i;
        }
        
        
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(word1[i-1]==word2[j-1]){
                    dp[i][j]=dp[i-1][j-1];
                }else{
                    // select the min value of delete, add ro replace
                    dp[i][j]=min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
                }
            }
        }
        
        return dp[m][n];
    }
};

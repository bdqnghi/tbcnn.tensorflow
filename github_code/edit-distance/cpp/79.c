class Solution {
public:
    int minDistance(string word1, string word2) {
        int m=word1.size();
        int n=word2.size();
        
        // dp[i][j] means the min distance to change word1[0,i) to word2[0,j]
        vector<vector<int> > dp(m+1,vector<int>(n+1,0));
        dp[0][0]=0;
        //initial the first col and row
        for(int j=1; j<=n; j++){
            //insert new element to change to word2
            dp[0][j]=j;
        }
        for(int i=0; i<=m; i++){
            //delete from word1 element to change to empty word2
            dp[i][0]=i;
        }
        
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(word1[i-1]==word2[j-1]){
                    dp[i][j]=dp[i-1][j-1];
                }else{
                    //dp[i-1][j] means to delete word1[i]
                    //dp[i][j-1] means to add word2[j] 
                    //dp[i-1][j-1] means to replace word1[i] to word2[j]
                    dp[i][j]=min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
                }
            }
        }
        
        return dp[m][n];
    }
};
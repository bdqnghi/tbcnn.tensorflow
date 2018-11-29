/*
@Copyright:LintCode
@Author:   JamY
@Problem:  http://www.lintcode.com/problem/edit-distance
@Language: Java
@Datetime: 16-12-17 14:08
*/

public class Solution {
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
    public int minDistance(String word1, String word2) {
        // write your code here
        int n = word1.length();
        int m = word2.length();
        
        int[][] dp = new int[n+1][m+1];
        for(int i=0; i< m+1; i++){
            dp[0][i] = i; 
        }
        for(int i=0; i<n+1; i++){
            dp[i][0] = i;
        }
        
        
        for(int i = 1; i<n+1; i++){
            for(int j=1; j<m+1; j++){
                if(word1.charAt(i-1) == word2.charAt(j-1)){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = 1 + Math.min(dp[i-1][j-1],Math.min(dp[i-1][j],dp[i][j-1]));
                }
            }
        }
        return dp[n][m];
    }
}
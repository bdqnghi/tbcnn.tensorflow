/*
@Copyright:LintCode
@Author:   siyang
@Problem:  http://www.lintcode.com/problem/edit-distance
@Language: Java
@Datetime: 16-09-21 01:59
*/

public class Solution {
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
    public int minDistance(String word1, String word2) {
        // write your code here
        if(word1 == null && word2 == null)
            return 0;
        if(word1.length() == 0)
            return word2.length();
        if(word2.length() == 0)
            return word1.length();    
        //dp[i][j] min steps from A[i] to B[j]
        int [][] dp = new int [word1.length() + 1][word2.length() + 1];
        
        //init
        for(int i = 0 ; i <= word1.length(); i ++)
            dp[i][0] = i;
            
        for(int j = 0; j <= word2.length(); j ++)
            dp[0][j] = j;
        
        for(int i = 1 ; i <= word1.length(); i ++){
            for(int j = 1; j <= word2.length(); j ++){
                dp[i][j] = Math.min(dp[i - 1][j], dp[i][j - 1]) + 1;
                if(word1.charAt(i - 1) == word2.charAt(j - 1))
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - 1]);
                else
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
        
        return dp[word1.length()][word2.length()];
    }
}
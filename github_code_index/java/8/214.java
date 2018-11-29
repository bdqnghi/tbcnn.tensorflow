package ladders.USGiants.l9_DynamicProgramming.num119_EditDistance;

public class Solution_FromOther_BryanBCRevision {
    public int minDistance(String word1, String word2) {
        int len1 = word1.length();
        int len2 = word2.length();

        int[][] dp = new int[len1 + 1][len2 + 1];
        for (int i = 0; i < len2 + 1; i++) dp[0][i] = i;
        for (int i = 0; i < len1 + 1; i++) dp[i][0] = i;

        for (int i = 1; i < len1 + 1; i++){
            for (int j = 1; j < len2 + 1; j++){
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = 1 + Math.min(dp[i - 1][j - 1], Math.min(dp[i - 1][j], dp[i][j - 1]));
            }
        }
        return dp[len1][len2];
    }
}
//http://www.lintcode.com/en/problem/edit-distance/
/*
Edit Distance

 Description
 Notes
 Testcase
 Judge
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

Insert a character
Delete a character
Replace a character
Have you met this question in a real interview? Yes
Example
Given word1 = "mart" and word2 = "karma", return 3.
*/
//From http://www.jiuzhang.com/solutions/edit-distance/
//PractiedOn20170217Fri 5Times
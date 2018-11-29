/**
 * Created by Nazli on 2017-03-12.
 */

/*
* Question source: http://www.lintcode.com/en/problem/edit-distance/
* Solution source: http://www.programcreek.com/2013/12/edit-distance-in-java/
*                  http://www.jiuzhang.com/solutions/edit-distance/
*                  https://github.com/shawnfan/LintCode/blob/master/Java/Edit%20Distance.java
* */

/*
* Note: The 2-D array representing the operations that shows number of steps based on number of required operations
* Insert, replace and delete are 3 
* */
public class EditDistance {
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
        public int minDistance(String word1, String word2) {
        // write your code here
        int l1 = word1.length();
        int l2 = word2.length();


        int[][] dp = new int[l1+1][l2+1];

        for (int i = 0; i < l2+1; i++) {
            dp[0][i] = i;
        }
        for (int i = 0; i < l1+1; i++) {
            dp[i][0] = i;
        }

        for (int i = 1; i < l1+1; i++) {
            for (int j = 1; j < l2+1; j++) {
                if (word1.charAt(i-1) == word2.charAt(j-1)){
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    // for insert and delete
                    dp[i][j] = Math.min(dp[i-1][j-1], Math.min(dp[i-1][j], dp[i][j-1])) +1;
                }
            }
        }
        return dp[l1][l2];
    }
}

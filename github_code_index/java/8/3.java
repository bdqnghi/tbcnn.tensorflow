/*
@Copyright:LintCode
@Author:   LLihao
@Problem:  http://www.lintcode.com/problem/edit-distance
@Language: Java
@Datetime: 17-06-05 03:37
*/

public class Solution {
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
    public int minDistance(String word1, String word2) {
        int m = word1.length() + 1;
        int n = word2.length() + 1;
        int[][] edits = new int[m][n];
        for (int i = 0; i < m; ++i) {
            edits[i][0] = i;
        }
        for (int i = 0; i < n; ++i) {
            edits[0][i] = i;
        }
        
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    edits[i][j] = edits[i - 1][j - 1];
                } else {
                    int removeCharFromWord1 = edits[i - 1][j];
                    int removeCharFromWord2 = edits[i][j - 1];
                    int removeCharFromBoth = edits[i - 1][j - 1];
                    edits[i][j] = 1 + Math.min(removeCharFromBoth, Math.min(removeCharFromWord1, removeCharFromWord2));
                }
            }
        }
        return edits[m - 1][n - 1];
    }
}
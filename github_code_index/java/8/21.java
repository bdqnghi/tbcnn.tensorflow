public class Solution {
    /**
     * @param word1 & word2: Two string.
     * @return: The minimum number of steps.
     */
    public int minDistance(String word1, String word2) {
        // write your code here
        if (word1 == null || word2 == null) {
            return 0;
        }
        int m = word1.length();
        int n = word2.length();
        //state
        int[][] f = new int[m + 1][n + 1];
        //initial
        for (int i = 0; i <= m; i++) {
            f[i][0] = i;
        }
        for (int i = 0; i <= n; i++) {
            f[0][i] = i;
        }
        //function
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    f[i][j] = Math.min(f[i - 1][j - 1], Math.min(f[i - 1][j], f[i][j - 1]) + 1);
                } else {
                    f[i][j] = Math.min(f[i - 1][j - 1], Math.min(f[i - 1][j], f[i][j - 1])) + 1;
                }
            }
        }
        return f[m][n];
    }
}

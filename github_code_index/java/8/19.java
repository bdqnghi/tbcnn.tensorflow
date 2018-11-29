// Solution runs in O(n * m) time and uses O(n * m) space, where n and m are lengths of word1 and
// word2. This is the classic problem of edit distance, where you need to find the smallest number
// of edits (insert, delete, replace) to convert word1 into word2.
// Can be easily solved by dynamic programming (problem is described in Algorithm Design Manual).
class Solution {
  public int minDistance(String word1, String word2) {
    int n = word1.length(), m = word2.length();
    int[][] dp = new int[n + 1][m + 1];

    for (int i = 1; i <= n; i++) dp[i][0] = dp[i-1][0] + 1;
    for (int j = 1; j <= m; j++) dp[0][j] = dp[0][j-1] + 1;

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        dp[i][j] = Integer.MAX_VALUE;
        dp[i][j] = Math.min(dp[i][j], dp[i-1][j] + 1);
        dp[i][j] = Math.min(dp[i][j], dp[i][j-1] + 1);
        dp[i][j] = Math.min(dp[i][j], dp[i-1][j-1] + (word1.charAt(i-1) == word2.charAt(j-1) ? 0 : 1));
      }
    }
    return dp[n][m];
  }
}

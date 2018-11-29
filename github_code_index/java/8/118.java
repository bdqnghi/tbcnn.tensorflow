package edit_distance;

import org.junit.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class EditDistance {
  /*
      Edit Distance
      Leetcode #72
      https://leetcode.com/problems/edit-distance/
      Difficulty: Hard
   */
  public class Solution {
    public int minDistance(String word1, String word2) {
      if (word1 == null || word2 == null) return 0;
      if (word1 == null || word1.length() == 0) return word2.length();
      if (word2 == null || word2.length() == 0) return word1.length();

      int m = word1.length(), n = word2.length();
      int[][] dp = new int[m + 1][n + 1];
      for (int i = 0; i <= n; i++) dp[0][i] = i;

      for (int i = 1; i <= m; i++) {
        dp[i][0] = i;
        for (int j = 1; j <= n; j++) {
          dp[i][j] = Math.min(dp[i - 1][j], dp[i][j - 1]) + 1;
          if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
            dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - 1]);
          } else {
            dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - 1] + 1);
          }
        }
      }
      return dp[m][n];
    }
  }

  /*
      Edit Distance - In memory array
      Leetcode #72
      https://leetcode.com/problems/edit-distance/
      Difficulty: Hard
   */
  public class Solution_2 {
    public int minDistance(String word1, String word2) {
      if (word1 == null || word2 == null) return 0;
      if (word1 == null || word1.length() == 0) return word2.length();
      if (word2 == null || word2.length() == 0) return word1.length();
      int m = word1.length(), n = word2.length();

      int[] dp1 = new int[n + 1];
      for (int i = 0; i <= n; i++) dp1[i] = i;
      int[] dp2 = new int[n + 1];
      for (int i = 1; i <= m; i++) {
        dp2[0] = i;
        for (int j = 1; j <= n; j++) {
          dp2[j] = Math.min(dp2[j - 1], dp1[j]) + 1;
          if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
            dp2[j] = Math.min(dp2[j], dp1[j - 1]);
          } else {
            dp2[j] = Math.min(dp2[j], dp1[j - 1] + 1);
          }
        }
        for (int j = 0; j <= n; j++) dp1[j] = dp2[j];
      }

      return dp1[n];
    }
  }

  public static class UnitTest {
    @Test
    public void test1() {
      Solution sol = new EditDistance().new Solution();
      assertEquals(sol.minDistance("a", ""), 1);
      assertEquals(sol.minDistance("a", "bcd"), 3);
    }

    @Test
    public void test2() {
      Solution_2 sol2 = new EditDistance().new Solution_2();
      assertEquals(sol2.minDistance("a", ""), 1);
      assertEquals(sol2.minDistance("a", "bcd"), 3);
      assertEquals(sol2.minDistance("a", "bad"), 2);
    }
  }
}

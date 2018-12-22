package algorithm.DynamicProgramming;

/**
 * Given two words word1 and word2, find the minimum number of steps required to
 * convert word1 to word2. (each operation is counted as 1 step.)
 * 
 * http://www.lintcode.com/en/problem/edit-distance/
 * https://leetcode.com/problems/edit-distance/#/description
 * http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/
 * 
 *
 */
public class EditDistance {

	public int minDistance(String word1, String word2) {
		if (word1 == null || word2 == null) {
			return 0;
		}
		int n = word1.length();
		int m = word2.length();
		int[][] dp = new int[n + 1][m + 1];
		// initialize
		for (int i = 0; i <= n; i++) {
			dp[i][0] = i;
		}
		for (int i = 0; i <= m; i++) {
			dp[0][i] = i;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				//状态转移方程
				if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
					// dp[i][j] = Math.min(dp[i-1][j-1], 1+ Math.min(dp[i-1][j], dp[i][j-1]));
					dp[i][j] = dp[i - 1][j - 1]; // same as above
				} else {
					dp[i][j] = 1 + Math.min(dp[i - 1][j - 1], Math.min(dp[i - 1][j], dp[i][j - 1]));
				}
			}
		}

		return dp[n][m];
	}

	public static void main(String[] args) {

	}

}

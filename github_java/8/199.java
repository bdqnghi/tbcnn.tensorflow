// 72. Edit Distance
// DescriptionHintsSubmissionsDiscussSolution
// Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.
//
// You have the following 3 operations permitted on a word:
//
// Insert a character
// Delete a character
// Replace a character
// Example 1:
//
// Input: word1 = "horse", word2 = "ros"
// Output: 3
// Explanation:
// horse -> rorse (replace 'h' with 'r')
// rorse -> rose (remove 'r')
// rose -> ros (remove 'e')
// Example 2:
//
// Input: word1 = "intention", word2 = "execution"
// Output: 5
// Explanation:
// intention -> inention (remove 't')
// inention -> enention (replace 'i' with 'e')
// enention -> exention (replace 'n' with 'x')
// exention -> exection (replace 'n' with 'c')
// exection -> execution (insert 'u')


class Solution {
    public int minDistance(String word1, String word2) {
        if (word1 == null || word1.length() == 0) {
            return word2.length();
        }
        if (word2 == null || word2.length() == 0) {
            return word1.length();
        }
        if (word1.equals(word2)) {
            return 0;
        }

        // return mytry(word1, word2);

        // return method2(word1, word2);

        return method3(word1, word2);
    }

    private int method3(String w1, String w2) {
        // 其实没有太理解滚动数组的做法
        int n = w1.length();
        int m = w2.length();
        int[] f = new int[m + 1];
        for (int j = 0; j < m + 1; j++) {
            f[j] = j;
        }
        // DP
        for (int i = 1; i < n + 1; i++) {
            int[] curr = new int[m + 1];
            curr[0] = i;
            for (int j = 1; j < m + 1; j++) {
                if (w1.charAt(i - 1) == w2.charAt(j - 1)) {
                    curr[j] = f[j - 1];
                } else {
                    curr[j] = Math.min(f[j - 1], Math.min(f[j], curr[j - 1])) + 1;
                }
            }
            f = curr;
        }
        // result
        return f[m];
    }

    private int method2(String word1, String word2) {
        // iteration DP
        int n = word1.length();
        int m = word2.length();
        // definition: f[i][j] = min edit distance when word1 has i char left and word2 has j char left
        int[][] f = new int[n + 1][m + 1];
        // initialization
        for (int i = 0; i < n + 1; i++) {
            f[i][0] = i;
        }
        for (int j = 0; j < m + 1; j++) {
            f[0][j] = j;
        }
        // DP
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    f[i][j] = f[i - 1][j - 1];
                } else {
                    f[i][j] = Math.min(f[i - 1][j - 1], Math.min(f[i - 1][j], f[i][j - 1])) + 1;
                }
            }
        }
        // result
        return f[n][m];
    }

    private int mytry(String w1, String w2) {
        // recursion with memorization
        int n = w1.length();
        int m = w2.length();
        int[][] memo = new int[n + 1][m + 1];
        // initialization
        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < m + 1; j++) {
                memo[i][j] = -1;
            }
        }
        return recursion(memo, n, m, w1, w2);
    }
    private int recursion(int[][] memo, int i, int j, String w1, String w2) {
        if (i == 0 && j == 0) {
            return memo[i][j] = 0;
        }
        if (i == 0) {
            return memo[i][j] = j;
        }
        if (j == 0) {
            return memo[i][j] = i;
        }
        // pruning
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        // they have same char, cancel out
        if (w1.charAt(i - 1) == w2.charAt(j - 1)) {
            return memo[i][j] = recursion(memo, i - 1, j - 1, w1, w2);
        }
        // min{insert, insert, replace}, + 1 means this operation
        return memo[i][j] = Math.min(Math.min(recursion(memo, i - 1, j, w1, w2), recursion(memo, i, j - 1, w1, w2)), recursion(memo, i - 1, j - 1, w1, w2)) + 1;
    }
}

public class Solution {
    public int minDistance(String word1, String word2) {
        int m = word1.length();
        int n = word2.length();
        int[][] cost = new int[m + 1][n + 1];
        
        for (int i = 0; i <= m; i++) {
            cost[i][0] = i;
        }
        for (int i = 0; i <= n; i++) {
            cost[0][i] = i;
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (word1.charAt(i) == word2.charAt(j)) {
                    cost[i + 1][j + 1] = cost[i][j];
                } else {
                    int a = cost[i + 1][j] + 1;// insert?
                    int b = cost[i][j + 1] + 1;// delete?
                    int c = cost[i][j] + 1;
                    cost[i + 1][j + 1] = Math.min(a, Math.min(b, c));
                }
            }
        }
        return cost[m][n];
    }
}
// state:f[i][j] the min step take to change from word1 (0,i) to word2 (0,j)
// function:f[i][j] = f[i - 1][j - 1] if word1 at i equals to word2 at j
//          f[i][j] = min{a) b) c)}
// initialization: f[0][k] = f[k][0] = k
// answer: f[m][n]

public class Solution {
    public int minDistance(String word1, String word2) {
        int aLen = word1.length();
        int bLen = word2.length();
        if (aLen == 0 || bLen == 0) {
            return aLen == 0? bLen : aLen;
        }
        
        int[][] dist = new int[aLen + 1][bLen + 1];
        
        // initialize first row and col for empty string case.
        for (int i = 0; i <= aLen; i++) {
            dist[i][0] = i;
        }
        for (int j = 0; j <= bLen; j++) {
            dist[0][j] = j;
        }
        
        for (int i = 1; i <= aLen; i++) {
            for (int j = 1; j <= bLen; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dist[i][j] = dist[i - 1][j - 1];
                } else {
                    int insert = dist[i - 1][j] + 1;
                    int delete = dist[i][j - 1] + 1;
                    int replace = dist[i - 1][j - 1] + 1;
                    dist[i][j] = insert < delete? Math.min(replace, insert) : Math.min(replace, delete);
                }
            }
        }
        
        return dist[aLen][bLen];
    }
    
    
    public static int minDistance2(String word1, String word2) {
        // write your code here
        int aLen = word1.length();
        int bLen = word2.length();
        if (aLen == 0 || bLen == 0) {
            return aLen == 0? bLen : aLen;
        }

        int[][] dp = new int[aLen][bLen];
        // initialize first row and col
        dp[0][0] = word1.charAt(0) == word2.charAt(0)? 0 : 1;
        boolean singleMatch = false;
        for (int i = 1; i < aLen; i++) {
            if (word1.charAt(i) == word2.charAt(0)) {
                if (!singleMatch) {
                    singleMatch = true;
                    dp[i][0] = dp[i - 1][0];
                } else {
                    dp[i][0] = dp[i - 1][0] + 1;
                }
            } else {
                dp[i][0] = dp[i - 1][0] + 1;
            }
        }
        singleMatch = false;
        for (int j = 1; j < bLen; j++) {
            if (word2.charAt(j) == word1.charAt(0)) {
                if (!singleMatch) {
                    singleMatch = true;
                    dp[0][j] = dp[0][j - 1];
                } else {
                    dp[0][j] = dp[0][j - 1] + 1;
                }
            } else {
                dp[0][j] = dp[0][j - 1] + 1;
            }
        }

        for (int i = 1; i < aLen; i++) {
            for (int j = 1; j < bLen; j++) {
                int op1 = dp[i - 1][j - 1] + 1;
                int op2 = dp[i - 1][j] + 1;
                int op3 = dp[i][j - 1] + 1;
                int minOp = op1 < op2? Math.min(op1, op3) : Math.min(op2, op3);
                if (word1.charAt(i) == word2.charAt(j)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = minOp;
                }
            }
        }

        return dp[aLen - 1][bLen - 1];
    }
}
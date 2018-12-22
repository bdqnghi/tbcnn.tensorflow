public class Solution {
    public int minDistance(String word1, String word2) {
        int[][] dis = new int[word1.length() + 1][word2.length() + 1];
        for (int i = 1; i <= word2.length(); i++)
            dis[0][i] = i;
        for (int i = 1; i <= word1.length(); i++)
            dis[i][0] = i;
        for (int i = 1; i <= word1.length(); i++) {
            for (int j = 1; j <= word2.length(); j++) {
                // Insertion & deletion.
                dis[i][j] = Math.min(dis[i][j - 1], dis[i - 1][j]) + 1;
                // Do-nothing & replacement.
                if (word1.charAt(i - 1) == word2.charAt(j - 1))
                    dis[i][j] = Math.min(dis[i][j], dis[i - 1][j - 1]);
                else
                    dis[i][j] = Math.min(dis[i][j], dis[i - 1][j - 1] + 1);
            }
        }
        return dis[word1.length()][word2.length()];
    }
}

public class Solution {
    public int minDistance(String word1, String word2) {
        int len1 = word1.length();
        int len2 = word2.length();
        int[][] distance = new int[len1+1][len2+1];
        
        for (int i = 0; i <= len1; i++) {
            distance[i][0] = i;
        }
        for (int i = 0; i <= len2; i++) {
            distance[0][i] = i;
        }
        
        for (int i = 0; i < len1; i++) {
            for (int j = 0; j < len2; j++) {
                if (word1.charAt(i) == word2.charAt(j) ){
                    distance[i+1][j+1] = distance[i][j];
                } else {
                    int insert = distance[i][j+1] + 1;
                    int delete = distance[i+1][j] + 1;
                    int replace = distance[i][j] + 1;
                    int min = Math.min(insert, delete);
                    distance[i + 1][j + 1] = Math.min(min, replace);
                }
            } 
        }
        return distance[len1][len2];
    }
}
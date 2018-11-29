class Solution {
    public int minDistance(String word1, String word2) {
        int[][] editDistance = new int[word1.length()+1][word2.length()+1];
        for (int i = 0; i <= word1.length(); i++) {
            editDistance[i][0] = i;
        }
        for (int i = 0; i <= word2.length(); i++) {
            editDistance[0][i] = i;
        }
        for (int i = 1; i <= word1.length(); i++) {
            for (int j = 1; j <= word2.length(); j++) {
                editDistance[i][j] = editDistance[i-1][j-1];
                editDistance[i][j] += (word1.charAt(i-1) == word2.charAt(j-1)) ? 0 : 1;
                editDistance[i][j] = Math.min(editDistance[i][j], editDistance[i][j-1] + 1);
                editDistance[i][j] = Math.min(editDistance[i][j], editDistance[i-1][j] + 1);
            }
        }
        return editDistance[word1.length()][word2.length()];
    }
}

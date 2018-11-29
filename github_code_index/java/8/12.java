/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

public class Solution {
    public int minDistance(String word1, String word2) {
        // Start typing your Java solution below
        // DO NOT write main() function
        int len1 = word1.length();
        int len2 = word2.length();
        int[][] map = new int[len1][len2];
        if (len1 < 1)
            return len2;
        if (len2 < 1)
            return len1;
        map[0][0] = word1.charAt(0) == word2.charAt(0) ? 0 : 1;

        for(int i=1;i<len1;++i) {
            map[i][0] = word1.charAt(i) == word2.charAt(0) ? i : map[i - 1][0]+1;
        }

        // map[0][1...M-1]
        for(int i=1; i<len2; ++i) {
            map[0][i] = word1.charAt(0) == word2.charAt(i) ? i : map[0][i-1] + 1;
        }

        for(int i=1;i<len1;++i) {
            for(int j=1;j<len2;++j) {
                if (word1.charAt(i) == word2.charAt(j))
                    map[i][j] = map[i-1][j-1];
                else {
                    // find the min neighbor and add 1
                    int min = map[i-1][j-1] > map[i-1][j] ? map[i-1][j] : map[i-
                        1][j-1];
                    min = min > map[i][j-1] ? map[i][j-1] : min;
                    map[i][j]=min + 1;
                }
            }
        }
        return map[len1-1][len2-1];
    }
}

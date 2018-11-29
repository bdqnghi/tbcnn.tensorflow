/**
 Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2.
 (each operation is counted as 1 step.)

 You have the following 3 operations permitted on a word:

 a) Insert a character
 b) Delete a character
 c) Replace a character
 */
public class EditDistance {

    public static void main(String[] args) {
        EditDistance ed = new EditDistance();

        System.out.println(ed.minDistance("abcde", "abcdfg"));

        System.out.println(ed.minDistanceRollingArray("abcde", "abcdfg"));

    }

    public int minDistance(String word1, String word2) {
        char[] w1char = word1.toCharArray();
        char[] w2char = word2.toCharArray();

        int i, j;

        int m = w1char.length;
        int n = w2char.length;

        int[][] editDistance = new int[m + 1][n + 1];

        for (i = 0; i <= m; i++) {
            editDistance[i][0] = i;
        }

        for (j = 0; j <= n; j++) {
            editDistance[0][j] = j;
        }

        for (i = 1; i <= m; i++) {
            for (j = 1; j <= n; j++) {
                editDistance[i][j] = Math.min(editDistance[i - 1][j] + 1, editDistance[i][j - 1] + 1);
                editDistance[i][j] = Math.min(editDistance[i][j], editDistance[i - 1][j - 1] + 1);

                if (w1char[i - 1] == w2char[j - 1]) {
                    editDistance[i][j] = Math.min(editDistance[i][j], editDistance[i - 1][j - 1]);
                }
            }
        }

        return editDistance[m][n];
    }

    public int minDistanceRollingArray(String word1, String word2) {
        char[] w1char = word1.toCharArray();
        char[] w2char = word2.toCharArray();

        int i, j;

        int m = w1char.length;
        int n = w2char.length;

        int[] cur = new int[n + 1];
        int[] prev = new int[n + 1];

        for (j = 0; j <= n; j++) {
            prev[j] = j;
        }

        for (i = 1; i <= m; i++) {
            cur[0] = i;

            for (j = 1; j <= n; j++) {
                cur[j] = Math.min(cur[j - 1] + 1, prev[j] + 1);
                cur[j] = Math.min(cur[j], prev[j - 1] + 1);

                if (w1char[i - 1] == w2char[j - 1]) {
                    cur[j] = Math.min(prev[j - 1], cur[j]);
                }
            }
            prev = cur.clone();
        }

        return cur[n];
    }
}

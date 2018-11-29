/**
 * Levenshtein.java
 * 
 * Dynamic programming solution to the classic Change Making problem
 * More info: http://bitingcode.blogspot.com/2016/12/levenshtein-distance.html
 * 
 * @author manny egalli64@gmail.com
 */
package fun;

public class Levenshtein {
    private int[][] matrix;

    public Levenshtein(String from, String to) {
        matrix = new int[from.length() + 1][to.length() + 1];
        for (int i = 1; i < matrix[0].length; ++i) {
            matrix[0][i] = i;
        }
        for (int j = 1; j < matrix.length; ++j) {
            matrix[j][0] = j;
        }

        for (int i = 0; i < from.length(); i++) {
            for (int j = 0; j < to.length(); j++) {
                if (from.charAt(i) == to.charAt(j)) {
                    matrix[i + 1][j + 1] = matrix[i][j];
                } else {
                    int insert = matrix[i][j + 1] + 1;
                    int delete = matrix[i + 1][j] + 1;
                    int substitute = matrix[i][j] + 1;
                    matrix[i + 1][j + 1] = Math.min(Math.min(insert, delete), substitute);
                }
            }
        }
    }

    public int getDistance() {
        int i = matrix.length - 1;
        int j = matrix[i].length - 1;
        return matrix[i][j];
    }

    public boolean equals(int[][] expected) {
        if (expected == null || expected.length == 0)
            return false;
        if (matrix.length != expected.length)
            return false;

        for (int i = 0; i < matrix.length; ++i) {
            if (matrix[i].length != expected[i].length)
                return false;

            for (int j = 0; j < matrix[i].length; ++j) {
                if (matrix[i][j] != expected[i][j])
                    return false;
            }
        }

        return true;
    }
}

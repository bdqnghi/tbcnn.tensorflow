package de.up.ling.stud.automaton;

import java.util.Arrays;

/**
 * Computes the edit-distance between two Strings, based on the
 * Levenshtein-Distance. For further information, see
 * http://en.wikipedia.org/wiki/Levenshtein_distance or Jurafsky & Martin:
 * Introduction to Speech and Language Processing (2nd International Edition)
 * (pp. 108)
 *
 * @author Johannes Gontrum <gontrum@uni-potsdam.de>
 */
public class EditDistance {

    private int[][] matrix;
    private int current_n;
    private int current_m;
    private int m;   // len(u)
    private int n;   // len(v)

    /**
     * Initialize this calculator only once, so that the matrix, that is used
     * internally does not have to be created and destroyed after every word. It
     * will only be resized, if a new word is larger than the chart.
     */
    public EditDistance() {
        current_m = 0;
        current_n = 0;
        m = 20;
        n = 20;
        initializeMatrix();
    }

    /**
     * Calculate the EditDistance between two words.
     *
     * @param firstWord
     * @param secondWord
     * @return Editdistance
     */
    public int calcDistance(String firstWord, String secondWord) {
        String wordU = firstWord;
        String wordV = secondWord;
        m = firstWord.length();
        n = secondWord.length();


        initializeMatrix();

        // Iterate over rows and columns to calculate the value for each cell
        for (int x = 1; x < m + 1; ++x) {
            for (int y = 1; y < n + 1; ++y) {
                // Copy the value from the predecessor cell, if the letters match
                if (wordU.charAt(x - 1) == wordV.charAt(y - 1)) {
                    matrix[x][y] = matrix[x - 1][y - 1];
                } else {
                    // If not, compute values for possible deletion, insertion and substitution.
                    int deletion = matrix[x - 1][y] + 1;
                    int insertion = matrix[x][y - 1] + 1;
                    int substitution = matrix[x - 1][y - 1] + 1;

                    matrix[x][y] = min(deletion, insertion, substitution);
                }
            }
        }


        return matrix[m][n];
    }

    /**
     * Faster way to calculate the EditDistance between two words. Define the
     * length and offset for each word to avoid a lot of array copying.
     *
     * @param firstWord
     * @param firstOffset
     * @param firstLength
     * @param secondWord
     * @param secondOffset
     * @param secondLength
     * @return Editdistance
     */
    public int calcDistance(int[] firstWord, int firstOffset, int firstLength, int[] secondWord, int secondOffset, int secondLength) {
        m = firstLength;
        n = secondLength;

        assert m >= firstLength + firstOffset;
        assert n >= secondLength + secondOffset;

        initializeMatrix();

        // Iterate over rows and columns to calculate the value for each cell
        for (int x = 1; x < m + 1; ++x) {
            for (int y = 1; y < n + 1; ++y) {
                // Copy the value from the predecessor cell, if the letters match
                if (firstWord[x - 1 + firstOffset] == secondWord[y - 1 + secondOffset]) {
                    matrix[x][y] = matrix[x - 1][y - 1];
                } else {
                    // If not, compute values for possible deletion, insertion and substitution.
                    int deletion = matrix[x - 1][y] + 1;
                    int insertion = matrix[x][y - 1] + 1;
                    int substitution = matrix[x - 1][y - 1] + 1;

                    matrix[x][y] = min(deletion, insertion, substitution);
                }
            }
        }
//        System.err.println("w1 = " + Arrays.toString(firstWord) + "  \tw2 = " + Arrays.toString(secondWord) + " = " + matrix[m][n]);


        return matrix[m][n];
    }

    /**
     * Calculate the EditDistance between two words, but you have to make a new
     * copy of the words for every call.
     *
     * @param firstWord
     * @param secondWord
     * @return Editdistance
     */
    public int calcDistance(int[] firstWord, int[] secondWord) {
        m = firstWord.length;
        n = secondWord.length;


        initializeMatrix();

        // Iterate over rows and columns to calculate the value for each cell
        for (int x = 1; x < m + 1; ++x) {
            for (int y = 1; y < n + 1; ++y) {
                // Copy the value from the predecessor cell, if the letters match
                if (firstWord[x - 1] == secondWord[y - 1]) {
                    matrix[x][y] = matrix[x - 1][y - 1];
                } else {
                    // If not, compute values for possible deletion, insertion and substitution.
                    int deletion = matrix[x - 1][y] + 1;
                    int insertion = matrix[x][y - 1] + 1;
                    int substitution = matrix[x - 1][y - 1] + 1;

                    matrix[x][y] = min(deletion, insertion, substitution);
                }
            }
        }
//        System.err.println("w1 = " + Arrays.toString(firstWord) + "  \tw2 = " + Arrays.toString(secondWord) + " = " + matrix[m][n]);


        return matrix[m][n];
    }

    // Build the matrix and fill it with default values. TODO: A lot of time is spent here!
    private void initializeMatrix() {
        if (n > current_n || m > current_m) { //only change matrix size if needed.
            matrix = new int[m + 1][n + 1];
            // fill the first entry of each row with a number i, 0 < i < m+1
            for (int x = 0; x < m + 1; ++x) {
                matrix[x][0] = x;
            }
            // do the same with the columns
            for (int y = 0; y < n + 1; ++y) {
                matrix[0][y] = y;
            }
            current_n = n;
            current_m = m;
        }

    }

    // Returns a < b < c
    private static int min(int a, int b, int c) {
        return Math.min(a, Math.min(b, c));
    }

    // Returns a human readeble version of the matrix.
    private String matrixToString(String wordU, String wordV) {
        StringBuilder buf = new StringBuilder("  " + Arrays.toString(" ".concat(wordV).toCharArray()) + "\n");
        String word_u_buf = " ".concat(wordU);
        for (int x = 0; x < matrix.length; ++x) {
            buf.append(word_u_buf.charAt(x)).append(" ").append(Arrays.toString(matrix[x])).append("\n");
        }
        return buf.toString();
    }
}

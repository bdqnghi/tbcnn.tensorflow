package de.qaware.rat.common;

/**
 * The {@class LevenshteinDistance} class computes the similiarty of two
 * strings.
 * 
 * @author Matthias
 *
 */
public final class LevenshteinDistance {
    private LevenshteinDistance() {
    }

    private static int minimum(int a, int b, int c) {
        return Math.min(Math.min(a, b), c);
    }

    /**
     * Compute the Levenshtein distance.
     * 
     * @param lhs
     *            the left string to compare.
     * @param rhs
     *            the right string to compare.
     * @return the Levenshtein distance value.
     */
    public static int computeLevenshteinDistance(CharSequence lhs, CharSequence rhs) {
        int[][] distance = new int[lhs.length() + 1][rhs.length() + 1];

        for (int i = 0; i <= lhs.length(); i++) {
            distance[i][0] = i;
        }
        for (int j = 1; j <= rhs.length(); j++) {
            distance[0][j] = j;
        }

        for (int i = 1; i <= lhs.length(); i++) {
            for (int j = 1; j <= rhs.length(); j++) {
                distance[i][j] = minimum(distance[i - 1][j] + 1, distance[i][j - 1] + 1,
                        distance[i - 1][j - 1] + ((lhs.charAt(i - 1) == rhs.charAt(j - 1)) ? 0 : 1));
            }
        }

        return distance[lhs.length()][rhs.length()];
    }
}
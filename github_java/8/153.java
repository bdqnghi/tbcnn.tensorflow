package com.sleepycoders.jlib.algorithm.distance;

/**
 * Levenshtein Distance (edit distance)
 * @author Joshua Moody (joshimoo@hotmail.de)
 */
public final class LevenshteinDistance {
    private static final int DELETION_COST = 1;
    private static final int INSERTION_COST = 1;
    private static final int SUBSTITUTION_COST = 1;

    /**
     * Don't let anyone instantiate this class.
     */
    private LevenshteinDistance() {}

    /**
     * Calculates the cheapest cost to transform
     * string @param src to @param dst via deletions, insertions, substitutions
     * Uses the default cost of 1 for all operations
     * Runtime: O(src.length * dst.length)
     * Memory: O((src.length + 1) * (dst.length + 1))
     */
    public static int distance(String src, String dst) {
        return distance(src, dst, DELETION_COST, INSERTION_COST, SUBSTITUTION_COST);
    }

    /**
     * Calculates the cheapest cost to transform
     * string @param src to @param dst via deletions, insertions, substitutions
     * Uses the user specified cost factors for each operation
     * Runtime: O(src.length * dst.length)
     * Memory: O((src.length + 1) * (dst.length + 1))
     */
    public static int distance(String src, String dst, int deletionCost, int insertionCost, int substitutionConst) {
        // Null Strings, is the same as an empty string
        if (src == null) { src = ""; }
        if (dst == null) { dst = ""; }

        // for all i and j, d[i,j] will hold the Levenshtein distance between
        // the first i characters of s and the first j characters of t;
        // NOTE: d[length + 1][length + 1] => because 0 indexes are for mapping against empty strings
        int[][] d = new int[src.length() + 1][dst.length() + 1];

        // source prefixes can be transformed into empty string by dropping all characters
        // the distance of any first string to an empty second string
        for (int i = 0; i <= src.length(); i++) { d[i][0] = i; }

        // target prefixes can be reached from empty source prefix by inserting every character
        // the distance of any second string to an empty first string
        for (int j = 0; j <= dst.length(); j++) { d[0][j] = j; }

        // Now process both strings
        for (int j = 1; j <= dst.length(); j++) {
            for (int i = 1; i <= src.length(); i++) {

                // Same Char, therefore no operation is required
                // 0 cost --> same total cost as prev position
                // NOTE: transform into string (0-based index)
                if (src.charAt(i - 1) == dst.charAt(j - 1)) {
                    d[i][j] = d[i - 1][j - 1];
                } else {
                    // Find the cheapest operation
                    d[i][j] = min(
                            d[i - 1][j] + deletionCost,         // deletion
                            d[i][j - 1] + insertionCost,        // insertion
                            d[i - 1][j - 1] + substitutionConst // substitution
                    );
                }
            }
        }

        // The cheapest total cost is
        return d[src.length()][dst.length()];
    }

    /**
     * @return the minimum of a list of values
     */
    private static int min(int... a) {
        int min = a[0];
        for (int x : a) { if (x < min) { min = x; } }
        return min;
    }


    /**
     * Recursive LevenshteinDistance with exponential runtime
     * @deprecated use dynamic programming based approach
     * @return the minimum distance to transform string @param src into string @param dst
     */
    static int distanceRec(String src, String dst) {
        return distanceRec(src, src.length(), dst, dst.length());
    }

    /**
     * Recursive LevenshteinDistance with exponential runtime
     * @deprecated use dynamic programming based approach
     * @return the minimum distance to transform string @param src into @param dst
     */
    private static int distanceRec(String src, int srcLength, String dst, int dstLength) {
        // BaseCase: one string is empty
        if (srcLength == 0) { return dstLength; }
        if (dstLength == 0) { return srcLength; }

        // Does the current char match?
        int cost = src.charAt(srcLength - 1) != dst.charAt(dstLength - 1) ? SUBSTITUTION_COST : 0;

        // return minimum of delete char from src, delete char from dst, and delete char from both
        return min(
                distanceRec(src, srcLength - 1, dst, dstLength) + DELETION_COST,   // deletion
                distanceRec(src, srcLength, dst, dstLength - 1) + INSERTION_COST,  // insertion
                distanceRec(src, srcLength - 1, dst, dstLength - 1) + cost         // substitution
        );
    }
}

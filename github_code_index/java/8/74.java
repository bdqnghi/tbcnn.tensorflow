package edu.itu.the_d.map.dataprocessing;

import static java.lang.Math.abs;

/**
 * Class calculating the Levenshtein distance between two strings
 * <p>
 * Copyright 2016 The-D
 */
public class Levenshtein {
    //Set the maximum allowed Levenshtein distance between two strings
    private static final int MAX_ALLOWED_DISTANCE = 2;

    /**
     * Calculate the Levenshtein distance between two given strings
     * Some of this code is taken from: <a href="http://rosettacode.org/wiki/Levenshtein_distance#Java">RosettaCode</a>
     *
     * @param a of type String
     * @param b if type String
     * @return int
     * @see <a href="http://rosettacode.org/wiki/Levenshtein_distance#Java">http://rosettacode.org/wiki/Levenshtein_distance#Java</a>
     */
    public static int distance(String a, String b) {
        //If the difference in length between the two strings exceeds the max allowed Levenshtein distance then return.
        if (abs(a.length() - b.length()) > MAX_ALLOWED_DISTANCE) return MAX_ALLOWED_DISTANCE + 1;

        //Convert the strings to lower case
        a = a.toLowerCase();
        b = b.toLowerCase();

        int[] costs = new int[b.length() + 1];

        for (int j = 0; j < costs.length; j++) costs[j] = j;

        for (int i = 1; i <= a.length(); i++) {
            costs[0] = i;
            int nw = i - 1;
            for (int j = 1; j <= b.length(); j++) {
                int cj = Math.min(1 + Math.min(costs[j], costs[j - 1]), a.charAt(i - 1) == b.charAt(j - 1) ? nw : nw + 1);
                nw = costs[j];
                costs[j] = cj;
            }
        }

        return costs[b.length()];
    }

    /**
     * @param a String
     * @param b String
     * @return Returns a boolean indicating wether the levenshtein distance between two given strings exceeed the maximum allowed distance
     * or not
     */
    public static boolean isLevenshteinAllowed(String a, String b) {
        return distance(a, b) <= MAX_ALLOWED_DISTANCE;
    }

}

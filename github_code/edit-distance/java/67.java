package com.everything.strings.similarity;

import org.apache.commons.text.similarity.LevenshteinDistance;

/**
 * User: Makar Kalancha
 * Date: 01/01/2018
 * Time: 19:10
 */

class StringSimilarity {

    /**
     * Calculates the similarity (a number within 0 and 1) between two strings.
     */
    public static double similarity(String s1, String s2) {
        String longer = s1, shorter = s2;
        if (s1.length() < s2.length()) { // longer should always have greater length
            longer = s2; shorter = s1;
        }
        int longerLength = longer.length();
        if (longerLength == 0) { return 1.0; /* both strings are zero length */ }
        /* // If you have StringUtils, you can use it to calculate the edit distance:
        return (longerLength - StringUtils.getLevenshteinDistance(longer, shorter)) /
                                                             (double) longerLength; */
        return (longerLength - editDistance(longer, shorter)) / (double) longerLength;

    }

    // Example implementation of the Levenshtein Edit Distance
    // See http://r...content-available-to-author-only...e.org/wiki/Levenshtein_distance#Java
    public static int editDistance(String s1, String s2) {
        s1 = s1.toLowerCase();
        s2 = s2.toLowerCase();

        int[] costs = new int[s2.length() + 1];
        for (int i = 0; i <= s1.length(); i++) {
            int lastValue = i;
            for (int j = 0; j <= s2.length(); j++) {
                if (i == 0)
                    costs[j] = j;
                else {
                    if (j > 0) {
                        int newValue = costs[j - 1];
                        if (s1.charAt(i - 1) != s2.charAt(j - 1))
                            newValue = Math.min(Math.min(newValue, lastValue),
                                    costs[j]) + 1;
                        costs[j - 1] = lastValue;
                        lastValue = newValue;
                    }
                }
            }
            if (i > 0)
                costs[s2.length()] = lastValue;
        }
        return costs[s2.length()];
    }

    public static void printSimilarity(String s, String t) {
        System.out.println(String.format(
                "%.3f is the similarity between \"%s\" and \"%s\"", similarity(s, t), s, t));
    }

    public static void printLevenshteinDistanceSimilarity(LevenshteinDistance levenshteinDistance, String s, String t) {
        System.out.println(String.format(
                "%d\tis the similarity between \"%s\" and \"%s\"", levenshteinDistance.apply(s, t), s, t));
    }

    public static void main(String[] args) {
        long start = System.nanoTime();
        printSimilarity("", "");
        printSimilarity("1234567890", "1");
        printSimilarity("1234567890", "123");
        printSimilarity("1234567890", "1234567");
        printSimilarity("1234567890", "1234567890");
        printSimilarity("1234567890", "1234567980");
        printSimilarity("47/2010", "472010");
        printSimilarity("47/2010", "472011");
        printSimilarity("47/2010", "AB.CDEF");
        printSimilarity("47/2010", "4B.CDEFG");
        printSimilarity("47/2010", "AB.CDEFG");
        printSimilarity("The quick fox jumped", "The fox jumped");
        printSimilarity("The quick fox jumped", "The fox");
        printSimilarity("The quick fox jumped", "The quick fox jumped off the balcany");
        printSimilarity("kitten", "sitting");
        printSimilarity("Amazon", "Amazon.ca");
        printSimilarity("AMT", "ATM");
        long end = System.nanoTime();
        long duration = end - start;
        System.out.println("duration (nano sec): " + duration);

        start = System.nanoTime();
        LevenshteinDistance levenshteinDistance = new LevenshteinDistance();
        printLevenshteinDistanceSimilarity(levenshteinDistance, "", "");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "1234567890", "1");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "1234567890", "123");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "1234567890", "1234567");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "1234567890", "1234567890");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "1234567890", "1234567980");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "47/2010", "472010");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "47/2010", "472011");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "47/2010", "AB.CDEF");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "47/2010", "4B.CDEFG");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "47/2010", "AB.CDEFG");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "The quick fox jumped", "The fox jumped");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "The quick fox jumped", "The fox");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "The quick fox jumped", "The quick fox jumped off the balcany");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "kitten", "sitting");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "Amazon", "Amazon.ca");
        printLevenshteinDistanceSimilarity(levenshteinDistance, "AMT", "ATM");
        end = System.nanoTime();
        duration = end - start;
        System.out.println("duration (nano sec): " + duration);
    }

}

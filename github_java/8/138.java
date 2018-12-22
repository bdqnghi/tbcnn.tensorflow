package biz.a7software.slimmyinvoice.helper;

/**
 * The LevenshteinDistance class aims at computing the Levenshtein distance between two strings.
 * Source : http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance
 */
public class LevenshteinDistance {

    private static volatile LevenshteinDistance instance = null;

    private LevenshteinDistance() {
    }

    public final static LevenshteinDistance getInstance() {
        if (LevenshteinDistance.instance == null) {
            synchronized (LevenshteinDistance.class) {
                if (LevenshteinDistance.instance == null) {
                    LevenshteinDistance.instance = new LevenshteinDistance();
                }
            }
        }
        return LevenshteinDistance.instance;
    }

    // Minimum between 3 integers.
    private static int minimum(int a, int b, int c) {
        return Math.min(Math.min(a, b), c);
    }

    // Computes the Levenshtein Distance between two strings.
    public static int computeLevenshteinDistance(String str1, String str2) {
        int[][] distance = new int[str1.length() + 1][str2.length() + 1];

        for (int i = 0; i <= str1.length(); i++)
            distance[i][0] = i;
        for (int j = 1; j <= str2.length(); j++)
            distance[0][j] = j;

        for (int i = 1; i <= str1.length(); i++)
            for (int j = 1; j <= str2.length(); j++)
                distance[i][j] = minimum(
                        distance[i - 1][j] + 1,
                        distance[i][j - 1] + 1,
                        distance[i - 1][j - 1] + ((str1.charAt(i - 1) == str2.charAt(j - 1)) ? 0 : 1));

        return distance[str1.length()][str2.length()];
    }
}
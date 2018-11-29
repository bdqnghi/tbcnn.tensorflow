package de.reffle.jfsdict.levenshtein;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class LevenshteinDistance {
  private static int minimum(int... aInts) {
    int min = Integer.MAX_VALUE;
    for(int x : aInts) {
      min = Math.min(min, x);
    }
    return min;
  }

  public static int computeLevenshteinDistance(CharSequence lhs, CharSequence rhs) {
    int[][] distance = new int[lhs.length() + 1][rhs.length() + 1];

    for (int i = 0; i <= lhs.length(); i++)
      distance[i][0] = i;
    for (int j = 1; j <= rhs.length(); j++)
      distance[0][j] = j;

    for (int i = 1; i <= lhs.length(); i++) {
      for (int j = 1; j <= rhs.length(); j++) {
        int transpositionDistance = Integer.MAX_VALUE;
        if(i>=2 && j >=2 && lhs.charAt(i-1)==rhs.charAt(j-2) && lhs.charAt(i-2)==rhs.charAt(j-1)) {
          transpositionDistance = distance[i-2][j-2] + 1;
        }
        distance[i][j] = minimum(
            distance[i - 1][j] + 1,
            distance[i][j - 1] + 1,
            distance[i - 1][j - 1] + ((lhs.charAt(i - 1) == rhs.charAt(j - 1)) ? 0 : 1),
            transpositionDistance
            );
      }
    }
    return distance[lhs.length()][rhs.length()];
  }

  @Test
  public void test() throws Exception {
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "axc"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "xbc"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "abx"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "bc"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "ab"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "ac"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "acb"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "abxc"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "abcx"));
    assertEquals(1, LevenshteinDistance.computeLevenshteinDistance("abc", "xabc"));
}
}
package de.freiburg.iif.utils;

/**
 * The class StringSimilarity that provided methods to compare two string by
 * similarity.
 * 
 * @author Claudius Korzen
 * 
 */
public class StringSimilarity {
  /** The bonus points for a match in Smith Waterman */
  private static final float SMITH_WATERMAN_MATCH_BONUS = 2;
  /** The malus points for a mismatch in Smith Waterman */
  private static final float SMITH_WATERMAN_MISMATCH_MALUS = -1;

  /**
   * Computes the Levenshtein-distance between two given strings via dynamic
   * programming.
   * 
   * @param s1
   *          the first string to process.
   * @param s2
   *          the second string to process.
   * @return the Levenshtein-distance between the two given strings.
   */
  public static float levenshtein(String s1, String s2) {
    if (s1 != null && s2 != null) {
      s1 = s1.toLowerCase();
      s2 = s2.toLowerCase();

      char[] s1Chars = s1.toCharArray();
      char[] s2Chars = s2.toCharArray();

      int m = s1Chars.length;
      int n = s2Chars.length;

      // Initialize the matrix
      float[][] matrix = new float[m + 1][n + 1];
      for (int i = 0; i <= m; i++) {
        matrix[i][0] = i;
      }
      for (int j = 0; j <= n; j++) {
        matrix[0][j] = j;
      }

      for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
          if ((s1Chars[i - 1] != s2Chars[j - 1])) {
            float addCosts = matrix[i - 1][j] + 1;
            float deleteCosts = matrix[i][j - 1] + 1;
            float replaceCosts = matrix[i - 1][j - 1] + 1;

            matrix[i][j] = min(addCosts, deleteCosts, replaceCosts);
          } else {
            matrix[i][j] = matrix[i - 1][j - 1];
          }
        }
      }
      return matrix[m][n];
    }
    return -1;
  }

  /**
   * Computes the Smith Waterman similarity between two given strings via
   * dynamic programming.
   * 
   * @param s1
   *          the first string to process.
   * @param s2
   *          the second string to process.
   * @return the Smith Waterman-distance between the two given strings.
   */
  public static float[] smithWaterman(String s1, String s2) {
    float[] result = new float[3];

    // The easy case: length1 == 0 || length2 = 0;
    if (s1 == null && s2 == null) {
      result[0] = 0;
      result[1] = -1;
      result[2] = -1;
      return result;
    }

    s1 = s1 != null ? s1.toLowerCase() : "";
    s2 = s2 != null ? s2.toLowerCase() : "";

    char[] s1Chars = s1.toCharArray();
    char[] s2Chars = s2.toCharArray();

    int m = s1Chars.length;
    int n = s2Chars.length;

    // The easy case: length1 == 0 || length2 = 0;
    if (m == 0 || n == 0) {
      result[0] = 0;
      result[1] = -1;
      result[2] = -1;
      return result;
    }

    // Initialize the matrix
    float[][] matrix = new float[m + 1][n + 1];
    for (int i = 0; i < m + 1; i++) {
      matrix[i][0] = 0;
    }
    for (int j = 0; j < n + 1; j++) {
      matrix[0][j] = 0;
    }

    // Step 3: Fill the matrix by determining the minimum of the three values
    // for Replacement, Insertion and Deletion
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        // If chars are the same: costs = 2, otherwise: costs = -1;
        float costs =
            s1Chars[i - 1] == s2Chars[j - 1] ? SMITH_WATERMAN_MATCH_BONUS
                : SMITH_WATERMAN_MISMATCH_MALUS;

        float replaceCosts = matrix[i - 1][j - 1] + costs; // Replace
        float addCosts = matrix[i - 1][j] - 1; // insert
        float deleteCosts = matrix[i][j - 1] - 1; // delete

        // Determine Minimum of the three values
        matrix[i][j] =
            Math.max(Math.max(0, replaceCosts),
                Math.max(addCosts, deleteCosts));
        if (matrix[i][j] > result[0]) {
          result[0] = matrix[i][j];
          result[1] = i;
          result[2] = j;
        }
      }
    }

    // // Search for starts
    // int i = (int) result[2];
    // int j = (int) result[4];
    //
    // while (i >= 0 && j >= 0 && matrix[i][j] > 0) {
    // i--;
    // j--;
    // }
    // result[1] = i - 1;
    // result[3] = j - 1;

    // TODO: Which one to choose? (Title: first variant, Reference: second one).
    // return maxScore / (2 * Math.max(m, n));
    return result;
  }

  /**
   * Returns the maximum attainable smith waterman-score for the given text.
   * 
   * @param text
   *          the text to process.
   * @return the maximum attainable smith waterman-score for the given text.
   */
  public static float getMaxSmithWatermanScore(String text) {
    if (text != null) {
      return SMITH_WATERMAN_MATCH_BONUS * text.length();
    } else {
      return 0;
    }
  }

  /**
   * Returns the minimum of three given floats.
   * 
   * @param x
   *          the first floats.
   * @param y
   *          the second floats.
   * @param z
   *          the third floats.
   * @return the minimum of three given integers.
   */
  private static float min(float x, float y, float z) {
    return Math.min(x, Math.min(y, z));
  }
}

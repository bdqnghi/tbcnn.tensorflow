/*
 * Copyright 2013 Adrien Favre-Bully, Florian Froese, Adrian Schmidmeister
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 		http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

package ch.ethz.student.dejavu.strings;

import ch.ethz.student.dejavu.DistanceMetric;
import ch.ethz.student.dejavu.SimilarityMetric;
import ch.ethz.student.dejavu.utilities.Utilities;

/**
 * The Levenshtein distance between two strings is defined as the minimum number of edits needed to
 * transform one string into the other, with the allowable edit operations being insertion,
 * deletion, or substitution of a single character.
 *
 * For creation please use default LevenshteinDistance or the Builder {@link Builder}.
 *
 * <p>Wikipedia: <a href="http://en.wikipedia.org/wiki/Levenshtein_distance">http://en.wikipedia.org/wiki/Levenshtein_distance</a></p>
 *
 * @author Adrien Favre-Bully
 * @author Florian Froese
 * @author Adrian Schmidmeister
 * @since 1.0
 */
public class LevenshteinDistance implements DistanceMetric, SimilarityMetric {

  private static final double DEFAULT_INSERTION_WEIGHT = 1.0;
  private static final double DEFAULT_DELETION_WEIGHT = 1.0;
  private static final double DEFAULT_SUBSTITUTION_WEIGHT = 1.0;

  private double insertionWeight;
  private double deletionWeight;
  private double substitutionWeight;

  private LevenshteinDistance() {
  }

  // ===== Metric Methods  =====

  @Override
  public double computeSimilarity(String s1, String s2) {
    if (!Utilities.checkInputs(s1, s2)) {
      return Utilities.SIMILARITY_EMPTY_EMPTY;
    }

    double dist = computeDistance(s1, s2);

    return 1 - (dist / Utilities.max(s1.length(), s2.length()) / Utilities
        .min(substitutionWeight, insertionWeight + deletionWeight));
  }

  /**
   * @param s1 String, first string
   * @param s2 String, second string
   * @return double Levenshtein Distance between String s1 and s2
   */
  @Override
  public double computeDistance(String s1, String s2) {
    if (!Utilities.checkInputs(s1, s2)) {
      return Utilities.DISTANCE_EMPTY_EMPTY;
    }

    int I = s1.length();
    int J = s2.length();

    if (I == 0) {
      return (double) J;
    }
    if (J == 0) {
      return (double) I;
    }

    double distance[][] = new double[s1.length() + 1][s2.length() + 1];
    double deletionWeight = this.deletionWeight;
    double insertionWeight = this.insertionWeight;
    double substitutionWeight = this.substitutionWeight;
    double cost;

    // dynamic programming table initialization
    for (int i = 0; i <= I; i++) {
      distance[i][0] = i * insertionWeight;
    }
    for (int j = 0; j <= J; j++) {
      distance[0][j] = j * insertionWeight;
    }

    // dynamic programming loop
    for (int i = 1; i <= I; i++) {
      for (int j = 1; j <= J; j++) {
        cost = (s1.charAt(i - 1) != s2.charAt(j - 1)) ? substitutionWeight : 0;
        distance[i][j] = Utilities.min(
            distance[i - 1][j] + deletionWeight,
            distance[i][j - 1] + insertionWeight,
            distance[i - 1][j - 1] + cost
        );
      }
    }
    return distance[I][J];
  }

  // ===== Builder Methods =====


  /**
   * @return        {@link Builder}
   * @see Builder
   * @see LevenshteinDistance
   */
  public static Builder getBuilder() {
    return new Builder();
  }

  /**
   * @return A standard LevenshteinDistance object
   * @return        {@link LevenshteinDistance}
   * @see LevenshteinDistance
   */
  public static LevenshteinDistance getInstance() {
    return new Builder().build();
  }

  // ===== Builder Class =====

  /**
   * LevenshteinDistance Builder
   *
   * @author Adrien Favre-Bully
   * @author Florian Froese
   * @author Adrian Schmidmeister
   * @since 1.0
   */
  public static class Builder {

    private double bInsertionWeight;
    private double bDeletionWeight;
    private double bSubstitutionWeight;

    public Builder() {
      bInsertionWeight = DEFAULT_INSERTION_WEIGHT;
      bDeletionWeight = DEFAULT_DELETION_WEIGHT;
      bSubstitutionWeight = DEFAULT_SUBSTITUTION_WEIGHT;
    }

    public LevenshteinDistance build() {
      if (bInsertionWeight <= 0.0) {
        throw new IllegalArgumentException("The insertion weight must be positive.");
      }
      if (bDeletionWeight <= 0.0) {
        throw new IllegalArgumentException("The deletion weight must be positive.");
      }
      if (bSubstitutionWeight <= 0.0) {
        throw new IllegalArgumentException("The substitution weight must be positive.");
      }

      LevenshteinDistance d = new LevenshteinDistance();

      d.insertionWeight = bInsertionWeight;
      d.deletionWeight = bDeletionWeight;
      d.substitutionWeight = bSubstitutionWeight;

      return d;
    }

    /**
     * Insertion weight (must be positive)
     *
     * @param insertionWeight double
     * @return builder object
     */
    public Builder insertionScore(double insertionWeight) {
      bInsertionWeight = insertionWeight;
      return this;
    }

    /**
     * Deletion weight (must be positive)
     *
     * @param deletionWeight double
     * @return builder object
     */
    public Builder deletionScore(double deletionWeight) {
      bDeletionWeight = deletionWeight;
      return this;
    }

    /**
     * Substitution weight (must be positive)
     *
     * @param substitutionWeight double
     * @return builder object
     */
    public Builder substitutionScore(double substitutionWeight) {
      bSubstitutionWeight = substitutionWeight;
      return this;
    }
  }

}

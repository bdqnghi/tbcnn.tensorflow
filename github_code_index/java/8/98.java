package net.digitaltsunami.word.sequence;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

/**
 * Provides a set of utility methods related to edit distance.
 * 
 * @author dhagberg
 * 
 */
public class EditDistance {
    /**
     * Used to calculate edit distance using strategy. Distance will be
     * calculated by invoking
     * {@link EditDistanceCalculator#getEditDistance(String, String)}
     */
    private static AtomicReference<EditDistanceCalculator> defaultDistanceCalculator = new AtomicReference<EditDistanceCalculator>(
            new EditDistanceCalculator());

    /**
     * Reduce the provided collection of strings to list of strings within an
     * edit distance provided by the maxDistance parameter. Collection passed in
     * will not be modified. The results will be returned in a new collection.
     * 
     * @param candidates
     *            Collection of terms to compare against fromTerm
     * @param fromTerm
     *            Term from which the edit distance will be calculated.
     * @param maxDistance
     *            Maximum edit distance cutoff for matching candidates.
     * @return
     */
    public static Collection<String> getAllWithinDistance(Collection<String> candidates,
            String fromTerm, int maxDistance) {
        return getAllWithinDistance(candidates, fromTerm, maxDistance,
                defaultDistanceCalculator.get());
    }

    /**
     * Reduce the provided collection of strings to list of strings within an
     * edit distance provided by the maxDistance parameter. Collection passed in
     * will not be modified. The results will be returned in a new collection.
     * 
     * @param candidates
     *            Collection of terms to compare against fromTerm
     * @param fromTerm
     *            Term from which the edit distance will be calculated.
     * @param maxDistance
     *            Maximum edit distance cutoff for matching candidates.
     * @param distanceCalculator
     *            used to calculate edit distance using strategy. Distance will
     *            be calculated by invoking
     *            {@link EditDistanceCalculator#getEditDistance(String, String)}
     * @return
     */
    public static Collection<String> getAllWithinDistance(Collection<String> candidates,
            String fromTerm, int maxDistance, EditDistanceCalculator distanceCalculator) {

        List<WeightedString> withinDistance = new ArrayList<EditDistance.WeightedString>(
                candidates.size());
        /*
         * Add all terms within edit distance, storing the distance and term to
         * order the list after completion.
         */
        for (Iterator<String> iterator = candidates.iterator(); iterator.hasNext();) {
            String candidate = iterator.next();
            double editDistance = distanceCalculator.getEditDistance(fromTerm, candidate);
            if (editDistance <= maxDistance) {
                withinDistance.add(new WeightedString(editDistance, candidate));
            }
        }

        // Sort the qualified terms by edit distance.
        Collections.sort(withinDistance);
        /*
         * Copy the contents (term) of each WeightedString to a collection for
         * return. hold all returned terms to prevent unnecessary expansions.
         */
        ArrayList<String> allTerms = new ArrayList<String>(withinDistance.size());
        for (WeightedString ws : withinDistance) {
            allTerms.add(ws.string);
        }

        return allTerms;
    }

    /**
     * Testing method to dump out edit matrix.
     * 
     * @param fromTerm
     * @param toTerm
     * @param prefixLengths
     */
    private static void printEditMatrix(char[] fromTerm, char[] toTerm, int[][] prefixLengths) {
        System.out.printf("\n%3s", ""); // Print first Row
        System.out.printf("%2s", "0"); // Print 0 col hdr
        for (int c = 0; c < toTerm.length; c++) { // Print String 2
            System.out.printf("%3s", toTerm[c]);
        }
        System.out.printf("\n");
        System.out.printf("%2s", " 0"); // Print 0 row hdr
        for (int c = 0; c <= toTerm.length; c++) { // Print 0 for each column
            System.out.printf("|%2d", prefixLengths[0][c]);
        }
        for (int r = 1; r <= fromTerm.length; r++) {
            System.out.printf("\n%2s", fromTerm[r - 1]);
            for (int c = 0; c < toTerm.length + 1; c++) {
                System.out.printf("|%2d", prefixLengths[r][c]);
            }
        }
        System.out.println("");
    }

    /**
     * Set the {@link EditDistanceCalculator} used as the default when not
     * explicitly provided to methods within this class.
     * 
     * @param editDistanceCalculator
     */
    public static void setDefaultEditDistanceCalculator(
            EditDistanceCalculator editDistanceCalculator) {
        defaultDistanceCalculator.set(editDistanceCalculator);
    }

    /**
     * Temporary result storing string value and edit distance from primary
     * term.
     * 
     */
    private static class WeightedString implements Comparable<WeightedString> {
        final double weight;
        final String string;

        private WeightedString(double weight, String string) {
            this.weight = weight;
            this.string = string;
        }

        @Override
        public int compareTo(WeightedString o) {
            long delta = Double.doubleToLongBits(weight) - Double.doubleToLongBits(o.weight);
            if (delta == 0) {
                return this.string.compareTo(o.string);
            } else {
                return delta > 0 ? 1 : -1;
            }
        }

        /*
         * (non-Javadoc)
         * 
         * @see java.lang.Object#hashCode()
         */
        @Override
        public int hashCode() {
            final int prime = 31;
            int result = 1;
            result = prime * result + ((string == null) ? 0 : string.hashCode());
            long temp;
            temp = Double.doubleToLongBits(weight);
            result = prime * result + (int) (temp ^ (temp >>> 32));
            return result;
        }

        /*
         * (non-Javadoc)
         * 
         * @see java.lang.Object#equals(java.lang.Object)
         */
        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;
            if (obj == null)
                return false;
            if (getClass() != obj.getClass())
                return false;
            WeightedString other = (WeightedString) obj;
            if (string == null) {
                if (other.string != null)
                    return false;
            } else if (!string.equals(other.string))
                return false;
            if (Double.doubleToLongBits(weight) != Double.doubleToLongBits(other.weight))
                return false;
            return true;
        }
    }
}

/*******************************************************
 * See: Rod-cutting problem (p. 360)
 * Introduction to Algorithms, Third Edition (Cormen)
 *
 * Given a rod of length n, and an array of prices,
 * lengthPrices[i], where i = 1, 2, .., n determine
 * the maximum revenue obtainable by cutting up the rod
 * and selling the pieces.
 *
 * A recursive and dynamic programming solution is
 * implemented.
 *
 * Last Revised: 25 Jan 2015
 * Tarif Haque
 *******************************************************/

public class RodCutting {

    /**************************************
     * The (tree) recursive approach.
     * It is sad how inefficient this is...
     **************************************/
    public static int recursivelyCutRod(int[] lengthPrices, int rodLength) {

        if (rodLength == 0) return 0;

        int[] solutions = new int[(rodLength / 2) + 1];
        solutions[0] = lengthPrices[rodLength];

        for (int i = 1; i < solutions.length; i++) {
            solutions[i] = recursivelyCutRod(lengthPrices, i) + recursivelyCutRod(lengthPrices, rodLength - i);
        }

        return max(solutions);
    }

    /*********************************************************
     * My twist on the bottom-up strategy....
     * Such elegance.. such efficiency...
     *
     * revenues[i] for i = 1 ... rodLength stores the max
     * revenue for a rod of length i
     *********************************************************/
    public static int cutRod(int[] lengthPrices, int rodLength) {

        // assume a rodLength of 0 costs nothing
        if (rodLength == 0) return 0;

        int[] revenues = new int[rodLength + 1];

        for (int n = 1; n < revenues.length; n++) {
            int[] solutions = new int[(n / 2) + 1];
            solutions[0] = lengthPrices[n];

            for (int i = 1; i < solutions.length; i++) {
                solutions[i] = revenues[i] + revenues[n - i];
            }

            revenues[n] = max(solutions);
        }

        return revenues[rodLength];
    }

    /**************************************************
     * I'm getting too old for writing trivial methods
     * that should be built in...
     **************************************************/
    private static int max(int[] array) {
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < array.length; i++) {
            if (array[i] > max) max = array[i];
        }
        return max;
    }

}

package com.anuragkapur.misc;

import java.util.HashMap;
import java.util.Map;

/**
 * Problem Statement:
 *
 * Given a rod of length n inches and a table of prices pi for i = 1,2,...,n, determine the maximum revenue rn
 * obtainable by cutting up the rod and selling the pieces. Note that if the price pn for a rod of length n is large
 * enough, an optimal solution may require no cutting at all.
 *
 * @author anuragkapur
 */
public class RodCutting {

    /**
     * Simple recursive approach to find the max price
     *
     * Run time complexity: O(2^n) ; tries all possible cut permutations
     *
     * @param p
     * @param n
     * @return
     */
    public int cutRodToMaximisePrice1(int p[], int n) {

        if (n == 0) {
            return 0;
        }

        // a simple sysout to show that sub-problems are re-evaluated and hence there is scope for improvement in this
        // algorithm.
        System.out.println("n="+n);

        int maxPrice = Integer.MIN_VALUE;
        for (int i=0; i<n; i++) {
            maxPrice = Math.max(maxPrice, p[i]+cutRodToMaximisePrice1(p, n-i-1));
        }

        return maxPrice;
    }

    /**
     * Top down with memoization
     *
     * Run time complexity: O(n^2)
     *
     * @param p
     * @param n
     * @return
     */
    public int cutRodToMaximisePrice2(int p[], int n, Map<Integer, Integer> memoizedResults) {

        // recursion base case
        if (n == 0) {
            return 0;
        }

        // one time init for memoization
        if (memoizedResults == null) {
            System.out.println("Memoized results store init");
            memoizedResults = new HashMap<>();
        }

        if (memoizedResults.containsKey(n)) {
            return memoizedResults.get(n);
        }

        System.out.println("n="+n);

        int maxPrice = Integer.MIN_VALUE;
        for (int i=0; i<n; i++) {
            maxPrice = Math.max(maxPrice, p[i]+cutRodToMaximisePrice2(p, n-i-1, memoizedResults));
        }

        memoizedResults.put(n, maxPrice);

        return maxPrice;
    }
}

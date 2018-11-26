package net.geekscore.algo.dynamic;

import java.time.Duration;
import java.time.Instant;
import java.util.Arrays;

/**
 *
 * Finding an optimal solution requires solutions to multiple subproblems
 *
 * Find best way to cut a rod of length n
 *
 * Given: rod of length n
 * Assume that each length rod has a price pi
 * Find best set of cuts to get maximum price
 *      Each cut is integer length
 *      Can use any number of cuts, from 0 to n−1
 *      No cost for a cut
 *
 * Example:
 * Rod lengths and values
 * length i	1	2	3	4	5	6	7	8   9   10
 * price pi	1	5	8	9	10	17	17	20  24  30
 *
 * Which one provides the maximum revenue r(4)?
 * 4 rods of size 1 (achieved by 3 cuts) = 4 x p(1) = 4 x 1 = 4
 * 2 rods of size 1 + 1 rod of size 2 (achieved by 2 cuts) = 2 x p(1) + 1 x p(2) = 2 x 1 + 5 = 7
 * 2 rods of size 2 (achieved by 1 cut)= 2 x p(2) = 2 x 5 = 10
 * 1 rod of size 1 + 1 rod of size 3 (achieved by 2 cuts)= 1 x p(1) + 1 x p(3) = 1 + 8= 9
 * original rod of size 4 (achieved by no cuts)= 1 x p(4) = 9
 *
 * Best: two 2-inch pieces = revenue of p2+p2=5+5=10
 *
 */
public class RodCutting {

    public static void main(String[] args) {

        System.out.println("---------------");
        Instant start = Instant.now();
        System.out.println(cutRod(new int[]{1,5,8,9,10,17,17,20,24,30}, 4)); // 10
        System.out.println(cutRod(new int[]{1,5,8,9,10,17,17,20,24,30}, 6)); // 17
        System.out.println(cutRod(new int[]{1,5,8,9,10,17,17,20,24,30}, 8)); // 22
        System.out.println(Duration.between(start, Instant.now()).toNanos());

        System.out.println("---------------");
        start = Instant.now();
        System.out.println(cutRodMemoize(new int[]{1,5,8,9,10,17,17,20,24,30}, 4)); // 10
        System.out.println(cutRodMemoize(new int[]{1,5,8,9,10,17,17,20,24,30}, 6)); // 17
        System.out.println(cutRodMemoize(new int[]{1,5,8,9,10,17,17,20,24,30}, 8)); // 22
        System.out.println(Duration.between(start, Instant.now()).toNanos());

        System.out.println("---------------");
        start = Instant.now();
        System.out.println(cutRodBottomUp(new int[]{1,5,8,9,10,17,17,20,24,30}, 4)); // 10
        System.out.println(cutRodBottomUp(new int[]{1,5,8,9,10,17,17,20,24,30}, 6)); // 17
        System.out.println(cutRodBottomUp(new int[]{1,5,8,9,10,17,17,20,24,30}, 8)); // 22
        System.out.println(Duration.between(start, Instant.now()).toNanos());

    }

    private static final int cutRod(int[] prices, int n) {
        if(n==0) return 0;
        int max = Integer.MIN_VALUE;
        for (int i = 1; i <= n; i++) {
            max = Math.max(max, prices[i-1]+ cutRod(prices, n-i));
        }
        return max;
    }

    private static final int cutRodMemoize(int[] prices, int n) {
        final int[] maxPrice = new int[prices.length+1];
        Arrays.fill(maxPrice, -1);
        maxPrice[0] = 0;
        return cutRodMemoizeHelper(prices, n, maxPrice);
    }

    private static final int cutRodMemoizeHelper(int[] prices, int n, int[] maxPrice) {
        if(maxPrice[n] != -1) return maxPrice[n];
        int max = Integer.MIN_VALUE;
        for (int i = 1; i <= n; i++) {
            max = Math.max(max, prices[i-1] + cutRodMemoizeHelper(prices, n-i, maxPrice));
        }
        maxPrice[n] = max;
        return max;
    }

    private static final int cutRodBottomUp(int[] prices, int n) {
        final int[] maxPrice = new int[prices.length+1];
        Arrays.fill(maxPrice, -1);
        maxPrice[0] = 0;
        for (int len = 1; len <= n; len++) {
            int max = Integer.MIN_VALUE;
            for (int l = 1; l <= len; l++) {
                max = Math.max(max, prices[l-1]+ maxPrice[len-l]);
            }
            maxPrice[len] = max;
        }
        return maxPrice[n];
    }
}

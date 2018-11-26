package dp;/* Authored by Kushagra on 2/10/2016. */

public class RodCuttingDemo {

    public static void main(String[] args) {
        int[] prices = {1, 5, 8, 9, 10, 17, 17, 20};
        System.out.println(cutRod(prices, prices.length));
    }

    // n! time algorithm
    private static int cutRod(int[] prices, int n) {

        if (n <= 0) return 0;
        int maxPrice = Integer.MIN_VALUE;

        for (int i = 0; i < n; i++) {
            maxPrice = Math.max(maxPrice, prices[i] + cutRod(prices, n - i - 1));
        }

        return maxPrice;
    }

    // quadratic time algorithm
    private static int cutRod(int[] P) {

        int n = P.length;
        int[] maxCost = new int[n + 1]; // justify why n + 1
        maxCost[0] = 0;

        int maxVal;

        // Bottom up DP
        for (int i=1; i<=n; i++) {
            maxVal = Integer.MIN_VALUE;
            for (int j=0; j<i; j++) {
                maxVal = Math.max(maxVal, P[j] + maxCost[i-j-1]);
            }
            maxCost[i] = maxVal;
        }

        return maxCost[n];
    }

}

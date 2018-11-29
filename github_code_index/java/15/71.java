package dp;

import java.util.Map;

/**
 * Question: http://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/
 * Solution: https://www.youtube.com/watch?v=IRwVmTmN6go
 */
public class RodCutting {
    public int maxProfit(Map<Integer, Integer> costsMap, int n) {
        int[] memo = new int[n + 1];

        for (int i = 1; i < memo.length; i++) memo[i] = costsMap.getOrDefault(i, 0);

        for (int i = 2; i <= n; i++) {
            int max = 0;
            for (int j = 1; j <= i; j++) {
                max = Math.max(max, memo[j] + memo[i - j]);
            }
            memo[i] = max;
        }

        return memo[n];
    }


    public int maxProfitTopDown(Map<Integer, Integer> costsMap, int n) {
        int[] memo = new int[n + 1];
        for (int i = 1; i < memo.length; i++) memo[i] = -1;
        return maxProfitTopDown(costsMap, n, memo);
    }

    private int maxProfitTopDown(Map<Integer, Integer> costsMap, int n, int[] memo) {
        if (n <= 0) return 0;
        if (memo[n] == -1) {
            int max = 0;
            for (int i = 1; i <= n; i++) {
                max = Math.max(max, costsMap.getOrDefault(i, 0) + maxProfitTopDown(costsMap, n - i, memo));
            }
            memo[n] = max;
        }

        return memo[n];
    }
}

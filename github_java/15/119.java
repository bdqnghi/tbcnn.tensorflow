package edu.neu.dp;

import java.util.ArrayList;
import java.util.List;

/*
    Given a rod of length n inches and a table of prices pi for i = 1, 2, ..., n,
    determine the maximum revenue rn obtainable by cutting up the rod and selling
    the pieces.
 */

/*
    1. Optimal substructure:
       Let n be the rod length and {x1,x2,...,xm} be lengths of cut rods in the optimal solution.
        {x1,x2,...,xm-1} must be the optimal solution for a rod of length n-xm
    2. Recursive solution:
       Define dp[i] to be the maximum revenue for cutting a rod of i length.
       dp[i] = |- 0                      if i = 0
               |- max(dp[j] + P[i-j])    for 0<=j<=i if i>0
 */
public class RodCutting {
    public static void main(String[] args) {
        RodCutting r = new RodCutting();
        int[] prices = new int[]{1, 5, 8, 9, 10, 17, 17, 20};
        int n = prices.length;
        int[] dp = r.solve(prices, n);
        System.out.println("The maximum revenue for cutting the rod is: " + dp[n]);
        r.printRodLen(dp, prices, n);
    }

    public int[] solve(int[] prices, int n) {
        int[] dp = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (i - j - 1 < prices.length) {
                    dp[i] = Math.max(dp[j] + prices[i - j - 1], dp[i]);
                }
            }
        }
        return dp;
    }

    private void printRodLen(int[] dp, int[] prices, int n) {
        List<Integer> rodLen = new ArrayList<>();
        int revenue = dp[n];
        for (int i = n; i >= 0 && revenue > 0; ) {
            for (int j = i - 1; j >= 0; j--) {
                if (revenue - prices[i - j - 1] == dp[j]) {
                    rodLen.add(i - j);
                    revenue -= prices[i - j - 1];
                    i = j;
                    break;
                }
            }
        }

        System.out.print("The cut rod lengths are: ");
        for (Integer i : rodLen) {
            System.out.print(i + " ");
        }
    }
}

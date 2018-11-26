package leetcode;

import java.io.BufferedInputStream;
import java.util.Scanner;

/**
 Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n.
 Determine the maximum value obtainable by cutting up the rod and selling the pieces. For example,
 if length of the rod is 8 and the values of different pieces are given as following,
 then the maximum obtainable value is 22 (by cutting in two pieces of lengths 2 and 6)


 length   | 1   2   3   4   5   6   7   8
 --------------------------------------------
 price    | 1   5   8   9  10  17  17  20
 And if the prices are as following, then the maximum obtainable value is 24 (by cutting in eight pieces of length 1)

 length   | 1   2   3   4   5   6   7   8
 --------------------------------------------
 price    | 3   5   8   9  10  17  17  20


 geeksforgeeks:https://practice.geeksforgeeks.org/problems/rod-cutting/0
 * */
public class CuttingRod {


    public static void main(String[] args) {
        Scanner scanner = new Scanner(new BufferedInputStream(System.in));

        int testCase = scanner.nextInt();
        for(int i = 0; i < testCase; i++) {
            int[] price = new int[scanner.nextInt()];
            scanner.nextLine();
            String[] input = scanner.nextLine().split(" ");
            for(int j = 0; j < input.length; j++) { price[j] = Integer.parseInt(input[j]); }

            System.out.println(cuttingRod(price));
        }
    }

    /**
     * Complete package problem
     * cutRod(n) = max(prices[i] + cutRod(n-i-1)) for all i in {0, 1 .. n-1}
     * */
    private static int cuttingRod(int[] prices) {
        final int length = prices.length;
        int[] dp = new int[length + 1];

        for(int cost = 1; cost <= length; cost++) {
            for(int price = prices[cost - 1], c = cost; c <= length; c++) {
                dp[c] = Math.max(dp[c], dp[c - cost] + price);
            }
        }

        return dp[length];
    }
}

package dtprogrammer.github.io.other.dynamicprogramming;

import java.util.Arrays;
import java.util.Scanner;

/**
 * Rod Cutting Problem
 * Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n.
 * Determine the maximum value obtainable by cutting up the rod and selling the pieces.
 * <p>
 * Input:
 * First line consists of T test cases. First line of every test case consists of N, denoting the size of array.
 * Second line of every test case consists of price of ith length piece.
 * <p>
 * Output:
 * Single line output consists of maximum price obtained.
 * <p>
 * Constraints:
 * 1<=T<=100
 * 1<=N<=100
 * 1<=Ai<=100
 * <p>
 * Example:
 * Input:
 * 1
 * 8
 * 1 5 8 9 10 17 17 20
 * Output:
 * 22
 * Problem: http://practice.geeksforgeeks.org/problems/rod-cutting/0
 * The brute force approach has exponential time complexity in which we generate all the possibilities
 * of cutting which is 2 pow (n - 1) hence has exponential time complexity. We can reduce this by dynamic programming.
 * Time complexity:
 */
public class RodCutting {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numTestCaases = scanner.nextInt();
        for (int testCounter = 0; testCounter < numTestCaases; testCounter++) {
            int n = scanner.nextInt();
            int[] p = new int[n];
            for (int i = 0; i < n; i++) {
                p[i] = scanner.nextInt();
            }

            int[] memo = new int[p.length];
            Arrays.fill(memo, Integer.MIN_VALUE);

            System.out.println(curRod(n, p, memo));
        }

    }

    private static int curRod(int n, int[] p, int[] memo) {
        if (n == 0) {
            return 0;
        }
        if (memo[n - 1] >= 0) {
            return memo[n - 1];
        }
        int q = Integer.MIN_VALUE;
        for (int i = 1; i <= n; i++) {
            q = Math.max(q, p[i - 1] + curRod(n - i, p, memo));
        }
        memo[n - 1] = q;
        return q;
    }
}

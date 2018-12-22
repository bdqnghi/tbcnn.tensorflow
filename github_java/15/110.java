/*
 * Title: Rod Cutting
 * Author: Sam Gavis-Hughson
 * Date: 11/30/2017
 * 
 * Given a rod of a certain length and a list of prices for different length
 * rods, determine the best way to cut the rod to get the greatest price. You
 * can assume that you have prices for any length from 1 to the length of the 
 * rod.
 * 
 * eg. 
 * prices = {1, 5, 8, 9, 10}
 * (prices[i] = price for length i+1, ie. prices[0] = price for length 1)
 * 
 * rodCutting(prices, 4) = 10 (5 + 5)
 * rodCutting(prices, 5) = 13 (8 + 5)
 * 
 * Execution: javac RodCutting.java && java RodCutting 
 */

public class RodCutting {
    
    // Brute force solution. Recursively try every combination of different 
    // lengths to see which is the most valuable
    public static int bruteForceRodCutting(int[] prices, int length) {
        if (length == 0) return 0;
        
        int maxValue = 0;
        for (int i = 1; i <= length; i++) {
            maxValue = Math.max(maxValue, prices[i-1] + bruteForceRodCutting(prices, length - i));
        }
        return maxValue;
    }
    
    // Top-down dynamic solution
    public static int topDownRodCutting(int[] prices, int length) {
        int[] dp = new int[length + 1];
        return topDownRodCutting(prices, length, dp);
    }
    
    // Overloaded recursive method
    private static int topDownRodCutting(int[] prices, int length, int[] dp) {
        if (length == 0) return 0;
        if (dp[length] == 0) {
            int maxValue = 0;
            for (int i = 1; i <= length; i++) {
                maxValue = Math.max(maxValue, prices[i-1] + topDownRodCutting(prices, length - i, dp)); 
            }
            dp[length] = maxValue;
        }
        return dp[length];
    }
    
    // Bottom-up dynamic solution
    public static int bottomUpRodCutting(int[] prices, int length) {
        int[] dp = new int[length + 1];
        for (int i = 1; i < dp.length; i++) {
            int maxValue = 0;
            for (int j = 0; j < i; j++) {
                maxValue = Math.max(maxValue, prices[i - j - 1] + dp[j]);
            }
            dp[i] = maxValue;
        }
        return dp[length];
    }
    
    // Sample testcases
    public static void main(String[] args) {
        (new TestCase(new int[]{}, 0, 0)).run();
        (new TestCase(new int[]{1, 5, 8, 9, 10, 10}, 1, 1)).run();
        (new TestCase(new int[]{1, 5, 8, 9, 10, 10}, 4, 10)).run();
        (new TestCase(new int[]{1, 5, 8, 9, 10, 10}, 5, 13)).run();
        System.out.println("Passed all test cases");
    }
    
    // Class for defining and running test cases
    private static class TestCase {
        private int[] prices;
        private int length;
        private int output;
        
        private TestCase(int[] prices, int length, int output) {
            this.prices = prices;
            this.length = length;
            this.output = output;
        }
        
        private void run() {
            assert bruteForceRodCutting(prices, length) == output:
                "bruteForceRodCutting failed for length = " + length;
            assert topDownRodCutting(prices, length) == output:
                "topDownRodCutting failed for length = " + length;
            assert bottomUpRodCutting(prices, length) == output:
                "bottomUpRodCutting failed for length = " + length;
        }
    }
}
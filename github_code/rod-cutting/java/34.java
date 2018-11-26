package DynamicProblem.dp;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by liju on 6/30/16.
 *
 * Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n.
 * Determine the maximum value obtainable by cutting up the rod and selling the pieces.
 * For example, if length of the rod is 8 and the values of different pieces are given as following,
 * then the maximum obtainable value is 22 (by cutting in two pieces of lengths 2 and 6)
 *
 * length   | 1   2   3   4   5   6   7   8
   --------------------------------------------
   price    | 1   5   8   9  10  17  17  20

 And if the prices are as following, then the maximum obtainable value is 24 (by cutting in eight pieces of length 1)

 length   | 1   2   3   4   5   6   7   8
 --------------------------------------------
 price    | 3   5   8   9  10  17  17  20
 *
 *
 * Ref - http://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/
 */
public class CuttingRod {

    public int maxProfit(int len[], int price[], int remainingLenOfRod) {
        if (remainingLenOfRod <= 0) {
            return 0;
        }

        int max = Integer.MIN_VALUE;
        for (int i = 0; i < len.length; i++) {

            if (remainingLenOfRod >= len[i]) {
                int val = price[i] + maxProfit(len, price, remainingLenOfRod - len[i]);
                if (val > max) {
                    max = val;
                }
            }
        }
        return max;
    }

    // using memoization - dp

    public int maxProfitDP(int len[], int price[], int remainingLenOfRod, Map<Integer, Integer> lookup) {
        if (remainingLenOfRod <= 0) {
            return 0;
        }

        if (lookup.get(remainingLenOfRod) == null) {
            int max = Integer.MIN_VALUE;
            for (int i = 0; i < len.length; i++) {

                if (remainingLenOfRod >= len[i]) {
                    int val = price[i] + maxProfit(len, price, remainingLenOfRod - len[i]);
                    if (val > max) {
                        max = val;
                    }
                }
            }

            lookup.put(remainingLenOfRod, max);
        }

        return lookup.get(remainingLenOfRod);
    }

    public static void main(String[] args) {
        int[] len = { 1, 2, 3, 4, 5, 6, 7, 8 };
        int[] price = { 1, 5, 8, 9, 10, 17, 17, 20 };
        int[] price2 = { 3, 5, 8, 9, 10, 17, 17, 20 };
        CuttingRod cuttingRod = new CuttingRod();
        System.out.println("max profit using naive recursive solution : " + cuttingRod.maxProfit(len, price, 8));
        System.out.println("max profit using naive recursive solution : " + cuttingRod.maxProfit(len, price2, 8));

        System.out.println("max profit using dp solution : " + cuttingRod.maxProfitDP(len, price, 8, new HashMap<>()));
        System.out.println("max profit using dp solution : " + cuttingRod.maxProfitDP(len, price2, 8, new HashMap<>()));
    }

}



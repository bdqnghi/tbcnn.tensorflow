/*
切绳子问题
Rod Cutting Problem
问题
你有一根 n米的绳子，你可以按整数米切绳子，
切出来的任意一根 长i米的绳子，价值 vi
问，你应该如何切，才能得到最多的钱
 */


package dynamic_programming.rod_cutting_problem;


import java.util.HashMap;

public class RodCutting {
    public static void main(String[] args) {
        new RodCutting().run();
    }

    public void run() {
        int prices[][] = {{1, 2}, {2, 3}, {3, 7}, {4, 8}, {5, 10}};  //{length, price}
        int length = 5;
        System.out.println(maxValue(prices, length));
    }

    public int maxValue(int[][] prices, int length) {
        HashMap<Integer, Integer> map = new HashMap<>();
        return maxValueRecurse(prices, length, map);
    }

    private int maxValueRecurse(int[][] prices, int restOfLength, HashMap<Integer, Integer> map) {
        if (restOfLength <= 0) {
            return 0;
        }

        if (map.containsKey(restOfLength)) {
            return map.get(restOfLength);
        }

        int maxPrice = 0;
        for (int i = 0; i < prices.length; i++) {
            if (prices[i][0] <= restOfLength) {
                maxPrice = Math.max(maxPrice, prices[i][1] + maxValueRecurse(prices, restOfLength - prices[i][0], map));
            }
        }

        map.put(restOfLength, maxPrice);

        return maxPrice;
    }
}

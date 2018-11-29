package com.vijendert.algorithms.dp.rodcutting;

public class RodCutting {

	private int max = Integer.MIN_VALUE;

	public static void main(String[] args) {
		RodCutting rc = new RodCutting();
		// int[] prices = { 1, 5, 8, 9, 10, 17, 17, 20 };
		int[] prices = { 2, 5, 7, 3 };
		// int result = rc.cutRodRecursive(prices, 4);
		// int result = rc.cutRod(prices, 4);
		// System.out.println(result);
		rc.rodCuttingDp(prices, 5);
		int res = 0;

		for (int i = 1; i <= prices.length; i++) {
			int sum = rc.cutRodRecursiveMyWay(prices, 5, i, 0);
			if (sum >= res) {
				res = sum;
			}
		}
		System.out.println(res);

	}

	public int cutRodRecursiveMyWay(int[] prices, int M, int cutPoint, int sum) {
		if (M == 0) {
			if (sum > max) {
				max = sum;
			}
			return max;
		}
		M = M - cutPoint;
		if (M >= 0) {
			sum = sum + prices[cutPoint - 1];
		}

		int tmpCutPoint = cutPoint;
		if (M < 0) {
			M = M + cutPoint;
			int temM = M;
			while (M != 0) {
				tmpCutPoint--;
				M = temM - (tmpCutPoint);
			}
			cutPoint = tmpCutPoint;
			sum = sum + prices[cutPoint - 1];
		}
		return cutRodRecursiveMyWay(prices, M, cutPoint, sum);
	}

	// This whole method is wrong
	public int cutRodRecursive(int[] price, int len) {
		if (len <= 0) {
			return 0;
		}
		int maxValue = 0;
		for (int i = 0; i < len; i++) {
			int val = price[i] + cutRodRecursive(price, len - i - 1);
			if (maxValue < val) {
				maxValue = val;
			}
		}
		return maxValue;
	}

	public void rodCuttingDp(int[] prices, int len) {
		int[][] dpTable = new int[prices.length + 1][len + 1];
		int pricesVal = prices.length;
		for (int i = 0; i <= len; i++) {
			dpTable[0][i] = 0;
		}
		for (int i = 0; i <= pricesVal; i++) {
			dpTable[i][0] = 0;
		}
		for (int i = 1; i <= pricesVal; i++) {
			for (int j = 1; j <= len; j++) {
				if (j < i) {
					dpTable[i][j] = dpTable[i - 1][j];
				} else {
					dpTable[i][j] = Math.max(dpTable[i - 1][j], prices[i - 1] + dpTable[i][j - i]);
				}
			}
		}
		findCuttingPoint(dpTable, prices, len);
		System.out.println("The max money that could be made is : " + dpTable[pricesVal][len]);
	}

	public void findCuttingPoint(int[][] dpTable, int[] prices, int len) {
		int m = prices.length;
		int n = len;
		while (m != 0 && n != 0) {
			if (dpTable[m][n] == dpTable[m - 1][n]) {
				m = m - 1;
			} else {
				n = n - m;
				System.out.println("cut were made at " + m);
			}
		}
	}

}

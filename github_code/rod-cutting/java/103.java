package com.learning.ads.dynamicprogramming;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class RodCutting {

	public class Result {
		int finalPrice;
		List<Integer> cuts;
	}

	/**
	 * Complexity :O(2^n)
	 * 
	 * @param prices
	 * @param size
	 * @return
	 */
	public int cut(int[] prices, int size) {
		if (size == 0) {
			return 0;
		}
		int max = Integer.MIN_VALUE;
		for (int i = 1; i <= size; i++) {
			max = Math.max(max, prices[i] + cut(prices, size - i));
		}
		return max;
	}

	/**
	 * Complexity: O(n^2)
	 * 
	 * @param prices
	 * @param size
	 * @return
	 */
	public int cutTopDown(int[] prices, int size) {
		int[] dp = new int[size + 1];
		Arrays.fill(dp, Integer.MIN_VALUE);
		return cutTopDown(prices, size, dp);
	}

	private int cutTopDown(int[] prices, int size, int[] dp) {
		if (dp[size] >= 0) {
			return dp[size];
		}
		int result = 0;
		if (size != 0) {
			int max = Integer.MIN_VALUE;
			for (int i = 1; i <= size; i++) {
				max = Math.max(max, prices[i] + cutTopDown(prices, size - i, dp));
			}
			result = max;
		}
		dp[size] = result;
		return dp[size];
	}

	public Result cutTopDownWithPath(int[] prices, int size) {
		int[] dp = new int[size + 1];
		int[] paths = new int[size + 1];
		Arrays.fill(dp, Integer.MIN_VALUE);
		int finalPrice = cutTopDownWithPath(prices, size, dp, paths);
		List<Integer> cuts = new ArrayList<>();
		while (size != 0) {
			cuts.add(paths[size]);
			size = size - paths[size];
		}
		Result result = new Result();
		result.cuts = cuts;
		result.finalPrice = finalPrice;
		return result;
	}

	private int cutTopDownWithPath(int[] prices, int size, int[] dp, int[] paths) {
		if (dp[size] >= 0) {
			return dp[size];
		}
		int result = 0;
		if (size != 0) {
			int q = Integer.MIN_VALUE;
			for (int i = 1; i <= size; i++) {
				int val = prices[i] + cutTopDownWithPath(prices, size - i, dp, paths);
				if (q < val) {
					q = val;
					paths[size] = i;
				}
			}
			result = q;
		}
		dp[size] = result;
		return dp[size];
	}

	/**
	 * Complexity: O(n^2)
	 * 
	 * @param prices
	 * @param size
	 * @return
	 */
	public int cutBottomUp(int[] prices, int size) {
		int[] dp = new int[size + 1];
		dp[0] = 0;
		for (int i = 1; i <= size; i++) {
			int max = Integer.MIN_VALUE;
			for (int j = 1; j <= i; j++) {
				max = Math.max(max, prices[j] + dp[i - j]);
			}
			dp[i] = max;
		}
		return dp[size];
	}

	public Result cutBottomUpWithPath(int[] prices, int size) {
		int[] dp = new int[size + 1];
		int[] paths = new int[size + 1];
		dp[0] = 0;
		for (int i = 1; i <= size; i++) {
			int q = Integer.MIN_VALUE;
			for (int j = 1; j <= i; j++) {
				int val = prices[j] + dp[i - j];
				if (q < val) {
					q = val;
					paths[i] = j;
				}
			}
			dp[i] = q;
		}

		int finalPrice = dp[size];
		List<Integer> cuts = new ArrayList<>();
		while (size != 0) {
			cuts.add(paths[size]);
			size = size - paths[size];
		}
		Result result = new Result();
		result.cuts = cuts;
		result.finalPrice = finalPrice;
		return result;
	}

}

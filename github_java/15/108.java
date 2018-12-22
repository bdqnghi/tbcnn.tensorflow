package com.java.dynamicProgramming;

/**
 * Rod-cutting problem: Given a rod of length n inches and a table of price for i=1,2,3..n. Determine the maximum revenue r
 * obtainable by cutting up the rod and selling the pieces. Consider, we may need to no cut at all if its giving max. revenue.
 * This is dynamic programming approach using Bottom-Up with Memoization (No recursive call)
 * 
 * 
 * @author 502537203
 *
 */

public class RodCuttingBottomUp {
	static int[] storeMaxRev = new int[20];
	static int[] optimalSize = new int[20];

	public RodCuttingBottomUp() {
		for(int i=0; i<storeMaxRev.length; i++) { storeMaxRev[i] = 0; }
	}
	
	static int maxRevenue(int[] price, int size) {
		int maxRev = Integer.MIN_VALUE;
		
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=i; j++) {
				maxRev = Math.max(maxRev, price[j]+storeMaxRev[i-j]);
			}
			storeMaxRev[i] = maxRev;//Save the calculation
		}

		return storeMaxRev[size];
	}
	
	static int maxRevenueWithSize(int[] price, int size) {
		int maxRev = Integer.MIN_VALUE;
		
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=i; j++) {
				if (maxRev < price[j]+storeMaxRev[i-j]) {
					maxRev = price[j]+storeMaxRev[i-j];
					optimalSize[i] = j;
				}
			}
			storeMaxRev[i] = maxRev;//Save the calculation
		}

		return storeMaxRev[size];
	}
	
	static void printCutRodSolution(int size) {
		System.out.println("Optimal rod cutting size");
		while (size>0) {
			System.out.println(optimalSize[size]);
			size = size - optimalSize[size];
		}
	}
	
	public static void main(String[] args) {
		int[] price = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
		int size = 4;
		
		//System.out.println(maxRevenue(price, size));
		System.out.println("Maximum revenue of size "+size+ " inches is " +maxRevenueWithSize(price, size));
		printCutRodSolution(size);
		System.out.println(java.util.Arrays.toString(optimalSize));
	}
}

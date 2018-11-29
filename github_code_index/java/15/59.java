package com.java.recursion;

/**
 * Rod-cutting problem: Given a rod of length n inches and a table of price for i=1,2,3..n. Determine the maximum revenue r
 * obtainable by cutting up the rod and selling the pieces. Consider, we may need to no cut at all if its giving max. revenue
 * 
 * @author 502537203
 *
 */

class RodCutting {
	static int maxRevenue(int[] price, int size) {
		int maxRev = Integer.MIN_VALUE;
		
		if(size == 0) { return 0; } //Revenue is zero if rod size = 0
		
		for(int i=1; i<=size; i++) {
			maxRev = Math.max(maxRev, price[i] + maxRevenue(price, size-i)); //Recursively calculate the max revenue
		}
		return maxRev;
	}
	
	public static void main(String[] args) {
		int[] price = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};//price chart based on inches
		int size = 10;
		
		System.out.println(maxRevenue(price, size));
	}
}

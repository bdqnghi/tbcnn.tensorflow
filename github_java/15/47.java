package com.chandra.structures.dynamic;

//http://algorithms.tutorialhorizon.com/dynamic-programming-rod-cutting-problem/
public class RodCutting {
	
	public static int rodCutRec(int[] value, int length) {
		
		// base case
		if (length <= 0) return 0;
		
		int max = Integer.MIN_VALUE;
		// 1. Cut at 1inch and recursively go with rest of the rod
		// Recursively cut the rod in different pieces and
        // compare different configurations
		for (int i=0;i<length;i++) {
			max = Math.max(max, value[i]+rodCutRec(value, length-i-1));
		}
		return max;
	}
	
	public static int rodCutDP(int[] value, int length) {
		int price[] = new int[length+1];
		
		price[0] = 0;
		for (int i=1;i<=length;i++) {
			int maxVal = Integer.MIN_VALUE;
			for (int j=0;j<i;j++) {
				maxVal = Math.max(maxVal, value[j]+price[i-j-1]);
			}
			price[i] = maxVal;
		}
		
		return price[length];
	}
	
	public static void main(String[] args) {
		int[] value = { 2, 3, 7, 8, 9 };
		int len = 5;
		System.out.println(rodCutRec(value, len));
		System.out.println(rodCutDP(value, len));
	}
	
	

}

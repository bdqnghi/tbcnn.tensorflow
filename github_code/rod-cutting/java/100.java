package edu.mit.intro2algorithms.dp;

import java.util.Arrays;

/*
 * The rod-cutting problem is the following. Given a rod of length n inches and a
 * table of prices pi for i D 1; 2; : : : ; n, determine the maximum revenue rn
 * obtainable by cutting up the rod and selling the pieces.
 * Discussion: R[i] = max{P[1]+R[i-1], P[2]+R[i-2], ..., P[i]}
 * 
 * Category: DP
 */

public class RodCutting {
	
	public static void main(String[] args) {
		RodCutting rc = new RodCutting();
		int[] P = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
		rc.printResult(rc.maxRevenue(P));
	}
	
	public int[] maxRevenue(int[] P) {
		int[] R = new int[P.length];
		int[] S = new int[P.length];
		Arrays.fill(R, Integer.MIN_VALUE);
		
		R[0] = 0;
		R[1] = P[1];
		S[0] = 0;
		S[1] = 1;
		for (int i=2; i<R.length; i++) {
			for (int j=1; j<=i; j++) {
				if (P[j] + R[i-j] > R[i]) {
					R[i] = P[j] + R[i-j];
					S[i] = j;
				}
				//R[i] = P[j] + R[i-j] > R[i] ? P[j] + R[i-j] : R[i];
			}
		}
		
		return R;
	}
	
	private void printResult(int[] R) {
		for (int i=1; i<R.length; i++) {
			System.out.print(R[i] + " ");
		}
		System.out.println();
	}
}

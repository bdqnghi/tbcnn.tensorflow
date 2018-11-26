/*
 * Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n. Determine the maximum value obtainable by cutting up the rod and selling the pieces. For example, if length of the rod is 8 and the values of different pieces are given as following, then the maximum obtainable value is 22 (by cutting in two pieces of lengths 2 and 6)


length   | 1   2   3   4   5   6   7   8  
--------------------------------------------
price    | 1   5   8   9  10  17  17  20

And if the prices are as following, then the maximum obtainable value is 24 (by cutting in eight pieces of length 1)

length   | 1   2   3   4   5   6   7   8  
--------------------------------------------
price    | 3   5   8   9  10  17  17  20
 */

package com.nitin.algo;

public class RodCutting {
	
	private static int cutRod(int price[], int n)
	{
		 int val[] = new int[n + 1];
	        val[0] = 0;
	 
	        // Build the table val[] in bottom up manner and return
	        // the last entry from the table
	        for (int i = 1; i <= n; i++) {
	            int maxVal = Integer.MIN_VALUE;
	            for (int j = 0; j < i; j++)
	            		maxVal = Math.max(maxVal, price[j] + val[i-j-1]);
	            val[i] = maxVal;
	        }
	 
	        return val[n];
	}

	/* Driver program to test above functions */
	public static void main(String args[]) {
		int arr[] = new int[] {1, 5, 8, 9, 10, 17, 17, 20};
		int size = arr.length;
		System.out.println("Maximum Obtainable Value is "+ cutRod(arr, size));

	}

}

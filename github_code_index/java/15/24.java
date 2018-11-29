package com.prac.leetcode.dp;

/**
 * @author Manish Karki
 * 
 */

public class RodCutting {

	public static int profitDP(int[] value, int length) {
		int[] solution = new int[length + 1];
		solution[0] = 0;
//		solution[1] = value[0];

		for (int i = 1; i <= length; i++) {
			int max = -1;
			for (int j = 0; j < i; j++) {
				max = Math.max(max, value[j] + solution[i - (j + 1)]);
//				System.out.println("i:"+i+" i - (j + 1)::"+(i - (j + 1))+" soln[i - (j + 1)]::"+solution[i - (j + 1)]+" max:"+max);
			}
			solution[i] = max;
		}
		for(int i = 0; i<length+1; i++){
			System.out.println(solution[i]);
		}
		return solution[length];
	}

	public static void main(String[] args) {
		int[] value = { 2, 3, 7, 8, 9 };
		int len = 5;
		System.out.println("Max profit for length is " + len + ":"
				+ profitDP(value, len));

	}

}
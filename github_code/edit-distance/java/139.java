package org.javapearls.algorithm.oj;

public class LevenshteinDistance {


	/**
	 *
	 * @param x
	 * @param y
	 * @return
	 */
	public static int distance(String x, String y){
		if (x == y || x.equals(y)){
			return 0;
		}

		return dp(x.toCharArray(), y.toCharArray());
		//return distance(x.toCharArray(), x.length() - 1, y.toCharArray(), y.length() - 1);
	}

	/**
	 *
	 * @param a
	 * @param endA - end index of A
	 * @param b
	 * @param endB - end index of B
	 * @return
	 */
	public static int distance(char[] a, int endA, char[] b, int endB){

		if (endA < 0) return endB + 1;
		if (endB < 0) return endA + 1;

		int cost = 1;
		if (a[endA] == b[endB]){
			cost = 0;
		}

		int d1 = distance(a, endA-1, b, endB) + 1;
		int d2 = distance(a, endA, b, endB-1) + 1;
		int d3 = distance(a, endA-1, b, endB -1) + cost;

		return Math.min(Math.min(d1, d2), d3);
	}

	public static int dp(char[] a, char[] b){

		int rows = a.length + 1, cols = b.length  + 1;
		int[][] distance = new int[rows][cols];

		// source string can be transform to empty
		// string by drop off all the characters
		for (int i = 1; i < rows; i++){
			distance[i][0] = i;
		}

		// target string can be transformed from empty
		// string by insert all the characters
		for (int j = 1; j < cols; j++){
			distance[0][j] = j;
		}

		for (int i = 1; i < rows; i++){
			for (int j = 1; j < cols; j++){

				if (a[i-1] == b[j-1]){
					distance[i][j] = distance[i-1][j-1];
				} else{
					distance[i][j] = Math.min(
							distance[i-1][j-1] + 1,			// substitution
							Math.min(distance[i-1][j] + 1,	// deletion
									distance[i][j-1] + 1) 	// insertion
									);
				}
			}
		}

		return distance[rows-1][cols-1];
	}


}

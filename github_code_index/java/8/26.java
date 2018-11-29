package com.careercup;

public class EditDistance {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String string1 = "MONEY";
		String string2 = "MAONKEY";
		int editDistance = editDistance(string1, string2);
		System.out.println(editDistance);
	}

	private static int editDistance(String string1, String string2) {
		int[][] editDistance = new int[string1.length() + 1][string2.length() + 1];
		for (int i = 0; i < editDistance.length; i++)
			editDistance[i][0] = i;
		for (int i = 0; i < editDistance[0].length; i++)
			editDistance[0][i] = i;
		for (int i = 1; i < editDistance.length; i++) {
			for (int j = 1; j < editDistance[i].length; j++) {
				//int m = Math
					//	.min(editDistance[i][j - 1], editDistance[i - 1][j]) + 1;
				int k = string1.charAt(i - 1) == string2.charAt(j - 1) ? 0 : 1;
				editDistance[i][j] = Math
						.min(editDistance[i][j - 1]+1, editDistance[i - 1][j - 1] + k);
			}
		}
		return editDistance[editDistance.length - 1][editDistance[editDistance.length - 1].length - 1];
	}

}

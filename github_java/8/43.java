package com.walmart.productgenome.pairComparison.utils.comparers.stringComparers;

import com.walmart.productgenome.pairComparison.utils.comparers.IComparer;

public class LevenshteinDistanceBasedComparer implements IComparer {

	public double compare(String str1, String str2) {
		if (str1 == null) throw new IllegalArgumentException("str1 cannot be null");
		if (str2 == null) throw new IllegalArgumentException("str2 cannot be null");
		
		//the two strings must at least be 5 characters long for this comparer to work
		if (str1.length() < 5) return 0.0;
		if (str2.length() < 5) return 0.0;
		
		//the two strings are at least 5 characters long, so the comparer can work.
		
		//Compute the levenshtein-distance between the two strings
		double distance = (double)computeLevenshteinDistance(str1, str2);
		
		//get the length of the longer string
		double maxLength = Math.max((double)str1.length(), (double)str2.length());
		
		double simScore = 1.0 - (distance/maxLength);
		
		return simScore;
	}
	
	

	private static int computeLevenshteinDistance(CharSequence str1, CharSequence str2) {
		int[][] distance = new int[str1.length() + 1][str2.length() + 1];

		for (int i = 0; i <= str1.length(); i++)
			distance[i][0] = i;
		for (int j = 1; j <= str2.length(); j++)
			distance[0][j] = j;

		for (int i = 1; i <= str1.length(); i++)
			for (int j = 1; j <= str2.length(); j++)
				distance[i][j] = minimum(
						distance[i - 1][j] + 1,
						distance[i][j - 1] + 1,
						distance[i - 1][j - 1]
								+ ((str1.charAt(i - 1) == str2.charAt(j - 1)) ? 0
										: 1));

		return distance[str1.length()][str2.length()];
	}
	
	private static int minimum(int a, int b, int c) {
		return Math.min(Math.min(a, b), c);
	}

	
	
}

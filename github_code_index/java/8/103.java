package dp.assignment.editdistance;

import java.io.IOException;
import java.util.Scanner;

/**
 * Levenshtein Distance (also called Edit Distance) Given two words word1 and
 * word2, find the minimum number of steps required to convert word1 to word2.
 * (each operation is counted as 1 step.)
 * 
 * You have the following 3 operations permitted on a word:
 * 
 * a) Insert a character b) Delete a character c) Replace a character
 * 
 * e.g. Minimum edit distance between the words 'kitten' and 'sitting', is 3
 * 
 * kitten → sitten (substitution of "s" for "k") sitten → sittin (substitution
 * of "i" for "e") sittin → sitting (insertion of "g" at the end).
 * 
 * 
 * (Assume all inputs and substitutions in lower case)
 * 
 * More about Levenshtein Distance:
 * https://en.wikipedia.org/wiki/Levenshtein_distance
 * 
 * Solution:
 * http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/
 * 
 * 
 * @author dwaraknathbs
 *
 */
public class EditDistance {
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(System.in);
		int res;
		String _strWord1;
		try {
			_strWord1 = in.nextLine();
		} catch (Exception e) {
			_strWord1 = null;
		}

		String _strWord2;
		try {
			_strWord2 = in.nextLine();
		} catch (Exception e) {
			_strWord2 = null;
		}

		res = levenshteinDistance(_strWord1, _strWord2);
		System.out.println(String.valueOf(res));

	}

	private static int levenshteinDistance(String _strWord1, String _strWord2) {
		char[] word1 = _strWord1.toCharArray();
		char[] word2 = _strWord2.toCharArray();

		int[][] cache = new int[word1.length + 1][word2.length + 1];
		for (int i = 0; i <= word1.length; i++)
			for (int j = 0; j <= word2.length; j++)
				cache[i][j] = -99;

		editDistanceRecursive(word1, word2, word1.length, word2.length);

		editDistanceWithCache(word1, word2, word1.length, word2.length, cache);

		return editDistanceIterative(word1, word2, cache);
	}

	/**
	 * First step is to identify the recursion. Starting from the end of the two
	 * strings, we are left with three choices.
	 * 
	 * 1) The last two characters could be same- Which means the edit distance
	 * is the edit distance of the substrings word1(0 to m-1) word2 (0 to n-1)
	 * 
	 * 2) We could add a new character in the end- Which means the edit distance
	 * is 1+ edit distance of the substring word1(0 to m-1) and word2(n) - As we
	 * have added a character
	 * 
	 * 3) We could replace/switch a character in the end- Which means the edit
	 * distance is 1+ edit distance of the substring word1(0 to m-1) and word2(0
	 * to n-1) - As we have replaced a character
	 * 
	 * 4)We could remove a character from second word-Which means the edit
	 * distance is 1+ edit distance of the substring word1(0 to m)( First word
	 * is still same) and word2(0 to n-1) - As we have removed a character
	 * 
	 * Min of the possibility 1,2,3 gives the edit distance
	 * 
	 * @param word1
	 * @param word2
	 * @param length1
	 * @param length2
	 * @return
	 */
	private static int editDistanceRecursive(char[] word1, char[] word2, int length1, int length2) {

		if (length1 == 0)
			return length2;
		if (length2 == 0)
			return length1;

		if (word1[length1 - 1] == word2[length2 - 1])
			return editDistanceRecursive(word1, word2, length1 - 1, length2 - 1);

		return 1 + Math.min(editDistanceRecursive(word1, word2, length1 - 1, length2 - 1),
				Math.min(editDistanceRecursive(word1, word2, length1, length2 - 1),
						editDistanceRecursive(word1, word2, length1 - 1, length2)));
	}

	/**
	 * Second step- We notice that during recursion the same problem is solved
	 * multiple times resulting in exponential time. For example for cat and
	 * clan
	 * 
	 * editDistanceRecursive(cat,clan,3,4) editDistanceRecursive(cat,clan,2,3)
	 * editDistanceRecursive(cat,clan,1,2) editDistanceRecursive(cat,clan,0,1)
	 * editDistanceRecursive(cat,clan,1,1) editDistanceRecursive(cat,clan,0,0)
	 * editDistanceRecursive(cat,clan,0,2) editDistanceRecursive(cat,clan,3,3)
	 * editDistanceRecursive(cat,clan,2,2) editDistanceRecursive(cat,clan,1,1)
	 * editDistanceRecursive(cat,clan,0,0) editDistanceRecursive(cat,clan,2,1)
	 * editDistanceRecursive(cat,clan,1,0) editDistanceRecursive(cat,clan,2,0)
	 * editDistanceRecursive(cat,clan,1,1) editDistanceRecursive(cat,clan,0,0)
	 * editDistanceRecursive(cat,clan,1,2) editDistanceRecursive(cat,clan,0,1)
	 * editDistanceRecursive(cat,clan,1,1) editDistanceRecursive(cat,clan,0,0)
	 * editDistanceRecursive(cat,clan,0,2) editDistanceRecursive(cat,clan,3,2)
	 * editDistanceRecursive(cat,clan,2,1) editDistanceRecursive(cat,clan,1,0)
	 * editDistanceRecursive(cat,clan,2,0) editDistanceRecursive(cat,clan,1,1)
	 * editDistanceRecursive(cat,clan,0,0) editDistanceRecursive(cat,clan,3,1)
	 * editDistanceRecursive(cat,clan,2,0) editDistanceRecursive(cat,clan,3,0)
	 * editDistanceRecursive(cat,clan,2,1) editDistanceRecursive(cat,clan,1,0)
	 * editDistanceRecursive(cat,clan,2,0) editDistanceRecursive(cat,clan,1,1)
	 * editDistanceRecursive(cat,clan,0,0) editDistanceRecursive(cat,clan,2,2)
	 * editDistanceRecursive(cat,clan,1,1) editDistanceRecursive(cat,clan,0,0)
	 * editDistanceRecursive(cat,clan,2,1) editDistanceRecursive(cat,clan,1,0)
	 * editDistanceRecursive(cat,clan,2,0) editDistanceRecursive(cat,clan,1,1)
	 * editDistanceRecursive(cat,clan,0,0) editDistanceRecursive(cat,clan,1,2)
	 * editDistanceRecursive(cat,clan,0,1) editDistanceRecursive(cat,clan,1,1)
	 * editDistanceRecursive(cat,clan,0,0) editDistanceRecursive(cat,clan,0,2)
	 * editDistanceRecursive(cat,clan,2,3) editDistanceRecursive(cat,clan,1,2)
	 * editDistanceRecursive(cat,clan,0,1) editDistanceRecursive(cat,clan,1,1)
	 * editDistanceRecursive(cat,clan,0,0) editDistanceRecursive(cat,clan,0,2)
	 * editDistanceRecursive(cat,clan,2,4) editDistanceRecursive(cat,clan,1,3)
	 * editDistanceRecursive(cat,clan,0,2) editDistanceRecursive(cat,clan,1,2)
	 * editDistanceRecursive(cat,clan,0,1) editDistanceRecursive(cat,clan,1,1)
	 * editDistanceRecursive(cat,clan,0,0) editDistanceRecursive(cat,clan,0,2)
	 * editDistanceRecursive(cat,clan,0,3) editDistanceRecursive(cat,clan,2,3)
	 * editDistanceRecursive(cat,clan,1,2) editDistanceRecursive(cat,clan,0,1)
	 * editDistanceRecursive(cat,clan,1,1) editDistanceRecursive(cat,clan,0,0)
	 * editDistanceRecursive(cat,clan,0,2) editDistanceRecursive(cat,clan,1,4)
	 * editDistanceRecursive(cat,clan,0,3) editDistanceRecursive(cat,clan,1,3)
	 * editDistanceRecursive(cat,clan,0,2) editDistanceRecursive(cat,clan,1,2)
	 * editDistanceRecursive(cat,clan,0,1) editDistanceRecursive(cat,clan,1,1)
	 * editDistanceRecursive(cat,clan,0,0) editDistanceRecursive(cat,clan,0,2)
	 * editDistanceRecursive(cat,clan,0,3) editDistanceRecursive(cat,clan,0,4)
	 * 
	 * We notice that the editDistanceRecursive(cat,clan,1,1) is solved 11
	 * times. Similarly for other sub problems. It will be worth to store the
	 * outcome of the result in a cache the first time its calculated and looked
	 * up in future calls
	 * 
	 * @param word1
	 * @param word2
	 * @param length1
	 * @param length2
	 * @param cache
	 * @return
	 */
	private static int editDistanceWithCache(char[] word1, char[] word2, int length1, int length2, int[][] cache) {
		if (cache[length1][length2] == -99) {
			if (length1 == 0)
				cache[length1][length2] = length2;
			else if (length2 == 0)
				cache[length1][length2] = length1;

			else if (word1[length1 - 1] == word2[length2 - 1]) {
				cache[length1][length2] = editDistanceWithCache(word1, word2, length1 - 1, length2 - 1, cache);
			} else {

				cache[length1][length2] = 1
						+ Math.min(editDistanceWithCache(word1, word2, length1 - 1, length2 - 1, cache),
								Math.min(editDistanceWithCache(word1, word2, length1, length2 - 1, cache),
										editDistanceWithCache(word1, word2, length1 - 1, length2, cache)));
			}
		}
		return cache[length1][length2];

	}

	/**
	 * Step 3- We know that in step 2 we rely on previously executed
	 * subproblems( stored in the cache) to solve the main problem. Instead we
	 * could iteratively build the cache from bottom up. The cache in step2
	 * looks like below
	 * 
	 * <pre>
	 * 					  length2
	 *      			0 1 2 3 4 
	   		length1		1 0 1 2 3 
	        			2 1 1 1 2 
	        			3 2 2 2 2
	 * 
	 * </pre>
	 * 
	 * @param word1
	 * @param word2
	 * @param cache
	 * @return
	 */
	private static int editDistanceIterative(char[] word1, char[] word2, int[][] cache) {

		for (int length1 = 0; length1 <= word1.length; length1++) {

			for (int length2 = 0; length2 <= word2.length; length2++) {

				if (length1 == 0)
					cache[length1][length2] = length2;
				else if (length2 == 0)
					cache[length1][length2] = length1;

				else if (word1[length1 - 1] == word2[length2 - 1]) {
					cache[length1][length2] = cache[length1 - 1][length2 - 1];
				} else {

					cache[length1][length2] = 1 + Math.min(cache[length1 - 1][length2 - 1],
							Math.min(cache[length1][length2 - 1], cache[length1 - 1][length2]));
				}

			}
		}
		return cache[word1.length][word2.length];

	}

}

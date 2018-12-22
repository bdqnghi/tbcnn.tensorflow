/*Edit Distance
question: http://www.lintcode.com/en/problem/edit-distance/
answer:  http://www.jiuzhang.com/solutions/edit-distance/

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
You have the following 3 operations permitted on a word:

Insert a character
Delete a character
Replace a character

Example
Given word1 = "mart" and word2 = "karma", return 3.
*/
package twoSequenceDP;

public class EditDistance {
	public static int minstep(String A, String B){
		if (A == null || A.length() == 0){
			return B.length();
		}
		if (B == null || B.length() == 0){
			return A.length();
		}
		int n = A.length();
		int m = B.length();
		//1. state: min[i][j] means the minimum step for changing the first i of A to first j  of B
		int[][] min = new int[n + 1][m + 1];
		//2. initialization
		for (int i = 0; i < n + 1; i++){
			min[i][0] = i;
		}
		for (int j = 0; j < m + 1; j++){
			min[0][j] = j;
		}
		//3. function
		for (int i = 1; i < n + 1; i++){
			for (int j = 1; j < m + 1; j++){
				if (A.charAt(i - 1) == B.charAt(j - 1)){
					min[i][j] = min[i - 1][j - 1];
				}else{
					min[i][j] = 1 + Math.min(min[i - 1][j - 1], Math.min(min[i - 1][j], min[i][j - 1]));
				}
			}
		}		
		return min[n][m];		
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String A = "mart";
		String B = "karma";
		System.out.println(minstep(A,B));
	}
}

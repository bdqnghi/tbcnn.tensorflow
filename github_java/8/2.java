package Divideandconquer;

import java.util.Scanner;

public class KPalindromeString {
public static void main(String[] args) {
	Scanner in = new Scanner(System.in);
	try{
		System.out.println("Enter the string first and then the integer");
		String s = in.nextLine();
		int k = in.nextInt();
		if(usingRecursion(s, k))
			System.out.println("YES");
		else
			System.out.println("NO");
		if(dynamicProgrammingSolution("abxa","axba",k) <= 2*k)
			System.out.println("YES");
		else
			System.out.println("NO");
	}
	finally{
		in.close();
	}
}
public static boolean usingRecursion(String s, int k){
	if(s.length()==0 || s.length() == 1)
		return true;
	
	while(s.charAt(0)==s.charAt(s.length()-1)){
		s=s.substring(1,s.length()-1);
		
		if(s.length()==0 || s.length() == 1)// If the substring is decremented till the point where the length is 0 or 1, then return true
			return true;
	}
	 
	if(k==0)    // If there is a mismatch, then check if the k is already 0
		return false;
	
	return usingRecursion(s.substring(0,s.length()-1), k-1) || usingRecursion(s.substring(1,s.length()), k-1); // decrement the k and check for the remaining string leaving behind the character which led to the mis-matach
	
}

public static int dynamicProgrammingSolution (String s, String rev, int k){
	
	
	/*
	 * Algorithm:
The question asks if we can transform the given string S into its reverse deleting at most K letters.
 
We could modify the traditional Edit-Distance algorithm, considering only deletions, and check if 
this edit distance is <= 2K. There is a problem though. S can have length = 20,000 and the 
Edit-Distance algorithm takes O(N^2). Which is too slow. 

(From here on, I'll assume you're familiar with the Edit-Distance algorithm and its DP matrix) 

However, we can take advantage of K. We are only interested to delete K letters. 
This means that any position more than K positions away from the main diagonal is useless because 
its edit distance must exceed those K deletions. 

Since we are comparing the string with its reverse, we will do at most K deletions 
and K insertions (to make them equal). Thus, we need to check if the ModifiedEditDistance is <= 2*K 

Since in this algorithm, we are making the string and its reverse equal. THEY BOTH HAVE
N CHARACTERS SO IF WE REMOVE K CHARACTERS, WE NEED TO INSERT K CHARACTERS SO AS TO 
MAINTAIN SIZE = N.

The correspondence between characters inserted and deleted is done because we're transforming 
the input string into its reverse AND DOING NOTHING TO THE REVERSE STRING because Edit Distance
Algorithm only modifies one string out of the given two strings in input.
So those operations will lead to a palindrome. 

"You can do (1 insertion + 1 deletion)*n times, and you will still be in the main diagonal" 
Sure, but the cost will be 2*N. As explained above, the final step is to compare DP[N][N] with 2*K. 
only then we decide the answer.

Here's the code:
	 */
	
	
	
	int n = s.length();
	
	int[][] dp = new int[n+1][n+1];
	for(int i=0;i<=n;i++)
		dp[i][0]=dp[0][i]=i;
	
	for(int i=1;i<=n;i++){     // for every row
		int from = Math.max(1, i-k);    // travel from the column starting from Max(1,i-k)
		int to = Math.min(i+k, n);      // till the column ending at Min(i+k,n)
		for(int j=from;j<=to;j++){
			if(s.charAt(i-1)==rev.charAt(j-1))
				dp[i][j] = dp[i-1][j-1];
			
			//(dp[i][j-1]) means delete character 'j' && (dp[i-1]+1) means inserting a character 'i'
			dp[i][j] = 	Math.min(Math.min(dp[i][j], 1 + dp[i][j-1]),1 + dp[i-1][j]); 
			
		}
	}
	return dp[n][n];	
}

}
/*
 * Analysis:
 * We only process (2*K+1) columns per row. So this algorithm works in O(N*K) which is fast enough.
 * Time Complexity = O(NK)
 * Space Complexity = O(N^2)
 */
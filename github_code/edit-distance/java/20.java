package com.geek;

import java.util.Scanner;

public class Editdistance {

	public static void main(String[] args) {
		
				Scanner sc=new Scanner(System.in);
				int a=sc.nextInt();
				for(int i=0;i<a;i++)
				{int l=sc.nextInt();
				int m=sc.nextInt();
				String s1=sc.next();
				String s2=sc.next();
				System.out.println(editDistDP(s1,s2,l,m));
	
				}
	}

	 static int min(int x,int y,int z)
	    {
	        if (x < y && x <z) return x;
	        if (y < x && y < z) return y;
	        else return z;
	    }
	 
	    static int editDistDP(String str1, String str2, int m, int n)
	    {
	        // Create a table to store results of subproblems
	        int dp[][] = new int[m+1][n+1];
	      
	        // Fill d[][] in bottom up manner
	        for (int i=0; i<=m; i++)
	        {
	            for (int j=0; j<=n; j++)
	            {
	                // If first string is empty, only option is to
	                // isnert all characters of second string
	                if (i==0)
	                    dp[i][j] = j;  // Min. operations = j
	      
	                // If second string is empty, only option is to
	                // remove all characters of second string
	                else if (j==0)
	                    dp[i][j] = i; // Min. operations = i
	      
	                // If last characters are same, ignore last char
	                // and recur for remaining string
	                else if (str1.charAt(i-1) == str2.charAt(j-1))
	                    dp[i][j] = dp[i-1][j-1];
	      
	                // If last character are different, consider all
	                // possibilities and find minimum
	                else
	                    dp[i][j] = 1 + min(dp[i][j-1],  // Insert
	                                       dp[i-1][j],  // Remove
	                                       dp[i-1][j-1]); // Replace
	            }
	        }
	  
	        return dp[m][n];
	    }
	 
}

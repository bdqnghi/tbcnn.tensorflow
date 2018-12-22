/*
Given two words A and B, find the minimum number of steps required to convert A to B. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

Insert a character
Delete a character
Replace a character
*/

public class Solution {
	public int minDistance(String a, String b) 
	{
	    int[][] numSteps = new int[a.length()+1][b.length()+1];
	    
	    for(int i = 0; i <= a.length(); i++)
	    {
	        for(int j = 0; j <= b.length(); j++)
	        {
	            if(i == 0 && j == 0) numSteps[i][j] = 0;
	            else if(i == 0 && j != 0) numSteps[i][j] = numSteps[i][j-1]+1;
	            else if(i != 0 && j == 0) numSteps[i][j] = numSteps[i-1][j]+1;
	            else if(a.charAt(i-1) == b.charAt(j-1)) numSteps[i][j] = numSteps[i-1][j-1];
	            else numSteps[i][j] = Math.min( 
	                Math.min(numSteps[i-1][j-1]+1, numSteps[i-1][j]+1),
	                numSteps[i][j-1]+1);
	        }
	    }
	    return numSteps[a.length()][b.length()];
	    
	}
}


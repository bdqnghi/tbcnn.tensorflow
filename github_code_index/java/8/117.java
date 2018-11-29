public class Solution {
    /**
     * @param word1 and word2: Two string.
     * @return: The minimum number of steps.
     */
    public int minDistance(String a, String b) {
        // write your code 
        
       if (a == null && b == null) {
    		return 0;
    	}

    	int n = a.length();
    	int m = b.length();
    	
    	int[][] f = new int[n + 1][m + 1];	//f[i][j]: the minimal distance of (the first i char of a and the first j of b)

    	for (int i = 0; i < f.length; i++) {
    		f[i][0] = i;
    	}

    	for (int j = 0; j < f[0].length; j++) {
    		f[0][j] = j;
    	}

    	for (int aFirst = 1; aFirst <= a.length(); aFirst++) {
    		for (int bFirst = 1; bFirst <= b.length(); bFirst++) {
    			if (a.charAt(aFirst - 1) == b.charAt(bFirst - 1)) {
    				f[aFirst][bFirst] = f[aFirst - 1][bFirst - 1];
    			} else {    
    				f[aFirst][bFirst] = 1 + Math.min(Math.min(f[aFirst - 1][bFirst - 1], f[aFirst][bFirst - 1]), f[aFirst - 1][bFirst]);
    			}

    		} 
    	}
    	return f[n][m];
    	
    }
}2
package dp.src;

public class editdistance {
	

	public int minDistance_based_on_new_model(String word1, String word2) {
		if(word1 == null || word1.length() == 0) return 0;
		if(word2 == null || word2.length() == 0) return 0;
		
		int m = word1.length();
		int n = word2.length();
		
		int[][] dist = new int[m+1][n+1];
		
		for(int i = 0; i <= m; i++) dist[i][0] = i;
		for(int i = 0; i <= n; i++) dist[0][i] = i;
		
		for(int i = 1; i <= m; i++) {
			char c1 = word1.charAt(i-1);
			for(int j = 1; j <= n; j++) {
				char c2 = word2.charAt(j-1);
				if(c1 == c2) dist[i][j] = dist[i-1][j-1];
				else {
					int insert = dist[i][j-1] + 1;
					int delete = dist[i-1][j] + 1;
					int replace = dist[i-1][j-1] + 1;
					
					dist[i][j] = Math.min(Math.min(insert, delete), replace);					
				}
				
			}
		}
		
		return dist[m][n];
		
	}
	
	public int minDistance(String word1, String word2) {
		if(word1 == null || word1.length() == 0) return 0;
		if(word2 == null || word2.length() == 0) return 0;
		
		int res = 0;
		
		int m = word1.length();
		int n = word2.length();
		
		int[][] dp = new int[m+1][n+1];  // the extra one is due to ""
		for(int i = 0; i < m+1; i++) {
			dp[i][0] = i; // delete
		}
		for(int i = 0; i < n+1; i++) {
			dp[0][i] = i; // add
		}
		
		for(int i = 1; i < m+1; i++) {
			for(int j = 1; j < n+1; j++) {
				if(word1.charAt(i-1) == word2.charAt(j-1)) dp[i][j] = dp[i-1][j-1];
				else dp[i][j] = 1 + Math.min(dp[i-1][j-1], Math.min(dp[i-1][j], dp[i][j-1])); 
			}
		}
		
		res = dp[m][n];
		
		return res;
	}
	
	 // say diff the the difference between two string length
     // case 1: if diff > 1, return false
	 // case 2: if diff == 1, remove one char from the longer one and the rest should match
	 // case 2: if diff == 0, all should match except one difference
	public boolean isOneEditDistance(String s, String t) {
		if(s == null && t != null) return false;
		if(s != null && t == null) return false;

		int m = s.length();
		int n = t.length();
		if(Math.abs(m-n) > 1) return false;
		
		int count = 0;  // how many different
		int i = 0;
		int j = 0;		
		while(i < m && j < n) {
			if(s.charAt(i) == t.charAt(j)) {
				i++;
				j++;
			} else {
				count++;
				if(count > 1) return false;
				if(m < n) j++;
				else if(m > n) i++;
				else {
					i++;
					j++;
				}
			}
		}
		
		if(i < m || j < n) {
			count++;
		}
		
		return count <= 1;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		editdistance test = new editdistance();
		String words1 = "Carthorse";
		String words2 = "Orchestra";
		int ans = test.minDistance(words1, words2);
		System.out.println(ans);
		
		ans = test.minDistance_based_on_new_model(words1, words2);
		System.out.println(ans);
		
		String s = "gesek";
		String t = "geeks";
		if(test.isOneEditDistance(s, t)) {
			System.out.println("Yes: " + s + " and "+ t + " has one edit distance");
		} else {
			System.out.println("No: " + s + " and "+ t + " has no one edit distance");
		}

	}

}

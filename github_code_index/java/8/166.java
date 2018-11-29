public static void main (String args[]) {
	String a = "apple";
	String b = "anne";
	editdistance(a,b);

}
public static void editdistance(String a, String b){
	int[][] dp = new int[a.length()+1][b.length()+1];
	for (int i = 0; i <= a.length(); i++) {
		dp[i][0] = i;
	}
	for(int j = 0; j <= b.length(); j++) {
		dp[0][j] = j;
	}
	for(int i = 1; i <= a.length(); i++){
		for(int j = 1; j <= b.length(); j++){
			if(a.charAt(i-1) == b.charAt(j-1)){
				dp[i][j] = dp[i-1][j-1];
			}else{
				dp[i][j] = Math.min(dp[i-1][j-1],dp[i-1][j],dp[i][j-1])+1;
			}
		}
	}

	return dp[a.length()][b.length()];

}
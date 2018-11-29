package dynamicProgramming;

public class CuttingRod {
	static int max = Integer.MIN_VALUE;
	public static void main(String[]args) {
		//System.out.println(cuttingCost(new int[] {1, 5, 8, 9, 10, 17, 17, 20},8));
		System.out.println(cutRod(new int[] {2,5,7,8},5));
	}
	// RECURSIVe
	public static int cuttingCost(int[]price,int length) {
		if (length <= 0)
            return 0;
        int max_val = Integer.MIN_VALUE;
 
        // Recursively cut the rod in different pieces and
        // compare different configurations
        for (int i = 0; i<length; i++)
            max_val = Math.max(max_val,
                              price[i] + cuttingCost(price, length-i-1));
 
        return max_val;
	}
	
	//ITERATIVE
	public static int cutRod(int[]price, int length) {
		if(length<=0)
			return 0;
		int[][] dp = new int[price.length][length+1];
		
		for(int i=0;i<dp.length;i++) {
			for(int j=1;j<dp[0].length;j++) {
				if(j<=length && i-1<0) {
					dp[i][j] = price[i]*j;
				}
				else if(j<=length) {
					if(j<i+1) {
						dp[i][j] = dp[i-1][j];
					}
					else {
						dp[i][j] = Math.max(price[i]+dp[i][j-i-1], dp[i-1][j]);
					}
				}
			}
		}
		return dp[price.length-1][length];
	}
}

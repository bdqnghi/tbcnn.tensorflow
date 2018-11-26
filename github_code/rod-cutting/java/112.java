package DynamicProgramming;

public class RodCutting {
	public int[] price;

	RodCutting(int[] p) {
		this.price = p;
	}

	public int rodCuttingTopDown(int dp[], int n) {
		if (n == 0)
			return 0;
		if (dp[n] > 0)
			return dp[n];
		int max = Integer.MIN_VALUE;
		// cur at every position from 1 to n
		for (int i = 1; i <= n; i++) {
			max = Integer.max(max, price[i] + rodCuttingTopDown(dp, n - i));
		}

		return dp[n] = max;
	}
//1
//        2
//        3
//        4
//        13
//        14
//        15
//
//        1
//        1
//        2
//        1 1
//        3
//        1 1 1
//        4
//        1 1 1 1
//        13
//        5
//        14
//        1 5
//        15
//        1 1 5
    public int rodCuttingBottomUp(int n) {
		int[][] dp = new int[n+1][price.length];
        for(int i = 1; i < price.length; i++) {
            for(int j = 0; j <= n; j++) {
                if(j >= i) {
                    dp[j][i] = Math.max(dp[j-i][i]
                            + price[i], dp[j][i-1]);
                }
                else {
                    dp[j][i] = dp[j][i-1];
                }
            }
        }

		return dp[n][price.length-1];
	}
	
	public void printSolution(int n, int[] firstCut) {
		while(n > 0) {
			System.out.print(firstCut[n] + " ");
			n-=firstCut[n];
		}
		System.out.println();
	}

	public static void main(String[] args) {
		int[] p = new int[] { 0, 1, 2, 3, 4, 13, 11, 13 };
		RodCutting rc = new RodCutting(p);
		int[] dp = new int[p.length+1];
		// Top down
		System.out.println(rc.rodCuttingTopDown(dp, 1));
		System.out.println(rc.rodCuttingTopDown(dp, 2));
		System.out.println(rc.rodCuttingTopDown(dp, 3));
		System.out.println(rc.rodCuttingTopDown(dp, 4));
		System.out.println(rc.rodCuttingTopDown(dp, 5));
		System.out.println(rc.rodCuttingTopDown(dp, 6));
		System.out.println(rc.rodCuttingTopDown(dp, 7));
		// Bottom up
		System.out.println();
		System.out.println(rc.rodCuttingBottomUp(1));
		System.out.println(rc.rodCuttingBottomUp(2));
        System.out.println(rc.rodCuttingBottomUp(3));
        System.out.println(rc.rodCuttingBottomUp(4));
        System.out.println(rc.rodCuttingBottomUp(5));
        System.out.println(rc.rodCuttingBottomUp(6));
        System.out.println(rc.rodCuttingBottomUp(7));
        System.out.println(rc.rodCuttingBottomUp(8));
        System.out.println(rc.rodCuttingBottomUp(9));
        System.out.println(rc.rodCuttingBottomUp(10));

	}

}

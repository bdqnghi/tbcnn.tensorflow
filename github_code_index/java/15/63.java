/**
 * Created by Kevin on 10/29/16.
 */
public class RodCutting {
    public static void main(String args[] ) throws Exception {
//        int[] profits = { 0, 1, 2, 4 };
//        int length = 10;
        int[] profits = {0, 1, 2, 4, 6, 10};
        int length = 6;

        System.out.println(bestProfitBottomUpDp(length, profits));
    }

    private static int bestProfitBottomUpDp(int length, int[] profits) {
        int[] dp = new int[length + 1];
        dp[0] = 0;

        for (int currLen = 1; currLen <= length; currLen++) {
            dp[currLen] = 0;
            for (int cut = 1; cut < profits.length; cut++) {
                if (currLen - cut >= 0) {
                    dp[currLen] = Math.max(dp[currLen], profits[cut] + dp[currLen - cut]);
                } else {
                    break;
                }
            }

        }

        return dp[length];
    }
}


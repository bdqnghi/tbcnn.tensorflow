package algorithms.dp;

/**
 * Created by saima_000 on 9/24/2016.
 */
public class RodCutting {
    private static int[][] dp;
    private static int rodCutting(int[] lengths, int[] prices, int index, int size) {
        if(size <= 0 || index >= prices.length)
            return 0;
        if(dp[index][size-1] != -1)
            return dp[index][size-1];
        int max = 0;
        for(int i=0;i<prices.length;i++) {
            if(lengths[i] > size)
                max = Math.max(max, rodCutting(lengths, prices, i, size-lengths[i]));
            else
                max = Math.max(max, rodCutting(lengths, prices, i, size-lengths[i])+prices[i]);
        }
        dp[index][size-1] = max;
        return max;
    }

    public static void main(String[] args) {
        int[] prices = {3, 5, 8, 9, 10, 17, 17, 20};
        int[] lengths = {1, 2, 3, 4, 5, 6, 7, 8};
        int size = 8;
        dp = new int[8][];
        for(int i=0;i<dp.length;i++)
            dp[i] = new int[dp.length];
        for(int i=0;i<dp.length;i++)
            for(int j=0;j<dp.length;j++)
                dp[i][j] = -1;
        System.out.println(rodCutting(lengths, prices, 0, lengths.length));
    }
}

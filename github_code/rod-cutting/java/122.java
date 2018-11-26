package dynamic.programming;

/**
 * @author Navin Kumar
 * @date 7/15/18
 */
public class RodCutting {

    private int maxProfit(int[] prices) {
        int n = prices.length;
        int[] v = new int[n+1];
        v[0] = 0;

        for(int i = 1; i<=n; i++) {
            int maxV = Integer.MIN_VALUE;
            for(int j = 0; j < i; j++) {
                maxV = Math.max(maxV, prices[j] + v[i - j - 1]);
            }
            v[i] = maxV;
        }

        return v[n];
    }

    public static void main(String[] args) {
        int arr[] = new int[] {1, 5, 8, 9, 10, 17, 17, 20};
        RodCutting rc = new RodCutting();
        int maxProfit = rc.maxProfit(arr);
        System.out.println("Max profit = " + maxProfit);
    }

}

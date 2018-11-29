package dp;

/**
 * Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n.
 * Determine the maximum value obtainable by cutting up the rod and selling the pieces. For example, if length of the
 * rod is 8 and the values of different pieces are given as following, then the maximum obtainable value is 22 (by
 * cutting in two pieces of lengths 2 and 6)
 * 
 * 
 * length | 1 2 3 4 5 6 7 8 -- price | 1 5 8 9 10 17 17 20
 * 
 * @author harish.sharma
 *
 */
public class RodCutting {

    public static int solve(int[] price, int n) {
        if (n == 0) return 0;
        if (n == 1) return price[n - 1];
        int res = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            res = Math.max(price[i] + solve(price, n - i - 1), res);
        }
        return res;
    }

    public static int solve1(int[] price) {

        int len = price.length;
        int[] P = new int[len + 1];

        for (int i = 1; i <= len; i++) {
            int res = Integer.MIN_VALUE;
            for (int j = 0; j < i; j++) {
                res = Math.max(res, price[j] + P[i - j - 1]);
            }
            P[i] = res;
        }
        return P[len];
    }

    public static void main(String[] args) {
        int arr[] = { 1, 5, 8, 9, 10, 17, 17, 20};
        System.out.println(solve(arr, arr.length));

        System.out.println(solve1(arr));
    }
}

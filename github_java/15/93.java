/**
 * Created by tp1082 on 4/11/2017.
 */

import java.util.Arrays;
import java.util.Random;
public class RodCutting {
    public static void main(String[] args) {

        Random rnd = new Random(2358L);

        RodCutting cutRod = new RodCutting();

        int rodLengths[] = computeRodLengths(3, 10);

        int nCases = 50;

        int max = 50;

        long[] computingTimeMemoized = new long[rodLengths.length];
        long[] computingTimeBottomUp = new long[rodLengths.length];
        long[] computingTimeRecursive= new long[rodLengths.length];
        for (int i = 0; i < nCases; i++) {

            int[] p = generateTestCase(rodLengths[rodLengths.length - 1], max, rnd);

            for (int j = 0; j < rodLengths.length; j++) {
                computingTimeMemoized[j] += testMemoized(p, rodLengths[j], cutRod);
                computingTimeBottomUp[j] += testBottomUp(p, rodLengths[j], cutRod);
                computingTimeRecursive[j] += testRecursive(p, rodLengths[j], cutRod);
            }
        }
        System.out.printf("%20s %20s %20s %20s\n", "rod length","Recursive time [ns]",
                "memoized time [ns]", "bottom-up time [ns]");
        for (int i = 0; i < rodLengths.length; i++) {
            computingTimeMemoized[i] /= nCases;
            computingTimeBottomUp[i] /= nCases;
            computingTimeRecursive[i] /=nCases;
            System.out.printf("%20d %20d %20d %20d\n", rodLengths[i],computingTimeRecursive[i],
                    computingTimeMemoized[i], computingTimeBottomUp[i]);
        }
    }
    public int cutRodRecursive(int price[], int n){
        if (n <= 0)
            return 0;
        int max_val = Integer.MIN_VALUE;

        // Recursively cut the rod in different pieces and
        // compare different configurations
        for (int i = 0; i<n; i++)
            max_val = Math.max(max_val,
                    price[i] + cutRodRecursive(price, n-i-1));
        return max_val;
    }
    public int cutRodMemoized(int[] p, int n) {
        int r[] = new int[p.length + 1];
        Arrays.fill(r, Integer.MIN_VALUE);
        return cutRodMemoizedAux(p, n, r);
    }
    private int cutRodMemoizedAux(int[] p, int n, int[] r) {
        if (r[n] >= 0)
            return r[n];
        int q = 0;
        if (n != 0) {
            q = Integer.MIN_VALUE;
            for (int i = 1; i <= n; i++)
                q = Math.max(q, p[i - 1] + cutRodMemoizedAux(p, n - i, r));
        }
        r[n] = q;
        return q;
    }
    public int cutRodBottomUp(int[] p, int n) {
        int[] r = new int[p.length + 1];
        r[0] = 0;
        for (int j = 1; j <= n; j++) {
            int q = Integer.MIN_VALUE;
            for (int i = 1; i <= j; i++)
                q = Math.max(q, p[i - 1] + r[j - i]);
            r[j] = q;
        }
        return r[n];
    }
    private static int[] computeRodLengths(int interval, int max) {
        int l = max / interval;
        int[] ret = new int[l];
        for (int i = 0; i < l; i++)
            ret[i] = interval * (i + 1);
        return ret;
    }
    private static long testRecursive(int[] p, int n, RodCutting cutRod) {
        long start = System.nanoTime();
        cutRod.cutRodRecursive(p, n);
        return System.nanoTime() - start;
    }
    private static long testMemoized(int[] p, int n, RodCutting cutRod) {
        long start = System.nanoTime();
        cutRod.cutRodMemoized(p, n);
        return System.nanoTime() - start;
    }
    private static long testBottomUp(int[] p, int n, RodCutting cutRod) {
        long start = System.nanoTime();
        cutRod.cutRodBottomUp(p, n);
        return System.nanoTime() - start;
    }
    private static int[] generateTestCase(int n, int max, Random rnd) {
        int[] ret = new int[n];
        for (int i = 0; i < n; i++)
            ret[i] = rnd.nextInt(max);
        return ret;
    }
}

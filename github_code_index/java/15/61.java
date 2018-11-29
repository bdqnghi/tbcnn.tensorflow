/**
 * Implementation of Data Structure and Algorithms
 * Maximum profit for rod cutting for given length of problem
 * Created by Ketki Mahajan on 2/20/2018.
 **/
public class rodCuttingProblem {
    public static void main(String[] args) {
        //price array for each length i
        int[] p = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
        int n = 10;
        cutRod(p, n);
    }

    private static void cutRod(int[] p, int n) {
        int[] revenue = new int[p.length];
        revenue[0] = 0;
        for (int j = 1; j <= n; j++) {
            int q = -999;
            for (int i = 1; i <= j; i++) {
                q = Math.max(q, p[i] + revenue[j - i]);
            }
            revenue[j] = q;
        }
        System.out.println(revenue[n]);
    }
}


package algorithms.dynamic_programming;

import java.util.Arrays;

/*

The rod-cutting problem is the following. 
Given a rod of length n inches and a table of prices pi for i D 1, 2, ..., n, 
determine the maximum revenue rn obtainable by cutting up the rod and selling the pieces. 
 
*/

public class Rod_Cutting {

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public int cutRod_Recursive(int n, int[] prize, int[] r) {
        Arrays.fill(r, Integer.MIN_VALUE);
        return cutRod_Recursive_Aux(n, prize, r);
    }

    private int cutRod_Recursive_Aux(int n, int[] prize, int[] r) {
        int max = 0;
        if (r[n] >= 0) {
            return r[n];
        } else {
            for (int i = 1; i <= n; i++) {
                max = Math.max(max, prize[i] + cutRod_Recursive_Aux(n - i, prize, r));
            }
            return r[n] = max;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public int cutRod(int n, int[] prize, int[] r) {
        for (int j = 1; j <= n; j++) {
            int max = 0;
            for (int i = 1; i <= j; i++) {
                max = Math.max(max, prize[i] + r[j - i]);
            }
            r[j] = max;
        }
        return r[n];
    }

    public static void main(String[] args) {
        int[] prize = new int[] { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
        int n = 6;
        int[] r = new int[n + 1];
        System.out.println(new Rod_Cutting().cutRod(n, prize, r));
        System.out.println(new Rod_Cutting().cutRod_Recursive(n, prize, r));
    }

}

package com.mounacheikhna.practice.dynamicProgramming;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static java.lang.System.out;

/**
 * Created by m.cheikhna on 02/03/2017.
 */
public class RodCutting {

    int cutRod(int[] price, int n) {
        if (n == 0) return 0;

        int max_val = Integer.MIN_VALUE;
        for (int i = 1; i <= n; i++) {
            max_val = Math.max(max_val, price[i] + cutRod(price, n - i));
        }
        return max_val;
    }

    int memoizedCutRod(int[] price, int n) {
        if (n == 0) return 0;

        int[] r = new int[n + 1];
        Arrays.fill(r, Integer.MIN_VALUE);

        return memoizedCutRodAux(price, n, r);
    }

    private int memoizedCutRodAux(int[] price, int n, int[] r) {
        if (r[n] >= 0) return r[n];
        int max_val = 0;
        if (n > 0) {
            for (int i = 1; i <= n; i++) {
                max_val = Math.max(max_val, price[i] + memoizedCutRodAux(price, n - i, r));
            }
        }
        r[n] = max_val;
        return max_val;
    }

    int bottomUpCutRod(int[] price, int n) {
        int[] table = new int[n + 1];
        table[0] = 0;
        for (int j = 1; j <= n; j++) {
            int max_val = Integer.MIN_VALUE;
            for (int i = 1; i <= j; i++) {
                max_val = Math.max(max_val, price[i] + table[j - i]);
            }
            table[j] = max_val;
        }
        return table[n];
    }

    RodCuttingResult extendedBottomUpRod(int[] price, int n) {
        int[] r = new int[n + 1];
        int[] s = new int[n + 1];
        r[0] = 0;
        for (int j = 1; j <= n; j++) {
            int max_val = Integer.MIN_VALUE;
            for (int i = 1; i <= j; i++) {
                if (max_val < price[i] + r[j - i]) {
                    max_val = price[i] + r[j - i];
                    s[j] = i;
                }
            }
            r[j] = max_val;
        }

        int k = n;
        List<Integer> cuts = new ArrayList<>();
        while(k > 0) {
            cuts.add(s[k]);
            k = k - s[k];
        }

        return new RodCuttingResult(r[n], cuts);
    }

    class RodCuttingResult {
        int r;
        List<Integer> s;

        RodCuttingResult(int r, List<Integer> s) {
            this.r = r;
            this.s = s;
        }
    }

    //4, { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    //7, { 1, 5, 8, 10, 12, 21, 19, 22, 25, 30 };
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        out.println("Enter the size of the rod");
        int n = ip(br.readLine());
        int prices[] = new int[n + 1];
        out.println("Enter prices of each rod");
        for (int i = 1; i <= n; i++) {
            prices[i] = ip(br.readLine());
        }
        RodCutting rodCutting = new RodCutting();
        int max = rodCutting.cutRod(prices, n);
        out.println("Max using non memoized cutRod: " + max);

        max = rodCutting.memoizedCutRod(prices, n);
        out.println("Max using memoized cutRod: " + max);

        max = rodCutting.bottomUpCutRod(prices, n);
        out.println("Max using memoized bottom up cutRod: " + max);

        final RodCuttingResult rodCuttingResult = rodCutting.extendedBottomUpRod(prices, n);
        out.println("Max using extended memoized bottom up cutRod: "
            + rodCuttingResult.r);
        out.println("rod cut at: "+ rodCuttingResult.s);
    }

    private static int ip(String s) {
        return Integer.parseInt(s);
    }
}

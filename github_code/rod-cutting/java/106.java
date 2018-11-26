package com.github.chauhraj.dynaprog;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import static com.github.chauhraj.Utils.*;
/**
 * Created by chauhraj on 5/30/16.
 */
public class RodCutting {

    private int[] revenue;
    private int[] cuts;

    public RodCutting(int[] price) {
        revenue = new int[price.length];
        cuts = new int[price.length];

        int N = price.length - 1;
        for(int rodSize = 1; rodSize <= N; rodSize++) {
            int revenueOfRodSize = -1;
            for(int otherRodSize = 1; otherRodSize <= rodSize; otherRodSize++) {
                if(revenueOfRodSize < price[otherRodSize] + revenue[rodSize - otherRodSize]) {
                    revenueOfRodSize = price[otherRodSize] + revenue[rodSize - otherRodSize];
                    cuts[rodSize] = otherRodSize;
                }
            }
            revenue[rodSize] = revenueOfRodSize;
        }
    }

    public void solve(int N) {
        System.out.printf("Max Revenue for N=%d is %d and cuts are: %s\n", N, revenue[N], cuts(N));
    }

    private String cuts(int n) {
        String s = "(";
        while(n > 0) {
            s = s.concat("" + cuts[n]).concat(", ");
            n = n - cuts[n];
        }
        s = s + ")";
        return s;
    }

    public static void main(String... args) {
        RodCutting p = new RodCutting(a(0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30));
        int[] sizes = {1, 2, 4, 5, 7, 9, 10};
        for(int n : sizes) {
            p.solve(n);
        }
    }


}

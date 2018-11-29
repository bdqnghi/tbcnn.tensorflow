package me.nithind.algo;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Created by devangn on 27-12-2016.
 */
public class RodCutting {

    int cost[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int sol[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    //Brute Force
    public int solve(int length) {
        if (length == 0) return 0;
        int curMax = -9999;
        for (int i=1; i<=length; i++) {
            curMax = Math.max(curMax, cost[i]+solve(length-i));
        }
        System.out.println("For length = " + length + " value is = "+curMax);
        return curMax;
    }

    public int solveDynamic(int length, int[] memory, Set<Integer> sizes) {
        if(memory[length] != 0){
            //System.out.println("Memory found for l = " + length + " value is = "+memory[length]);
            return memory[length];
        }
        if (length == 0) return 0;
        int curMax = -9999;
        //Integer curMaxI = null;
        for (int i=1; i<=length; i++) {
            int curMax2 = Math.max(curMax, cost[i]+solveDynamic(length-i, memory, sizes));
            if (curMax2 > curMax){
                System.out.println("Maxed for length = "+length +" and i = "+i);
                sol[length] = i;
            }
            curMax = curMax2;

        }
        //sizes.add(curMaxI);
        memory[length] = curMax;
        return curMax;
    }

    public int solveDynamicBottomUp(int length) {
        List<Integer> to = new ArrayList<Integer>();
        int[] memory = {0,0,0,0,0,0,0,0,0,0,0};
        int[] prevCut = {0,0,0,0,0,0,0,0,0,0,0};
        if (length == 0) return 0;
//        int max = -9999;
        for (int i =1; i<=length; i++) {
            int max = -9999;
            for (int j=1; j<=i; j++) {
                int max2 = Math.max(max, cost[j] + memory[i-j]);
                if (max2 != max) {
                    prevCut[i] = i-j;
                    max = max2;
                }
            }
            memory[i] = max;
        }
        int n=length;
        while(n>0) {
            if (prevCut[n] == 0) {
                to.add(n);
                break;
            } else {
                to.add(prevCut[n]);
                n = n - prevCut[n];
            }
        }
        System.out.print("cut into "+to);
        return memory[length];
    }

    public static void main(String[] args) {
        Set<Integer> sizes = new HashSet<Integer>();

        RodCutting rodCutting = new RodCutting();
        int[] memory = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        //System.out.println(rodCutting.solve(4));
        System.out.println(rodCutting.solveDynamic(4, memory, sizes));
        System.out.println("Bottom up "+rodCutting.solveDynamicBottomUp(6));

        System.out.println("Cut into " + sizes);
    }
}

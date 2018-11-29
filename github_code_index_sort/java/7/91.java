package com.ozkuran.algorithms.sorts.shellsort;

import java.util.ArrayList;
import java.util.List;

/**
 * @version 0.0.1.3
 * Created by MahmutAli on 11/9/2009.
 * Last Update by MahmutAli on 1/26/2015.
 * Returns if given Array in sorted order with Shell Sort
 * Worst Case Performance O(n.n)
 * Best Case Performance O(n.logn.logn)
 */
public abstract class ShellSort<T extends Comparable<T>> {
    public static <T extends Comparable<T>> T[] sort(T[] input) {
        int increment = input.length / 2;
        while (increment > 0) {
            for (int i = increment; i < input.length; i++) {
                int j = i;
                T temp = input[i];
                while (j >= increment && input[j - increment].compareTo(temp) > 0) {
                    input[j] = input[j - increment];
                    j = j - increment;
                }
                input[j] = temp;
            }
            if (increment == 2) {
                increment = 1;
            } else {
                increment *= (5.0 / 11);
            }
        }
        return input;
    }
}

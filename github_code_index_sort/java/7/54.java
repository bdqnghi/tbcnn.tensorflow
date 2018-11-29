package com.gerrard.sort.compare.comb;

import com.gerrard.sort.Sort;
import com.gerrard.util.ArrayHelper;

/**
 * Comb-Sort, works as a variation of Bubble-Sort, with complexity O(n^2).
 * Similar to Shell-Sort solution, we introduce the concept "gap".
 * Every time compare the element with gap-distance, and swap when wrong ordered.
 * <p>
 * The gap starts out as the length of the list n being sorted divided by the shrink factor k.
 * The "shrink factor" is suggested as 1.3 by the algorithm author.
 * <p>
 * Comb-Sort is better than Bubble-Sort by reduce the inversion.
 * It decreases swap operation but increases compare operation.
 * Every time it compares from start to end, regardless of whether the end part is already ordered.
 */
public class CombSort implements Sort {

    private double shrink = 1.3;

    public double getShrink() {
        return shrink;
    }

    public void setShrink(double shrink) {
        this.shrink = shrink;
    }

    @Override
    public void sort(int[] array) {
        int gap = array.length;
        boolean sorted = false;
        while (!sorted) {
            gap = (int) (gap / shrink);
            if (gap > 1) {
                sorted = false;
            } else {
                gap = 1;
                sorted = true;
            }
            int i = 0;
            while (i + gap < array.length) {
                if (array[i] > array[i + gap]) {
                    ArrayHelper.swap(array, i, i + gap);
                    sorted = false;
                }
                i++;
            }
        }
    }
}

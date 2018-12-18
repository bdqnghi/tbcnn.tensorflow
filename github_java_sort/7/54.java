package com.gerrard.sort.compare.comb;

import com.gerrard.sort.Sort;
import com.gerrard.util.ArrayHelper;


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

package com.candifood.sorting;

/**
 * Tested: Yes
 * <p/>
 * The bubble-sort algorithm makes various passes over a one-dimensional array.
 * For each pass, that algorithm compares adjacent data items to determine which
 * is numerically larger or smaller. Either the larger data item (for ascending
 * order) or the smaller data item (for descending order) swaps with the
 * adjacent data item and moves toward the bottom of the one-dimensional array.
 * By the end of the pass, the largest/smallest data item has moved toward the
 * array's end. This "bubbling" effect is the origin of the bubble-sort
 * algorithm's name.
 */


public class BubbleSort {

    public static void main(String[] args) {

        int i, pass;
        int[] x = {20, 15, 12, 30, -5, 72, 456};

        for (pass = 0; pass <= x.length - 2; pass++) {

            for (i = 0; i <= x.length - pass - 2; i++) {
                if (x[i] > x[i + 1]) {
                    int temp = x[i];
                    x[i] = x[i + 1];
                    x[i + 1] = temp;
                }
            }
        }
        for (i = 0; i < x.length; i++) {
            System.out.println(x[i]);
        }

    }
}

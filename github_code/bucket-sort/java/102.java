package com.algorithmhelper.generalalgorithms.sorting;

public class BucketSort {

    /**
     * Sorts the array arr.
     *
     * @param arr, the array to be sorted.
     * @throws IllegalArgumentException if arr is null
     */
    public static void sort(int[] arr) {
        if (arr == null)
            throw new IllegalArgumentException("sort with null array");

        int maxValue = maxValue(arr);
        int[] bucket = new int[maxValue+1];

        for (int i = 0; i < bucket.length; i++) {
            bucket[i] = 0;
        }

        for (int i = 0; i < arr.length; i++) {
            bucket[arr[i]]++;
        }

        int out = 0;
        for (int i = 0; i < bucket.length; i++) {
            for (int j = 0; j < bucket[i]; j++) {
                arr[out++] = i;
            }
        }
    }

    /**
     * Helper function to find the max element in an array of integers.
     *
     * @param arr, the array of integers
     * @return the max element in an array of integers
     */
    private static int maxValue(int[] arr) {
        int max = Integer.MIN_VALUE;
        for (int i : arr) {
            if (arr[i] > max)
                max = i;
        }
        return max;
    }
}

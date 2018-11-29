package com.personal.sorting;

public class InsertionSort {

    // https://www.programiz.com/dsa/insertion-sort
    // https://www.geeksforgeeks.org/insertion-sort/
    // traverse towards right and keep on sorting element to put it in appropriate position.
    // Complexity, O(n^2),
    // Minimum time if array is already sorted
    public static void main(String[] args) {
        int[] arr = {64, 25, 12, 96, 11};

        for (int i = 1; i < arr.length; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;

        }

        for (int i : arr) {
            System.out.println(i);
        }
    }
}

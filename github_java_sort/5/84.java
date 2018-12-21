package com.mpakhomov.algorithms.sort;


public class BubbleSort implements Sorting {

    
    static public void sortNaive(int[] a) {
        final int N = a.length;
        for (int i = 0; i < N; i++) {
            for (int j = 1; j < N - i; j++) {
                if (a[j - 1] > a[j]) {
                    swap(a, j - 1, j);
                }
            }
        }
    }

    
    static public void sort(int[] a) {
        boolean swapped = true;
        for (int length = a.length; swapped ; length--) {
            swapped = false;
            for (int j = 1; j < length; j++) {
                if (a[j - 1] > a[j]) {
                    swap(a, j - 1, j);
                    swapped = true;
                }
            }
        }
    }

    static private void swap(int[] a, int i, int j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    @Override
    public void instanceSort(int[] a) {
        sort(a);
    }
}

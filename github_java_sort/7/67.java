package com.varunvats.practice.sorting;

public class Shell extends SortBase {

    private Shell() {
        
    }

    
    public static <T extends Comparable<T>> void sort(T[] a) {
        int N = a.length;
        int h = calculateH(N);
        while (h >= 1) {
            for (int i = h; i < N; i++) {
                for (int j = i; j >= h && less(a[j], a[j - h]); j -= h)
                    exchange(a, j, j - h);
            }
            h = h / 3;
        }
    }

    private static int calculateH(int N) {
        int h = 1;
        while (h < N / 3)
            h = 3 * h + 1;
        return h;
    }
}

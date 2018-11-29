package com.mpakhomov.algorithms.sort;

/**
 * Starting from the beginning of the list, compare every adjacent pair, swap their position if they are not in the
 * right order (the latter one is smaller than the former one). After each iteration, one less element (the last one)
 * is needed to be compared until there are no more elements left to be compared.
 * <p>
 * Optimized version: when no swaps occurred during an iteration, then the array is already in sorted order and we
 * are done
 * <p>
 * Performance: Average: O(n^2), Best: O(n), Worst: O(n^2)
 * Space: O(1) (in-place)
 * Stable: yes
 * Adaptive: yes
 *
 * @see <a href="https://en.wikipedia.org/wiki/Bubble_sort">https://en.wikipedia.org/wiki/Bubble_sort</a>
 * @see <a href="http://www.sorting-algorithms.com/bubble-sort">http://www.sorting-algorithms.com/bubble-sort</a>
 *
 * @author mpakhomov
 * @since 8/26/2015
 */
public class BubbleSort implements Sorting {

    /**
     * naive version of bubble sort
     *
     * @param a array to be sorted
     */
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

    /**
     * optimized version of bubble sort: it immediately exits when there are no swaps, which indicates that
     * the array is sorted
     *
     * @param a array to be sorted
     */
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

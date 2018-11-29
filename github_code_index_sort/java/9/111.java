package com.mpakhomov.algorithms.sort;

/**
 * The algorithm divides the input list into two parts: the sublist of items already sorted, which is built up from left
 * to right at the front (left) of the list, and the sublist of items remaining to be sorted that occupy the rest
 * of the list. Initially, the sorted sublist is empty and the unsorted sublist is the entire input list.
 * The algorithm proceeds by finding the smallest element in the unsorted sublist, exchanging it with the leftmost
 * unsorted element (putting it in sorted order), and moving the sublist boundaries one element to the right.
 * <p>
 * Performance: Average: O(n^2), Best: O(n^2), Worst: O(n^2)
 * Space: O(1) (in-place)
 * Stable: no
 * Adaptive: no
 *
 * @see <a href="https://en.wikipedia.org/wiki/Selection_sort">https://en.wikipedia.org/wiki/Selection_sort</a>
 * @see <a href="http://www.sorting-algorithms.com/selection-sort">http://www.sorting-algorithms.com/selection-sort</a>
 *
 * @author mpakhomov
 * @since 8/24/2015
 */
public class SelectionSort implements Sorting {

    /**
     * sort the array into ascending order
     *
     * @param a array to be sorted
     */
    public static void sort(int a[]) {
        final int N = a.length;
        // we use < N - 1 instead of < N, because we omit the very last iteration (i == N - 1).
        // at that iteration we have a list that consists of one element which already in the right place
        for (int i = 0; i < N - 1; i++) {
            // find the minimum element and exchange it with a[i]
            int indexOfMin = i;
            for (int j = i + 1; j < N; j++) {
                if (a[j] < a[indexOfMin]) {
                    indexOfMin = j;
                }
            }
            if (i != indexOfMin){
                exch(a, i, indexOfMin);
            }
        }
    }

    private static void exch(int a[], int i, int j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    @Override
    public void instanceSort(int[] a) {
        sort(a);
    }
}

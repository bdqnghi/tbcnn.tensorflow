package org.olmec.sorting;

/**
 * Shell sort is a simple extension of insertion sort that gains speed by allowing exchanges of
 * entries that are far apart, to produce partially sorted arrays that can be efficiently sorted,
 * eventually by insertion sort. The idea is to rearrange the array to give it the property that
 * taking every hth entry (starting anywhere) yields a sorted sequence. Such an array is said to be
 * h-sorted.
 *
 * Properties: Not stable - O(1) extra space - O(n^3/2) time as shown (see below) - Adaptive:
 * O(n·lg(n)) time when nearly sorted
 *
 * Average case = O((n log(n))²) Worst case = O((n log(n))²) Best case = O(n) Space Complexity:
 * Worst case = O(1)
 *
 * http://www.sorting-algorithms.com/shell-sort & http://en.wikipedia.org/wiki/Shell_sort
 *
 * @author t0tec (t0tec.olmec@gmail.com)
 * @version $Id$
 * @since 1.0
 */
public class ShellSort {

  /**
   * Sort the array by using shell sort algorithm with Knuth's increment sequence (1, 4, 13, 40,
   * ...)
   *
   * @param array the array
   */
  public <T extends Comparable<T>> void sort(T[] array) {
    int n = array.length;

    // 3x + 1 increment sequence:  1, 4, 13, 40, ...
    int h = 1;
    while (h < n / 3) {
      h = 3 * h + 1;
    }

    while (h >= 1) {
      for (int i = h; i < n; i++) {
        int j = i;
        while (j >= h && less(array[j], array[j - h])) {
          swap(array, j, j - h);
          j -= h;
        }
      }
      h /= 3;
    }
  }

  /**
   * Swap array[i] and array[j]
   *
   * @param array the array
   * @param i     the index i
   * @param j     the index j
   * @param <T>   the type of the objects
   */
  private <T extends Comparable<T>> void swap(T[] array, int i, int j) {
    T swap = array[i];
    array[i] = array[j];
    array[j] = swap;
  }

  /**
   * is i less than j?
   *
   * @param i   object i
   * @param j   object j
   * @param <T> the type of the objects
   * @return true if i is less than j and otherwise false
   */
  private <T extends Comparable<T>> boolean less(T i, T j) {
    return i.compareTo(j) < 0;
  }
}

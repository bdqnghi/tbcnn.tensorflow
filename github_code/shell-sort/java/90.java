package com.linbo.algs.sortings;

/**
 * Created by @linbojin on 21/1/17.
 *  This class provides static methods for sorting an
 *  array using Shellsort with Knuth's increment sequence (1, 4, 13, 40, ...).
 *  Ref: https://github.com/linbojin/algorithms/blob/master/doc/04-ElementarySorts.md#shell-sort
 */
public class Shell {

  private Shell() { }

  public static void sort(Comparable[] a) {
    int n = a.length;

    // 3x+1 increment sequence:  1, 4, 13, 40, 121, 364, 1093, ...
    int h = 1;
    while (h < n/3) h = 3*h + 1;

    while (h >= 1) {
      // h-sort the array
      for (int i = h; i < n; i++) {
        for (int j = i; j >= h && less(a[j], a[j-h]); j -= h) {
          exch(a, j, j-h);
        }
      }
      h /= 3;
    }
  }

  private static boolean less(Comparable v, Comparable w) {
    return v.compareTo(w) < 0;
  }

  private static void exch(Object[] a, int i, int j) {
    Object swap = a[i];
    a[i] = a[j];
    a[j] = swap;
  }

  public static void main(String args[]) {
    Integer[] a = {6,2,1,4,23,11,9,43,97,111,3,5,12,36};

    Shell.sort(a);

    for (int i: a) {
      System.out.print(i + " ");
    }
  }

}

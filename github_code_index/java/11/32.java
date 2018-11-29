/*******************************************************************************
 * Copyright (c) 2014 Nan Zhang.
 * 
 *        Filename:   RadixSort.java
 *         Created:   Oct 23, 2014 
 *          Author:   Nan Zhang 
 *    Organization:   https://github.com/Nan-Zhang
 *            Note:   RadixSort only fit in non-negative numbers sorting. n is number of array elements
 *                    Radix Sort takes O(d*(n+b)) time where b is the base for representing numbers.[see Count Sort]
 *                    If k is the maximum possible value, then d would be  O(log_b(k))
 *                    So overall time complexity is O((n+b)*log_b(k)).
 *                    NOTE if 0 <= k <= n^c where c is a constant. In that case, the complexity becomes O(n*log_b(n))
 *                    If we set b as n, we get the time complexity as O(n).
 *                    In other words, we can sort an array of integers with range from 1 to n^c if the numbers are represented in base n
 *                    http://www.geeksforgeeks.org/radix-sort/ 
 * All rights reserved.
 ******************************************************************************/
package search_sort;

public class RadixSort {
    public int[] countSort(int[] data, int exp, int b) {
        int[] output = new int[data.length];
        int[] count = new int[b];
        for (int i = 0; i < data.length; i++) {
            count[(data[i] / exp) % b]++;
        }
        for (int i = 1; i < b; i++) {
            count[i] += count[i - 1];
        }
        for (int i = data.length - 1; i >= 0; i--) {//NOTE must traverse from last to first, think why?
            output[count[(data[i] / exp) % b] - 1] = data[i];
            count[(data[i] / exp) % b]--;
        }
        return output;
    }

    public int[] radixSort(int[] data, int b) {
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < data.length; i++) {
            max = Math.max(max, data[i]);
        }
        for (int exp = 1; max / exp > 0; exp *= b) {
            data = countSort(data, exp, b);
        }
        return data;
    }

    public static void main(String[] args) {
        RadixSort test = new RadixSort();
        int[] output = test.radixSort(new int[] { 170, 45, 75, 82, 24, 0, 66 }, 6);
        for (int i = 0; i < output.length; i++) {
            System.out.println(output[i]);
        }
    }
}

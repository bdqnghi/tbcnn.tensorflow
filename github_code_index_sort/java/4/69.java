package org.ict.algorithm.sort;

import java.util.Arrays;
import org.ict.algorithm.util.StdIn;
import org.ict.algorithm.util.StdOut;

/**
 *  $ more ../resources/tiny.txt 
 *  S O R T E X A M P L E
 *  $ javac org/ict/algorithm/sort/Heap.java 
 *  Note: org/ict/algorithm/sort/Heap.java uses unchecked or unsafe operations.
 *  Note: Recompile with -Xlint:unchecked for details.
 *  $ java org/ict/algorithm/sort/Heap < ../resources/tiny.txt 
 *  [A, E, E, L, M, O, P, R, S, T, X]
 *
 * 
 * Sorts a sequence of strings from standard input using heapsort.
 *
 * @author Robert Sedgewick
 * @author Kevin Wayne
 */
public class Heap {

    //This class should not be instantiated.
    private Heap() {}

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param pq the array to be sorted
     */
    public static void sort(Comparable[] pq) {
        int n = pq.length;
        // heap construction 
        for (int k = n/2; k >=1; k--) {
            sink(pq, k, n);
        }

        // exchanges the largest element at a[1] with a[N]
        // and then repairs the heap, continuing until 
        // the heap is empty.
        while (n > 1) {
            exch(pq, 1, n--);
            sink(pq, 1, n);
        }
    }

    /**
     * Helper functions to restore the heap invariant.
     */
    private static void sink(Comparable[] pq, int k, int n) {
        while (2*k <= n) {
            int j = 2*k;
            if (j < n && less(pq, j, j+1)) {
                j++;
            }
            if (!less(pq, k, j)) {
                break;
            }
            exch(pq, k, j);
            k = j;
        }
    }

    /**
     * Helper functions for comparisons and swaps.
     * Indices are "off-by-one" to support 1-based indexing.
     */
    private static boolean less(Comparable[] pq, int i, int j) {
        return pq[i-1].compareTo(pq[j-1]) < 0;
    }

    private static void exch(Object[] pq, int i, int j) {
        Object swap = pq[i-1];
        pq[i-1] = pq[j-1];
        pq[j-1] = swap;
    }

    /**
     * Reads in a sequence of strings from standard input; heapsorts them;
     * and prints them to standard output in ascending order.
     */
    public static void main(String[] args) {
        String[] a = StdIn.readAllStrings();
        Heap.sort(a);
        StdOut.println(Arrays.toString(a));
    }
}

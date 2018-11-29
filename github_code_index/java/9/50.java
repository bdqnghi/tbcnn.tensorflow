package algs.sort;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Scanner;

import static algs.sort.Sort.*;

public class Heap {

//    public static void sort(Comparable[] a) {
//        int n = a.length-1;
//        for (int i = n / 2; i >= 1; i--)
//            sink(a, i, n);
//        while (n > 1) {
//            exch(a, n, 1);
//            sink(a, 1, --n);
//        }
//    }
//
//    private static void sink(Comparable[] a, int i, int n) {
//        while (i * 2 <= n) {
//            int j = i * 2;
//            if (j < n && less(a[j], a[j + 1])) j++;
//            if (less(a[i], a[j])) {
//                exch(a, i, j);
//                i = j;
//            } else break;
//        }
//    }

    private Heap() { }

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param pq the array to be sorted
     */
    public static void sort(Comparable[] pq) {
        int n = pq.length;
        for (int k = n/2; k >= 1; k--)
            sink(pq, k, n);
        while (n > 1) {
            exch(pq, 1, n--);
            sink(pq, 1, n);
        }
    }

    /***************************************************************************
     * Helper functions to restore the heap invariant.
     ***************************************************************************/

    private static void sink(Comparable[] pq, int k, int n) {
        while (2*k <= n) {
            int j = 2*k;
            if (j < n && less(pq, j, j+1)) j++;
            if (!less(pq, k, j)) break;
            exch(pq, k, j);
            k = j;
        }
    }

    /***************************************************************************
     * Helper functions for comparisons and swaps.
     * Indices are "off-by-one" to support 1-based indexing.
     ***************************************************************************/
    private static boolean less(Comparable[] pq, int i, int j) {
        return pq[i-1].compareTo(pq[j-1]) < 0;
    }

    private static void exch(Object[] pq, int i, int j) {
        Object swap = pq[i-1];
        pq[i-1] = pq[j-1];
        pq[j-1] = swap;
    }

    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("C:\\Users\\qianji\\IdeaProjects\\Algorithms\\src\\words.txt");
        InputStream inputStream = new FileInputStream(file);
        Scanner scanner = new Scanner(inputStream);
        String s = scanner.nextLine();
        String[] a = s.split(" ");
//        String[] t = new String[a.length + 1];
//        for (int i = 0; i < a.length; i++) {
//            t[i + 1] = a[i];
//        }
//        a = t;
        Heap.sort(a);
        show(a);
    }
}

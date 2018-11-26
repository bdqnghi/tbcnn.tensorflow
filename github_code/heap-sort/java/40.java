package sort;

import static v.ArrayUtils.*;

import java.security.SecureRandom;

import edu.princeton.cs.algs4.StdIn;

/******************************************************************************
 *  http://algs4.cs.princeton.edu/24pq/Heap.java
 *  http://algs4.cs.princeton.edu/24pq/Heap.java.html
 *  Compilation:  javac Heap.java
 *  Execution:    java Heap < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   http://algs4.cs.princeton.edu/24pq/tiny.txt
 *                http://algs4.cs.princeton.edu/24pq/words3.txt
 *  
 *  Sorts a sequence of strings from standard input using heapsort.
 *
 *  % more tiny.txt
 *  S O R T E X A M P L E
 *
 *  % java Heap < tiny.txt
 *  A E E L M O P R S T X                 [ one string per line ]
 *
 *  % more words3.txt
 *  bed bug dad yes zoo ... all bad yet
 *
 *  % java Heap < words3.txt
 *  all bad bed bug dad ... yes yet zoo   [ one string per line ]
 *
 ******************************************************************************/

/**
 *  The {@code Heap} class provides a static methods for heapsorting
 *  an array.
 *  <p>
 *  For additional documentation, see <a href="http://algs4.cs.princeton.edu/24pq">Section 2.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
@SuppressWarnings("unused")
public class Heap {
  public static double compares = 0;

    // This class should not be instantiated.
    private Heap(){}

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param pq the array to be sorted
     */
    public static <T extends Comparable<? super T>> double sort(T[] pq) {
        compares = 0;
        int n = pq.length;
        for (int k = n/2; k >= 1; k--)
            sink(pq, k, n);
        while (n > 1) {
            exch(pq, 1, n--);
            sink(pq, 1, n);
        }
        return compares;
    }

   /***************************************************************************
    * Helper functions to restore the heap invariant.
    ***************************************************************************/

    private static <T extends Comparable<? super T>> void sink(T[] pq, int k, int n) {
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
    private static <T extends Comparable<? super T>> boolean less(T[] pq, int i, int j) {
        compares++;
        return pq[i-1].compareTo(pq[j-1]) < 0;
    }

    private static void exch(Object[] pq, int i, int j) {
        Object swap = pq[i-1];
        pq[i-1] = pq[j-1];
        pq[j-1] = swap;
    }

    // is v < w ?
    private static <T extends Comparable<? super T>> boolean less(T v, T w) {
        return v.compareTo(w) < 0;
    }
        

   /***************************************************************************
    *  Check if array is sorted - useful for debugging.
    ***************************************************************************/
    private static <T extends Comparable<? super T>> boolean isSorted(T[] a) {
        for (int i = 1; i < a.length; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }


    // print array to standard output
    private static <T> void show(T[] a) {
        for (int i = 0; i < a.length; i++) System.out.print(a[i]+" ");
        System.out.println();
    }

    /**
     * Reads in a sequence of strings from standard input; heapsorts them; 
     * and prints them to standard output in ascending order. 
     *
     * @param args the command-line arguments
     */
    public static void main(String[] args) {
      
      SecureRandom sr = new SecureRandom();
      Double[] a = {0.,12.,3.,1.,5.,4.,6.,2.,7.,11.,10.,9.};
      a = rangeDouble(1.,21.);
      shuffle(a,sr);
      //      a = new double[]{5.0,8.0,4.0,18.0,15.0,3.0,12.0,2.0,13.0,1.0,16.0,11.0,20.0,17.0,19.0,6.0,10.0,7.0,14.0,9.0};
      par(a);
      sort(a);
      par(a);
      
//      
//        String[] a = StdIn.readAllStrings();
//        Heap.sort(a);
//        show(a);
//        assert isSorted(a);
    }
}

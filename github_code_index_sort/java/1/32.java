package org.ict.algorithm.sort;
import java.util.Comparator;
import java.util.Arrays;
import org.ict.algorithm.util.StdIn;
import org.ict.algorithm.util.StdOut;


/**
 *  $ javac org/ict/algorithm/sort/Insertion.java 
 *  Note: ./org/ict/algorithm/sort/AbstractSortHelper.java uses unchecked or unsafe operations.
 *  Note: Recompile with -Xlint:unchecked for details.
 *  $ more ../resources/tiny.txt 
 *   S O R T E X A M P L E
 *  $ java org/ict/algorithm/sort/Insertion < ../resources/tiny.txt 
 *   A
 *   E
 *   E
 *   L
 *   M
 *   O
 *   P
 *   R
 *   S
 *   T
 *   X
 *
 *
 *  The {@code Insertion} class provides static methods for sorting an
 *  array using insertion sort.
 *  <p>
 *  This implementation makes ~ 1/2 n^2 compares and exchanges in
 *  the worst case, so it is not suitable for sorting large arbitrary arrays.
 *  More precisely, the number of exchanges is exactly equal to the number
 *  of inversions. So, for example, it sorts a partially-sorted array
 *  in linear time.
 *  <p>
 *  The sorting algorithm is stable and uses O(1) extra memory.
 *  <p>
 *  See <a href="https://algs4.cs.princeton.edu/21elementary/InsertionPedantic.java.html">InsertionPedantic.java</a>
 *  for a version that eliminates the compiler warning.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
public class Insertion extends AbstractSortHelper {
    
    //This class should not be instantiated.
    private Insertion(){}
    
    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
	public static void sort(Comparable[] a) {
		int N = a.length;
		for (int i = 1; i < N; i++) {
			for (int j = i; j > 0 && less(a[j], a[j-1]); j--) {
			    exch(a, j, j-1);
			}
			assert isSorted(a, 0, i);
		}
		assert isSorted(a);
	}
	
	/**
	 * Rearranges the subarray a[lo] to a[hi] in ascending order, using the natural order.
	 * @param a the array to be sorted
     * @param lo left endpoint (inclusive)
     * @param hi right endpoint (exclusive)
	 */
	public static void sort(Comparable[] a, int lo, int hi) {
	    for (int i = lo; i < hi; i++) {
            for (int j = i; j > lo && less(a[j], a[j-1]); j--) {
                StdOut.println("exchange a[" + j + "]:" + a[j]+ " and a[" + (j-1) +"]:" + a[j-1]);
                exch(a, j, j-1);
            }
        }
        assert isSorted(a, lo, hi);
	}
    
    /**
     * Rearranges the array in ascending order, using a comparator.
     * @param a the array
     * @param comparator the comparator specifying the order
     */
    public static void sort(Object[] a, Comparator comparator) {
        int n = a.length;
        for (int i = 0; i < n; i++) {
            for (int j = i; j > 0 && less(a[j], a[j-1], comparator); j--) {
                exch(a, j, j-1);
            }
            assert isSorted(a, 0, i, comparator);
        }
        assert isSorted(a, comparator);
    }

    /**
     * Rearranges the subarray a[lo] to a[hi] in ascending order,
     * using a comparator.
     * @param a the array
     * @param lo left endpoint (inclusive)
     * @param hi right endpoint (exclusive)
     */
    public static void sort(Object[] a, int lo, int hi, Comparator comparator) {
        for (int i = lo; i < hi; i++) {
            for (int j = i; j > lo && less(a[j], a[j-1], comparator); j--) {
                exch(a, j, j-1);
            }
        }
        assert isSorted(a, lo, hi, comparator);
    }

    /**
     * Returns a permutation that gives the elements in the array
     * in ascending order.
     * @param a the array.
     * @return a permutation {@code p[]} such that {@code a[p[0]]},
     * {@code a[p[1]]}, ..., {@code a[p[n-1]]}
     * are in ascending order
     *
     */
    public static int[] indexSort(Comparable[] a) {
        int n = a.length;
        int[] index = new int[n];
        for (int i = 0; i < n; i++) {
            index[i] = i;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i; j > 0 && less(a[index[j]], a[index[j-1]]); j--) {
                exch(index, j, j-1);
            }
        }
        return index;
    }
	
	public static void main(String[] args) {
	    String[] a = StdIn.readAllStrings();
        Insertion.sort(a);
        StdOut.println(Arrays.toString(a));
	}	
}	

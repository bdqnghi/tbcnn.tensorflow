package a4;

import java.util.Arrays;

import edu.princeton.cs.introcs.StdIn;
import edu.princeton.cs.introcs.StdOut;
import edu.princeton.cs.introcs.StdRandom;
import edu.princeton.cs.introcs.Stopwatch;

/*************************************************************************
 *  Compilation:  javac Quick.java
 *  Execution:    java Quick < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   http://algs4.cs.princeton.edu/23quicksort/tiny.txt
 *                http://algs4.cs.princeton.edu/23quicksort/words3.txt
 *
 *  Sorts a sequence of strings from standard input using quicksort.
 *   
 *  % more tiny.txt
 *  S O R T E X A M P L E
 *
 *  % java Quick < tiny.txt
 *  A E E L M O P R S T X                 [ one string per line ]
 *
 *  % more words3.txt
 *  bed bug dad yes zoo ... all bad yet
 *       
 *  % java Quick < words3.txt
 *  all bad bed bug dad ... yes yet zoo    [ one string per line ]
 *
 *
 *  Remark: For a type-safe version that uses static generics, see
 *
 *    http://algs4.cs.princeton.edu/23quicksort/QuickPedantic.java
 *
 *************************************************************************/

/**
 * The <tt>Quick</tt> class provides static methods for sorting an array and
 * selecting the ith smallest element in an array using quicksort.
 * <p>
 * For additional documentation, see <a
 * href="http://algs4.cs.princeton.edu/21elementary">Section 2.1</a> of
 * <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 * 
 * @author Robert Sedgewick
 * @author Kevin Wayne
 */
public class Quick {

	// This class should not be instantiated.
	private Quick() {
	}

	/**
	 * Rearranges the array in ascending order, using the natural order.
	 * 
	 * @param a
	 *            the array to be sorted
	 */
	public static void sort(Comparable[] a) {
		StdRandom.shuffle(a);
		sort(a, 0, a.length - 1);
	}

	// switch over to insertion sort when the data gets smaller than i length
	public static void sort(Double[] a, int cut) {
		sort(a, 0, a.length - 1, cut);
	}

	// quicksort the subarray from a[lo] to a[hi], switching to insertion sort
	// for arrays smaller than cutoff
	private static void sort(Comparable[] a, int lo, int hi, int cut) {
		int N = hi - lo + 1;

		// cutoff to insertion sort
		if (N <= cut) {
			insertionSort(a, lo, hi);
			return;
		}

		if (hi <= lo)
			return;
		int j = partition(a, lo, hi);
		sort(a, lo, j - 1, cut);
		sort(a, j + 1, hi, cut);
		assert isSorted(a, lo, hi);
	}

	// quicksort the subarray from a[lo] to a[hi]
	private static void sort(Comparable[] a, int lo, int hi) {
		sort(a, lo, hi, Integer.MAX_VALUE);
	}

	// Insertion Sort:
	// http://algs4.cs.princeton.edu/23quicksort/QuickX.java.html
	private static void insertionSort(Comparable[] a, int lo, int hi) {
		for (int i = lo; i <= hi; i++)
			for (int j = i; j > lo && less(a[j], a[j - 1]); j--)
				exch(a, j, j - 1);
	}

	// partition the subarray a[lo..hi] so that a[lo..j-1] <= a[j] <= a[j+1..hi]
	// and return the index j.
	private static int partition(Comparable[] a, int lo, int hi) {
		int i = lo;
		int j = hi + 1;
		Comparable v = a[lo];
		while (true) {

			// find item on lo to swap
			while (less(a[++i], v))
				if (i == hi)
					break;

			// find item on hi to swap
			while (less(v, a[--j]))
				if (j == lo)
					break; // redundant since a[lo] acts as sentinel

			// check if pointers cross
			if (i >= j)
				break;

			exch(a, i, j);
		}

		// put partitioning item v at a[j]
		exch(a, lo, j);

		// now, a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
		return j;
	}

	/**
	 * Rearranges the array so that a[k] contains the kth smallest key; a[0]
	 * through a[k-1] are less than (or equal to) a[k]; and a[k+1] through
	 * a[N-1] are greater than (or equal to) a[k].
	 * 
	 * @param a
	 *            the array
	 * @param k
	 *            find the kth smallest
	 */
	public static Comparable select(Comparable[] a, int k) {
		if (k < 0 || k >= a.length) {
			throw new IndexOutOfBoundsException(
					"Selected element out of bounds");
		}
		StdRandom.shuffle(a);
		int lo = 0, hi = a.length - 1;
		while (hi > lo) {
			int i = partition(a, lo, hi);
			if (i > k)
				hi = i - 1;
			else if (i < k)
				lo = i + 1;
			else
				return a[i];
		}
		return a[lo];
	}

	/***********************************************************************
	 * Helper sorting functions
	 ***********************************************************************/

	// is v < w ?
	private static boolean less(Comparable v, Comparable w) {
		return (v.compareTo(w) < 0);
	}

	// exchange a[i] and a[j]
	private static void exch(Object[] a, int i, int j) {
		Object swap = a[i];
		a[i] = a[j];
		a[j] = swap;
	}

	/***********************************************************************
	 * Check if array is sorted - useful for debugging
	 ***********************************************************************/
	private static boolean isSorted(Comparable[] a) {
		return isSorted(a, 0, a.length - 1);
	}

	private static boolean isSorted(Comparable[] a, int lo, int hi) {
		for (int i = lo + 1; i <= hi; i++)
			if (less(a[i], a[i - 1]))
				return false;
		return true;
	}

	// print array to standard output
	private static void show(Comparable[] a) {
		for (int i = 0; i < a.length; i++) {
			StdOut.println(a[i]);
		}
	}


	/**
	 * Empirically determine the value of M for which quicksort runs fastest in
	 * your computing environment to sort random arrays of N doubles, for N = 10
	 * 3 , 10 4 , 10 5 , and 10 6 . Plot average running times for M from 0 to
	 * 30 for each value of M. 
	 */
	public static void main(String[] args) {
		runExp(1000);
		runExp(10000);
		runExp(100000);
		runExp(1000000);
	}

	private static void runExp(int N) {
		Double[] big = getArray(N);
		StdOut.printf("Running experiment for N=%d with 3 trials per M\n", N);
		StdOut.println("  M  :  time  ");
		double[] time = new double[31];
		for (int M = 0; M <= 30; M++) {
			time[M] = 0;
			for (int i = 0; i < 3; i++) {
				StdRandom.shuffle(big);
				time[M] += TimeQuickSort(big, M);
			}
			StdOut.printf(" %3d : %1.5f \n", M, time[M] / 3.0);
			//StdOut.printf(" %3d & %1.5f \\\\ \n", M, time[M] / 3.0);//printing for LaTeX table
		}
		StdOut.printf("For N  = %d, the best M value is: %d \n",N, analyse(time));
	}

	//determine best M value for this machine
	private static int analyse(double[] time) {
		double best = 400;
		int bestM = -1;
		for (int i = 0; i < time.length; i++) {
			if(time[i] < best) {best = time[i]; bestM = i; }
		}
		return bestM;
	}

	private static double TimeQuickSort(Double[] a, int cutoff) {
		Stopwatch watch = new Stopwatch();
		Quick.sort(a, cutoff);
		return watch.elapsedTime();
	}

	private static Double[] getArray(int n) {
		Double[] a = new Double[n];
		for (int i = 0; i < a.length; i++) {
			a[i] = StdRandom.uniform();
		}
		return a;
	}
}

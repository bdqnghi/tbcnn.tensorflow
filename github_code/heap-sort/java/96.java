package algs24;
import stdlib.*;
/* ***********************************************************************
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
 *************************************************************************/

public class Heap {

	public static <T extends Comparable<? super T>> void sort(T[] pq) {
		int N = pq.length;
		for (int k = N/2; k >= 1; k--) {
			sink(pq, k, N);
		}
		while (N > 1) {
			exch(pq, 1, N);
			N--;
			sink(pq, 1, N);
		}
	}

	/* *********************************************************************
	 * Helper functions to restore the heap invariant.
	 **********************************************************************/

	private static <T extends Comparable<? super T>> void sink(T[] pq, int k, int N) {
		while (2*k <= N) {
			int j = 2*k;
			if (j < N && less(pq, j, j+1)) j++;
			if (!less(pq, k, j)) break;
			exch(pq, k, j);
			k = j;
		}
	}

	/* *********************************************************************
	 * Helper functions for comparisons and swaps.
	 * Indices are "off-by-one" to support 1-based indexing.
	 **********************************************************************/
	private static <T extends Comparable<? super T>> boolean less(T[] pq, int i, int j) {
		if (COUNT_OPS) DoublingTest.incOps ();
		return pq[i-1].compareTo(pq[j-1]) < 0;
	}

	private static <T> void exch(T[] pq, int i, int j) {
		if (COUNT_OPS) DoublingTest.incOps ();
		T swap = pq[i-1];
		pq[i-1] = pq[j-1];
		pq[j-1] = swap;
	}

	// is v < w ?
	private static <T extends Comparable<? super T>> boolean less(T v, T w) {
		if (COUNT_OPS) DoublingTest.incOps ();
		return (v.compareTo(w) < 0);
	}


	/* *********************************************************************
	 *  Check if array is sorted - useful for debugging
	 ***********************************************************************/
	private static <T extends Comparable<? super T>> boolean isSorted(T[] a) {
		for (int i = 1; i < a.length; i++)
			if (less(a[i], a[i-1])) return false;
		return true;
	}


	// print array to standard output
	private static <T> void show(T[] a) {
		for (T element : a) {
			StdOut.println(element);
		}
	}


	// test code
	private static boolean COUNT_OPS = false;
	public static void main(String[] args) {
		//String[] cards = In.readStrings ("data/cards.txt");
		//StdRandom.shuffle (cards);

		//StdIn.fromFile ("data/tiny.txt");
		//StdIn.fromFile ("data/cards.txt");
		//StdIn.fromFile ("data/words3.txt");

		String[] a = StdIn.readAllStrings();
		sort(a);
		show(a);

		DoublingTest.run (2000, 5, N -> ArrayGenerator.integerRandomUnique (N),          (Integer[] x) -> sort (x));
		DoublingTest.run (2000, 5, N -> ArrayGenerator.integerRandom (N, 2),             (Integer[] x) -> sort (x));
		DoublingTest.run (2000, 5, N -> ArrayGenerator.integerPartiallySortedUnique (N), (Integer[] x) -> sort (x));
	}
}

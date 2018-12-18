

package problemset06;

import java.util.Comparator;


public class Merge {
	private static final int CUTOFF = 7;

	
	private Merge() {
	}

	

	
	private static boolean less(Object a, Object b, Comparator comparator) {
		return comparator.compare(a, b) < 0;
	}

	
	private static void merge(Comparable[] a, Comparable[] aux, int lo, int mid, int hi) {
		
		
		

		
		for (int k = lo; k <= hi; k++) {
			aux[k] = a[k];
		}

		
		int i = lo, j = mid + 1;
		for (int k = lo; k <= hi; k++) {
			if (i > mid)
				a[k] = aux[j++];
			else if (j > hi)
				a[k] = aux[i++];
			else if (less(aux[j], aux[i]))
				a[k] = aux[j++];
			else
				a[k] = aux[i++];
		}

		
		
	}

	
	private static void sort(Comparable[] a, Comparable[] aux, int lo, int hi) {
		
		
		
		if (hi <= lo + CUTOFF) {
			insertionSort(aux, lo, hi);
			return;
		}

		int mid = lo + (hi - lo) / 2;
		sort(a, aux, lo, mid);
		sort(a, aux, mid + 1, hi);
		merge(a, aux, lo, mid, hi);
	}

	
	public static void sort(Comparable[] a) {
		Comparable[] aux = new Comparable[a.length];
		sort(a, aux, 0, a.length - 1);
		assert isSorted(a);
	}

	
	private static void insertionSort(Comparable[] a, int lo, int hi) {
		for (int i = lo; i <= hi; i++)
			for (int j = i; j > lo && less(a[j], a[j - 1]); j--)
				exch(a, j, j - 1);
	}

	

	
	private static boolean less(Comparable v, Comparable w) {
		return v.compareTo(w) < 0;
	}

	
	private static void exch(Object[] a, int i, int j) {
		Object swap = a[i];
		a[i] = a[j];
		a[j] = swap;
	}

	
	private static boolean isSorted(Comparable[] a) {
		return isSorted(a, 0, a.length - 1);
	}

	private static boolean isSorted(Comparable[] a, int lo, int hi) {
		for (int i = lo + 1; i <= hi; i++)
			if (less(a[i], a[i - 1]))
				return false;
		return true;
	}

	
	
	private static void merge(Comparable[] a, int[] index, int[] aux, int lo, int mid, int hi) {

		
		for (int k = lo; k <= hi; k++) {
			aux[k] = index[k];
		}

		
		int i = lo, j = mid + 1;
		for (int k = lo; k <= hi; k++) {
			if (i > mid)
				index[k] = aux[j++];
			else if (j > hi)
				index[k] = aux[i++];
			else if (less(a[aux[j]], a[aux[i]]))
				index[k] = aux[j++];
			else
				index[k] = aux[i++];
		}
	}

	
	
	
	
	
	
	
	
	
	
	

	
	private static void sort(Comparable[] a, int[] index, int[] aux, int lo, int hi, Comparator comparator) {
		
		if (hi <= lo + CUTOFF) {
			insertionSort(a, lo, hi, comparator);
			return;
		}
		int mid = lo + (hi - lo) / 2;
		sort(a, index, aux, lo, mid, comparator);
		sort(a, index, aux, mid + 1, hi, comparator);
		merge(a, index, aux, lo, mid, hi);
	}

	
	private static void show(Comparable[] a) {
		for (int i = 0; i < a.length; i++) {
			StdOut.println(a[i]);
		}
	}

	
	private static void insertionSort(Comparable[] a, int lo, int hi, Comparator comparator) {
		for (int i = lo; i <= hi; i++)
			for (int j = i; j > lo && less(a[j], a[j - 1], comparator); j--)
				exch(a, j, j - 1);
	}

	
	public static void main(String[] args) {
		String[] a = StdIn.readAllStrings();
		Merge.sort(a);
		show(a);
	}
}



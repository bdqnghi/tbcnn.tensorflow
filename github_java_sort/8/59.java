package a4;

import java.util.Arrays;

import edu.princeton.cs.introcs.StdIn;
import edu.princeton.cs.introcs.StdOut;
import edu.princeton.cs.introcs.StdRandom;
import edu.princeton.cs.introcs.Stopwatch;




public class Quick {

	
	private Quick() {
	}

	
	public static void sort(Comparable[] a) {
		StdRandom.shuffle(a);
		sort(a, 0, a.length - 1);
	}

	
	public static void sort(Double[] a, int cut) {
		sort(a, 0, a.length - 1, cut);
	}

	
	
	private static void sort(Comparable[] a, int lo, int hi, int cut) {
		int N = hi - lo + 1;

		
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

	
	private static void sort(Comparable[] a, int lo, int hi) {
		sort(a, lo, hi, Integer.MAX_VALUE);
	}

	
	
	private static void insertionSort(Comparable[] a, int lo, int hi) {
		for (int i = lo; i <= hi; i++)
			for (int j = i; j > lo && less(a[j], a[j - 1]); j--)
				exch(a, j, j - 1);
	}

	
	
	private static int partition(Comparable[] a, int lo, int hi) {
		int i = lo;
		int j = hi + 1;
		Comparable v = a[lo];
		while (true) {

			
			while (less(a[++i], v))
				if (i == hi)
					break;

			
			while (less(v, a[--j]))
				if (j == lo)
					break; 

			
			if (i >= j)
				break;

			exch(a, i, j);
		}

		
		exch(a, lo, j);

		
		return j;
	}

	
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

	

	
	private static boolean less(Comparable v, Comparable w) {
		return (v.compareTo(w) < 0);
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

	
	private static void show(Comparable[] a) {
		for (int i = 0; i < a.length; i++) {
			StdOut.println(a[i]);
		}
	}


	
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
			
		}
		StdOut.printf("For N  = %d, the best M value is: %d \n",N, analyse(time));
	}

	
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

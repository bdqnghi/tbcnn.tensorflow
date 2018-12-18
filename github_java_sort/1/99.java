package com.mijiang.algo.sort;



import java.util.Comparator;

import com.mijiang.algo.common.StdIn;
import com.mijiang.algo.common.StdOut;
import static com.mijiang.algo.sort.SortHelper.*;


public class Insertion {

	
	private Insertion() {
	}

	
	public static void sort(Comparable[] a) {
		int N = a.length;
		for (int i = 0; i < N; i++) {
			for (int j = i; j > 0 && less(a[j], a[j - 1]); j--) {
				exch(a, j, j - 1);
			}
			assert isSorted(a, 0, i);
		}
		assert isSorted(a);
	}
	
	public static void sort(Comparable[] a, int lo, int hi){
		for (int i = lo + 1; i <= hi; i++){
			for (int j = i; j > lo && less(a[j], a[j - 1]); j--)
				exch(a, j, j - 1);
		}
	}

	
	public static void sort(Object[] a, Comparator c) {
		int N = a.length;
		for (int i = 0; i < N; i++) {
			for (int j = i; j > 0 && less(c, a[j], a[j - 1]); j--) {
				exch(a, j, j - 1);
			}
			assert isSorted(a, c, 0, i);
		}
		assert isSorted(a, c);
	}

	
	
	
	public static int[] indexSort(Comparable[] a) {
		int N = a.length;
		int[] index = new int[N];
		for (int i = 0; i < N; i++)
			index[i] = i;

		for (int i = 0; i < N; i++)
			for (int j = i; j > 0 && less(a[index[j]], a[index[j - 1]]); j--)
				exch(index, j, j - 1);

		return index;
	}

	

	

	
	public static void main(String[] args) {
		String[] a = StdIn.readAllStrings();
		Insertion.sort(a);
		show(a);
	}
}

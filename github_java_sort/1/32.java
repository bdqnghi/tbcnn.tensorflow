package org.ict.algorithm.sort;
import java.util.Comparator;
import java.util.Arrays;
import org.ict.algorithm.util.StdIn;
import org.ict.algorithm.util.StdOut;



public class Insertion extends AbstractSortHelper {
    
    
    private Insertion(){}
    
    
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
	
	
	public static void sort(Comparable[] a, int lo, int hi) {
	    for (int i = lo; i < hi; i++) {
            for (int j = i; j > lo && less(a[j], a[j-1]); j--) {
                StdOut.println("exchange a[" + j + "]:" + a[j]+ " and a[" + (j-1) +"]:" + a[j-1]);
                exch(a, j, j-1);
            }
        }
        assert isSorted(a, lo, hi);
	}
    
    
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

    
    public static void sort(Object[] a, int lo, int hi, Comparator comparator) {
        for (int i = lo; i < hi; i++) {
            for (int j = i; j > lo && less(a[j], a[j-1], comparator); j--) {
                exch(a, j, j-1);
            }
        }
        assert isSorted(a, lo, hi, comparator);
    }

    
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

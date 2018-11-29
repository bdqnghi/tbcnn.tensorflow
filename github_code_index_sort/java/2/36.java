package javaAlgorithms.section2.mergeSort;

import javaAlgorithms.section2.Sort;
import javaAlgorithms.section2.SortingStub;

/**
 * top down mergesort
 */
public class Merge extends SortingStub implements Sort {

    private Comparable[] aux; // auxiliary array for merges

    public void sort(Comparable[] a) {
        aux = new Comparable[a.length];
        sort(a, 0, a.length - 1);
    }

    private void sort(Comparable[] a, int lo, int hi) {
        if (hi <= lo)
            return;

        int mid = lo + (hi - lo)/2;

        sort(a, lo, mid); // sort left half
        sort(a, mid + 1, hi); // sort right half

        merge(a, lo, mid, hi);
    }
}

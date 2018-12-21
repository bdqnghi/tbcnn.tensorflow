package javaAlgorithms.section2.mergeSort;

import javaAlgorithms.section2.Sort;
import javaAlgorithms.section2.SortingStub;


public class Merge extends SortingStub implements Sort {

    private Comparable[] aux; 

    public void sort(Comparable[] a) {
        aux = new Comparable[a.length];
        sort(a, 0, a.length - 1);
    }

    private void sort(Comparable[] a, int lo, int hi) {
        if (hi <= lo)
            return;

        int mid = lo + (hi - lo)/2;

        sort(a, lo, mid); 
        sort(a, mid + 1, hi); 

        merge(a, lo, mid, hi);
    }
}


package com.mycompany.snsp1;

import java.util.Comparator;


public class Merge {

    
    private Comparable[] array;
    private Comparable[] mergeArr;

    Comparator<Student> comp = new Comparator<Student>() {
        @Override
        public int compare(Student t1, Student t2) {
            return t1.compareTo(t2);
        }
    };

    
    public Merge(Comparable[] array) {
        this.array = array;
        this.mergeArr = new Comparable[array.length];

        chop(0, array.length - 1, comp);
    }

    
    private void chop(int laag, int hoog, Comparator comp) {
        if (laag < hoog) {
            if (hoog - laag < 10) {
                insertionSort(array, laag, hoog, comp);
            }
            int middel = laag + (hoog - laag) / 2;

            chop(laag, middel, comp);
            chop(middel + 1, hoog, comp);
            mergeAll(laag, middel, hoog, comp);
        }

    }

    
    private void mergeAll(int laag, int middel, int hoog, Comparator comp) {
        for (int i = laag; i <= hoog; i++) {
            mergeArr[i] = array[i];
        }
        int i = laag;
        int j = middel + 1;
        int k = laag;
        while (i <= middel && j <= hoog) {
            if (comp.compare(mergeArr[i], mergeArr[j]) < 0) {
                array[k] = mergeArr[i];
                i++;
            } else {
                array[k] = mergeArr[j];
                j++;
            }
            k++;
        }

        while (i <= middel) {
            array[k] = mergeArr[i];
            k++;
            i++;
        }
    }

    
    private void insertionSort(Comparable[] a, int laag, int hoog, Comparator comp) {
        for (int i = laag; i < hoog; i++) {
            for (int j = i; j > laag && isLager(a[j], a[j - 1], comp); j--) {
                isHoger(a, j, j - 1, comp);
            }
        }
    }

    
    private void isHoger(Comparable[] a, int i, int j, Comparator comp) {
        Comparable temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    
    private boolean isLager(Comparable a, Comparable b, Comparator comp) {
        return a.compareTo(b) < 0;
    }
}

/*
 * Deze klasse is een API van het boek: Algorithhms 4th Edition by Robert Sedgewick, Kevin Wayne.
 * Er zijn een aantal aanpassingen gedaan, om de code wat sneller te maken. We hebben bijvoorbeeld
 * voor kleine arrays ervoor gezorgd dat deze gesorteerd worden met insertion-sort, omdat insertion-sort
 * sneller is met sorteren van kleine arrays.
 */
package com.mycompany.snsp1;

import java.util.Comparator;

/**
 *
 * @author Miguel & Jordi
 */
public class Merge {

    // Twee lege Arrays. array word gevuld in de constructor en mergeArr krijg een lengte, maar blijft hier leeg.
    private Comparable[] array;
    private Comparable[] mergeArr;

    Comparator<Student> comp = new Comparator<Student>() {
        @Override
        public int compare(Student t1, Student t2) {
            return t1.compareTo(t2);
        }
    };

    /**
     *
     * @param array is een comparable array van objecten.
     */
    public Merge(Comparable[] array) {
        this.array = array;
        this.mergeArr = new Comparable[array.length];

        chop(0, array.length - 1, comp);
    }

    /**
     * Deze methode hakt de grote array in kleine stukjes om ze sneller te
     * kunnen sorteren. Als de array kleiner dan 10 is, word dit stuk van de
     * array gesorteerd met insertion-sort. Deze methode is recursief.
     *
     * @param laag = index in array.
     * @param hoog = index in array.
     * @param comp = Comparator.
     */
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

    /**
     * Deze methode sorteert de grotere arrays. In dit geval alle arrays die
     * groter zijn dan 9 indexen groot.
     *
     * @param laag = index in array.
     * @param middel = index in array.
     * @param hoog = index in array
     * @param comp = Comparator.
     */
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

    /**
     * Deze methode loopt door de array heen en maakt gebruik van de methodes
     * isLager en isHoger om de array te sorteren.
     *
     * @param a = Comparable array.
     * @param laag = de kleinste index in array.
     * @param hoog = de grootste index in array.
     * @param comp = Comparator
     */
    private void insertionSort(Comparable[] a, int laag, int hoog, Comparator comp) {
        for (int i = laag; i < hoog; i++) {
            for (int j = i; j > laag && isLager(a[j], a[j - 1], comp); j--) {
                isHoger(a, j, j - 1, comp);
            }
        }
    }

    /**
     *
     * @param a = Comparable array.
     * @param i = index in array.
     * @param j = index in array.
     * @param comp = Comparator.
     */
    private void isHoger(Comparable[] a, int i, int j, Comparator comp) {
        Comparable temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    /**
     *
     * @param a = Comparable array.
     * @param b = Comparable array.
     * @param comp = Comparator.
     * @return true or false als het lager is.
     */
    private boolean isLager(Comparable a, Comparable b, Comparator comp) {
        return a.compareTo(b) < 0;
    }
}

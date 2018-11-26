package com.aadityatiwari.java.tryouts;

import static org.junit.Assert.assertTrue;

import java.util.Random;

import com.aadityatiwari.algorithms.sorts.QuickSort;

public class QuickSort_Main {

    private static final Random RANDOM = new Random();
    private static final int SIZE = 10000;

    private static Integer[] unsorted = null;
    private static Integer[] sorted = null;
    private static Integer[] reverse = null;

    static {
        unsorted = new Integer[SIZE];
        int i = 0;
        while (i < unsorted.length) {
            int j = RANDOM.nextInt(unsorted.length * 10);
            unsorted[i++] = j;
        }

        sorted = new Integer[SIZE];
        for (i = 0; i < sorted.length; i++)
            sorted[i] = i;

        reverse = new Integer[SIZE];
        for (i = (reverse.length - 1); i >= 0; i--)
            reverse[i] = (SIZE - 1) - i;
    }

    private static final String print(Integer[] array) {
        return print(array, 0, array.length);
    }

    private static final String print(Integer[] array, int start, int length) {
        final Integer[] clone = array.clone();
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i<length; i++) {
            int e = clone[start+i];
            builder.append(e+" ");
        }
        return builder.toString();
    }

    private static final boolean check(Integer[] array) {
        for (int i = 1; i<array.length; i++) {
            if (array[i-1]>array[i])
                return false;
        }
        return true;
    }


	public static void main(String[] args) {
		// Quicksort
		Integer[] result = QuickSort.sort(QuickSort.PIVOT_TYPE.FIRST, unsorted.clone());
		result = QuickSort.sort(QuickSort.PIVOT_TYPE.FIRST, sorted.clone());
		assertTrue("Quick sort pivot firt sorted error. result=" + print(result), check(result));
		result = QuickSort.sort(QuickSort.PIVOT_TYPE.FIRST, reverse.clone());
		assertTrue("Quick sort pivot firt reverse error. result=" + print(result), check(result));
		result = QuickSort.sort(QuickSort.PIVOT_TYPE.MIDDLE, unsorted.clone());
		assertTrue("Quick sort pivot middle unsorted error. result=" + print(result), check(result));
		result = QuickSort.sort(QuickSort.PIVOT_TYPE.MIDDLE, sorted.clone());
		assertTrue("Quick sort pivot middle sorted error. result=" + print(result), check(result));
		result = QuickSort.sort(QuickSort.PIVOT_TYPE.MIDDLE, reverse.clone());
		assertTrue("Quick sort pivot middle reverse error. result=" + print(result), check(result));
		result = QuickSort.sort(QuickSort.PIVOT_TYPE.RANDOM, unsorted.clone());
		assertTrue("Quick sort pivot random unsorted error. result=" + print(result), check(result));
		result = QuickSort.sort(QuickSort.PIVOT_TYPE.RANDOM, sorted.clone());
		assertTrue("Quick sort pivot random sorted error. result=" + print(result), check(result));
		result = QuickSort.sort(QuickSort.PIVOT_TYPE.RANDOM, reverse.clone());
		assertTrue("Quick sort pivot random reverse error. result=" + print(result), check(result));

	}

}

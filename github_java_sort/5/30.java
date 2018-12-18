package com.ericzong.algorithm.sort;

import java.lang.reflect.Array;
import java.util.Comparator;


public class Bubble {
    public static <E extends Comparable<E>> void sort(E[] data) {
        sortImpl(data, null);
    }

    public static void sort(int[] data) {
        sortImpl(data, null);
    }

    public static <E> void sort(E[] data, Comparator<E> comparator) {
        sortImpl(data, comparator);
    }

    private static void sortImpl(Object data, Comparator comparator) {
        int length = Array.getLength(data);
        if (length <= 1) return;

        for (int i = 0; i < length; i++) {
            boolean swap = false;
            for (int j = 0; j < length - i - 1; j++) {
                swap |= swap(data, j, j + 1, comparator);
            }

            if (!swap) { 
                break;
            }
        }
    }

    private static boolean swap(Object data, int i, int j, Comparator comparator) {
        if (!data.getClass().isArray()) {
            throw new RuntimeException("Not Array");
        }

        Object first = Array.get(data, i);
        Object second = Array.get(data, j);

        if (isOrdered(first, second, comparator)) {
            return false;
        }

        Array.set(data, i, second);
        Array.set(data, j, first);

        return true;
    }

    private static boolean isOrdered(Object first, Object second, Comparator comparator) {
        if (comparator != null) {
            return comparator.compare(first, second) <= 0;
        } else if (first instanceof Comparable) {
            return ((Comparable) first).compareTo(second) <= 0;
        }

        throw new RuntimeException("Uncomparable!");
    }
}

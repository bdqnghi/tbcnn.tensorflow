package com.reggie.algs4.ch2_sorting.other;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;


public class Bucket {
    public static void sort(int[] a, int M) {
        int N = a.length;
        int min = a[0], max = a[0];
        for (int value : a) {
            if (value < min) {
                min = value;
                continue;
            }
            if (value > max) {
                max = value;
            }
        }
        int d = (max - min) / M;
        List[] buckets = new List[M + 1];
        for (List bucket : buckets) {
            bucket = new ArrayList();
        }
        for (int value : a) {
            List bucket = buckets[(value - min) / d];
            bucket.add(value);
        }
        for (List bucket : buckets) {
            if (bucket.size() != 0)
                bucket.sort(new IntegerComparator());
        }
        int k = 0;
        for (List bucket : buckets) {
            for (Object value : bucket) {
                a[k++] = (int) value;
            }
        }
    }

    private static class IntegerComparator implements Comparator<Integer> {

        @Override
        public int compare(Integer o1, Integer o2) {
            if (o1 < o2) return -1;
            else if (o1 > o2) return 1;
            else return 0;
        }
    }
}

/*
 * Copyright 2012 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.mingle.orange.arithmetic.sort;

import org.mingle.orange.util.SortUtils;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * @author mingle
 */
public class Quick {
    private static final int M = 10;

    public static <T extends Comparable<T>> void sort(List<T> a) {
        Collections.shuffle(a);
        sort(a, 0, a.size() - 1);
    }

    private static <T extends Comparable<T>> void sort(List<T> a, int lo, int hi) {
        if (hi <= lo + M) {
            Insertion.sort(a, lo, hi);
            return;
        }

        int j = partition(a, lo, hi);

        sort(a, lo, j - 1);
        sort(a, j + 1, hi);
    }

    /**
     * 中位数作为枢纽元
     *
     * @param a
     */
    public static <T extends Comparable<T>> void mediansort(List<T> a) {
        Collections.shuffle(a);
        mediansort(a, 0, a.size() - 1);
    }

    private static <T extends Comparable<T>> void mediansort(List<T> a, int lo, int hi) {
        if (hi <= lo + M) {
            Insertion.sort(a, lo, hi);
            return;
        }

        T pivot = SortUtils.median(a, lo, hi);
        int i = lo, j = hi - 1; // begin partitioning

        for (; ; ) {
            while (a.get(++i).compareTo(pivot) < 0) ;
            while (pivot.compareTo(a.get(--j)) < 0) ;
            if (i < j)
                SortUtils.exchange(a, i, j);
            else break;
        }

        SortUtils.exchange(a, i, hi - 1); // restore pivot

        mediansort(a, lo, i - 1);
        mediansort(a, i + 1, hi);
    }

    private static <T extends Comparable<T>> int partition(List<T> a, int lo, int hi) {
        int i = lo;
        int j = hi + 1;

        T v = a.get(lo);

        while (true) {
            while (SortUtils.less(a.get(++i), v)) if (i == hi) break;
            while (SortUtils.less(v, a.get(--j))) if (j == lo) break;

            if (i >= j) break;
            SortUtils.exchange(a, i, j);
        }

        SortUtils.exchange(a, lo, j);

        return j;
    }

    public static void main(String[] args) {
        Integer[] arr = {4, 5, 2, 11, 12, 13, 1, 3, 9, 8, 7, 6, 10};
        List<Integer> array = Arrays.asList(arr);
        sort(array);

        assert SortUtils.isSorted(array);

        SortUtils.show(array);

        mediansort(array);

        assert SortUtils.isSorted(array);

        SortUtils.show(array);
    }
}

/*
 * The MIT License
 *
 * Copyright 2017 Matthias Fussenegger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
package org.sort_search_lib.java.sort;

import org.sort_search_lib.java.sort.api.InPlaceSort;
import java.util.Comparator;

/**
 * Offers the Shell-Sort algorithm to sort an array consisting of any type in
 * ascending order or by using a specified {@link Comparator}.
 *
 * @author Matthias Fussenegger
 */
public final class ShellSort implements InPlaceSort {

    @Override
    @SuppressWarnings("unchecked")
    public <T> void sort(T[] values) {
        if (values != null && values.length > 1) {
            /*calculate gap using Knuth-sequence*/
            int gap = 1;
            while (gap <= Math.ceil(values.length / 3)) {
                gap *= 3 + 1;
            }

            while (gap > 0) {
                /*do insertion sort*/
                for (int i = gap; i < values.length; ++i) {
                    T temp = values[i];
                    int j = i;
                    while (j >= gap && ((Comparable<? super T>) values[j - gap]).compareTo(temp) > 0) {
                        values[j] = values[j - gap];
                        j -= gap;
                    }
                    values[j] = temp;
                }
                gap /= 3;
            }
        }
    }

    @Override
    public <T> void sort(T[] values, Comparator<? super T> c) {
        if (values != null && values.length > 1) {
            /*calculate gap using Knuth-sequence*/
            int gap = 1;
            while (gap <= Math.ceil(values.length / 3)) {
                gap *= 3 + 1;
            }

            while (gap > 0) {
                /*do insertion sort*/
                for (int i = gap; i < values.length; ++i) {
                    T temp = values[i];
                    int j = i;
                    while (j >= gap && c.compare(values[j - gap], temp) > 0) {
                        values[j] = values[j - gap];
                        j -= gap;
                    }
                    values[j] = temp;
                }
                gap /= 3;
            }
        }
    }
}

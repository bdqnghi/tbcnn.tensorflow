
package org.sort_search_lib.java.sort;

import org.sort_search_lib.java.sort.api.InPlaceSort;
import java.util.Comparator;


public final class ShellSort implements InPlaceSort {

    @Override
    @SuppressWarnings("unchecked")
    public <T> void sort(T[] values) {
        if (values != null && values.length > 1) {
            
            int gap = 1;
            while (gap <= Math.ceil(values.length / 3)) {
                gap *= 3 + 1;
            }

            while (gap > 0) {
                
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
            
            int gap = 1;
            while (gap <= Math.ceil(values.length / 3)) {
                gap *= 3 + 1;
            }

            while (gap > 0) {
                
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

package com.brainyvoyage.algos.sort;

/**
 * Shell-sort gains efficiency by making a trade-off between size and partial order in
 * the sub-sequences. At the <em>beginning</em>, the sub-sequences are <em>short</em>;
 * <em>later</em> in the sort, the sub-sequences are <em>partially sorted</em>.
 * In both cases, insertion sort is the method of choice. The extent to which the
 * sub-sequences are partially sorted is a variable factor that depends strongly
 * on the increment sequence
 */
public class ShellSort {
    public static void sort(Comparable[] data) {
        int h = 1;
        while (h < data.length / 3)
            h = 3 * h + 1;
        /* Initially h is large and hence the sub-sequence is small.
         * Selection sort works well when collection is small
         */
        while (h >= 1) {

            /* h-sorted using insertion sort */
            for (int i = h; i < data.length; i++) {
                /* Reducing by h element (j -= h) */
                for (int j = i; j >= h && SortUtils.less(data[j], data[j - h]); j -= h) {
                    SortUtils.swap(data, j, j - h);
                }
            }
            /* End of Insertion Sort */

            /* Every iteration h get smaller and hence the sub-sequence */
            h = h / 3;
        }
    }
}

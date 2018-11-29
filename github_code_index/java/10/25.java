package ru.job4j.arrays;

/**
 * Bubble-sort array.
 *
 * @author Aleksei Sapozhnikov (vermucht@gmail.com)
 * @version $Id$
 * @since 10.01.2018
 */
public class BubbleSort {

    /**
     * Sort given array using bubble-sort.
     *
     * @param array Given array.
     * @return The same array object with elements in sorted order.
     */
    public int[] sort(int[] array) {
        // number of iterations
        for (int i = 0; i < (array.length - 1); i++) {
            // iteration
            for (int j = 0; j < (array.length - 1) - i; j++) {
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
        return array;
    }

}

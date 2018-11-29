package com.jason;

/**
 * Created by jason on 02/24/2017.
 */
public class RadixSort {

    /**
     * <h1><strong>LOOP INVARIANT</strong></h1>
     * <ul>
     * <li>At the beginning of the for loop, the array is sorted on the last position−1 digits.</li>
     * </ul>
     * see more detail, <a href="http://www.geeksforgeeks.org/radix-sort/">just click here</a>.
     * Radix sort use counting sort as a subroutine.
     *
     * @param array
     * @return
     */
    public static int[] radixSort(int[] array) {
        //initialization---
        int maximum = ArrayUtil.getMaximum(array);
        int digitsNumber = NumberUtil.getDigitsNumber(maximum);
        int[] temporaryArray = array;
        //initialization---
        for (int position = 1; position <= digitsNumber; position++) {
            temporaryArray = CountingSort.countingSortByPosition(temporaryArray, position);
        }
        return temporaryArray;
    }

}
/*
 * Copyright (C) 2017  Luis Michaelis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

package de.lmichaelis.sorting.algorithm;

import de.lmichaelis.sorting.common.Comparator;
import de.lmichaelis.sorting.common.Converter;

/**
 * Represents the <code>BubbleSort</code> sorting algorithm
 * The bubble-sort algorithm is a slow, stable sorting algorithm.
 * It works by exchanging adjacent values that are in the wrong
 * order. It best-case time complexity os bubble sort is
 * <code>O(n)</code>, it's average- as well as it's worst-case
 * time complexity is <code>O(n^2)</code>. It has a space complexity
 * of <code>O(1)</code>.
 * <p>
 * <small>Taken from Wikipedia (<a href="https://en.wikipedia.org/w/index.php?title=Bubble_sort">Bubble Sort</a>, <a href="https://en.wikipedia.org/w/index.php?title=Sorting_algorithm">Sorting Algorithm</a>)</small>
 *
 * @author Luis Michaelis (for Sorting 2.0 on 31.12.2017)
 * @see de.lmichaelis.sorting.algorithm.Algorithm
 */
public class BubbleSort extends Algorithm {
    /**
     * Does a reverse bubble-sort {@link #loop(Object[], Comparator, Algorithm, int, int, int, int)} (needed for other algorithms).
     *
     * @param <T>        The type of the array
     * @param array      The array to use
     * @param comparator The comparator to use to compare the values
     * @param algorithm  The algorithm which called this method
     * @param start      The start index for the for loop
     * @param end        The end index for the for loop
     * @param subtract   The value the index is increased by every iteration
     * @param gap        The gap between the two checked values
     * @return <code>true</code> if any values were swapped, <code>false</code> otherwise.
     */
    static <T> boolean loopReverse ( T[] array,
                                     Comparator<T> comparator,
                                     Algorithm algorithm,
                                     int start,
                                     int end,
                                     int subtract,
                                     int gap ) {
        boolean swapped = false;

        for ( int i = start; i >= end; i -= subtract ) {
            if ( i + gap < array.length ) {
                if ( algorithm.compare( array, comparator, i, i + gap ) == Comparator.BIGGER ) {
                    algorithm.swap( array, i, i + gap );
                    swapped = true;
                }
            }
        }

        return swapped;
    }

    /**
     * Sorts an array using the {@link BubbleSort} sorting algorithm.
     * It performs a {@link #loop(Object[], Comparator, Algorithm, int, int, int, int)}
     * operation while a value has been swapped in the last run. After every
     * <code>loop</code> operation it decreases the <code>wall</code> which indicates
     * the <code>end</code> value for the <code>loop</code> operation because the
     * highest found value in that run is now at the end of the array.
     *
     * @param array      The array to sort
     * @param comparator The comparator to use for the sorting.
     * @param converter  The converter to use (not needed, can be <code>null</code> or use {@link #sort(Object[], Comparator)})
     * @param <T>        The type of the array.
     */
    @Override
    public <T> void sort ( T[] array, Comparator<T> comparator, Converter<T> converter ) {
        // The wall is at the end of the array
        int wall = array.length;

        // Determines if there were any swaps in the last run
        boolean swapped = true;

        // Perform a bubble-sort operation whenever at least one item
        // was swapped in the last run.
        while ( swapped ) {

            // Do a bubble-sort operation and decrement the wall because the biggest
            // element found in this iteration is at the end (-> we don't care about
            // already sorted sub-arrays).
            swapped = loop( array, comparator, this, 0, wall--, 1, 1 );
        }
    }

    /**
     * Does a bubble-sort loop (needed for other algorithms).
     * The loop works as follows: For every element in the list
     * from <code>start</code> to <code>end</code> compare the value
     * to the value of the next element. Is the value of this element
     * bigger, swap the two elements and continue.
     *
     * @param <T>        The type of the array
     * @param array      The array to use
     * @param comparator The comparator to use to compare the values
     * @param algorithm  The algorithm which called this method
     * @param start      The start index for the for loop
     * @param end        The end index for the for loop
     * @param add        The value the index is increased by every iteration
     * @param gap        The gap between the two checked values
     * @return <code>true</code> if any values were swapped, <code>false</code> otherwise.
     */
    static <T> boolean loop ( T[] array,
                              Comparator<T> comparator,
                              Algorithm algorithm,
                              int start,
                              int end,
                              int add,
                              int gap ) {
        boolean swapped = false;

        for ( int i = start; i < end; i += add ) {
            if ( i + gap < array.length ) {
                if ( algorithm.compare( array, comparator, i, i + gap ) == Comparator.BIGGER ) {
                    algorithm.swap( array, i, i + gap );
                    swapped = true;
                }
            }
        }

        return swapped;
    }
}

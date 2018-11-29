/*
 * Copyright 2009-2011 Nathan Fiedler. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */
package org.burstsort4j;

/**
 * Binary heap sort implementation based on pseudocode from Wikipedia.
 *
 * @author  Nathan Fiedler
 */
public class Heapsort {

    private Heapsort() {
    }

    /**
     * Sort the input array using the heap sort algorithm.
     * O(n*logn) running time with constant extra space.
     *
     * @param  <T>    type of comparable to be sorted.
     * @param  input  array of comparable objects to be sorted.
     */
    public static <T extends Comparable<? super T>> void sort(T[] input) {
        if (input == null || input.length < 2) {
            return;
        }

        // start is assigned the index in a of the last parent node
        for (int start = (input.length - 2) / 2; start >= 0; start--) {
            // sift down the node at index start to the proper place such
            // that all nodes below the start index are in heap order
            int root = start;
            // While the root has at least one child
            while (root * 2 + 1 < input.length) {
                // root*2+1 points to the left child
                int child = root * 2 + 1;
                // If the child has a sibling and the child's value
                // is less than its sibling's...
                if ((child + 1 < input.length) &&
                        input[child].compareTo(input[child + 1]) < 0) {
                    // ... then point to the right child instead
                    child++;
                }
                // out of max-heap order
                if (input[root].compareTo(input[child]) < 0) {
                    T temp = input[root];
                    input[root] = input[child];
                    input[child] = temp;
                    // repeat to continue sifting down the child now
                    root = child;
                } else {
                    break;
                }
            }
        }
        // after sifting down the root all nodes/elements are in heap order

        for (int end = input.length - 1; end > 0; end--) {
            // swap the root (maximum value) of the heap with the last
            // element of the heap
            T temp = input[end];
            input[end] = input[0];
            input[0] = temp;
            // put the heap back in max-heap order
            int root = 0;
            // While the root has at least one child
            while (root * 2 + 1 < end) {
                // root*2+1 points to the left child
                int child = root * 2 + 1;
                // If the child has a sibling and the child's value is
                // less than its sibling's...
                if ((child + 1 < end) &&
                        input[child].compareTo(input[child + 1]) < 0) {
                    // ... then point to the right child instead
                    child++;
                }
                // out of max-heap order
                if (input[root].compareTo(input[child]) < 0) {
                    temp = input[root];
                    input[root] = input[child];
                    input[child] = temp;
                    // repeat to continue sifting down the child now
                    root = child;
                } else {
                    break;
                }
            }
            // end of for loop decreases the size of the heap by one so that
            // the previous max value will stay in its proper placement
        }
    }
}

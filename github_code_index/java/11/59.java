package sortingAlgorithms.algorithms.linear;

import sortingAlgorithms.algorithms.SortingAlgorithm;

import java.util.ArrayList;
import java.util.List;

/**
 * Radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by
 * grouping keys by the individual digits which share the same significant position and value. A
 * positional notation is required, but because integers can represent strings of characters (e.g.,
 * names or dates) and specially formatted floating point numbers, radix sort is not limited to
 * integers. [http://en.wikipedia.org/wiki/Radix_sort]
 */
public class RadixSort implements SortingAlgorithm {

    /**
     * @param list - contain array with unsorted integer values.
     * @throws IllegalArgumentException
     * @return List<Integer>
     */
    @Override
    @SuppressWarnings("unchecked")
    public List<Integer> sort(List<Integer> list) {

        // checking input parameter for null
        if (list == null) {
            throw new IllegalArgumentException("ArrayList not specified!");
        }

        // To get a digit we can first divide number with 10^i and then get the remainder
        // after dividing by 10, where i = 0 to 2*Number of digits in N;
        int exp = 1;

        // the number of digits in N^2 can be maximum double of the digits in N
        int maxDigits = 2;

        for (int i = 0; i < maxDigits; i++) {

            // initiating multidimensional list of lists of size 10
            List[] bucketList = new ArrayList[10];
            for (int k = 0; k < 10; k++) {
                bucketList[k] = new ArrayList<Integer>();
            }
            for (Integer aList : list) {
                int number = (aList / exp) % 10;
                bucketList[number].add(aList); // producing warning: unchecked assignment - suppressed.
            }
            exp *= 10;
            int index = 0;
            for (int k = 0; k < 10; k++) {
                for (Object num : bucketList[k]) {
                    list.set(index, (Integer) num);
                    index++;
                }
            }
        }
        return list;
    }
}

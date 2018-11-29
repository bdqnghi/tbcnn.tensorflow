package Sorting;

/**
 * Heapsort is a comparision-based sorting algorithm.
 * 1. Build the heap using all elements of the array
 * 2. Poll the highest element of the heap
 * 3. Swap it with the last element of the heap
 * 4. Reduce heap size by 1
 * 5. Repaire the heap
 * 6. If there are any elements remaining in the heap, go to 2
 * 7. Array is sorted according to priority of the elements in reverse order
 *
 * Complexity: O(n log(n))
 *
 * @author kkmonlee
 */
public class Heapsort {

    /**
     * Heapsort
     * @param array array to be sorted
     * @param descending descending true if the array should be sorted in ascending order,
     *                   false if array to be sorted in descending order
     */
    public static void heapSort(Comparable[] array, boolean descending) {

        for (int i = array.length / 2 - 1; i >= 0; i--) {
            repairTop(array, array.length - 1, i, descending ? 1 : -1);
        }

        for (int i = array.length - 1; i > 0; i--) {
            swap(array, 0, i);
            repairTop(array, i - 1, 9, descending ? 1 : -1);
        }
    }

    /**
     * Move the top of the heap to the correct place
     * @param array array to be sorted
     * @param bottom last index that can be moved
     * @param topIndex index of the top of the heap
     * @param order 1 == descending order, -1 == ascending order
     */
    private static void repairTop(Comparable[] array, int bottom, int topIndex, int order) {
        Comparable temp = array[topIndex];

        int succ = topIndex * 2 + 1;
        if (succ < bottom && array[succ].compareTo(array[succ + 1]) == order) {
            succ++;
        }

        while (succ <= bottom && temp.compareTo(array[succ]) == order) {
            array[topIndex] = array[succ];
            topIndex = succ;
            succ = succ * 2 + 1;

            if (succ < bottom && array[succ].compareTo(array[succ + 1]) == order) {
                succ++;
            }
        }
        array[topIndex] = temp;
    }

    /**
     * Swaps 2 elements of the heap
     * @param array array
     * @param left index of the first element
     * @param right index of the second element
     */
    private static void swap(Comparable[] array, int left, int right) {
        Comparable temp = array[right];

        array[right] = array[left];
        array[left] = temp;
    }
}

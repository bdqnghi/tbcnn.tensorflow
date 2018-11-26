package clrs.sort;

import java.util.Arrays;

import clrs.heap.MaxHeap;

/**
 * Implements the <strong><i>Heap Sort</i></strong> algorithm.
 * 
 * @author ani
 *
 */
public class HeapSort {

    /**
     * The MaxHeap object.
     */
    private MaxHeap maxHeap;

    /**
     * Tags a {@code MaxHeap} object to the HeapSort type.
     * 
     * @param maxHeap
     *            The {@code MaxHeap} object
     */
    public HeapSort(MaxHeap maxHeap) {
        this.maxHeap = maxHeap;
    }

    /**
     * Sorts the given {@code array} in the ascending order using the
     * <i><strong>heap sort</strong></i> technique.
     * 
     * <p>
     * The algorithm follows these steps:
     * 
     * <ol>
     * <li>Build a 'Max heap' using {@link clrs.heap.MaxHeap#buildMaxHeap(int[])}
     * </li>
     * <li>Run a loop from the last element of the array to the first</li>
     * <li>Swap the first element in the heap with the current element of the
     * array</li>
     * <li>Call {@link clrs.heap.MaxHeap#maxHeapify(int[], int, int)} for every
     * element of the array, decreasing {@code heapSize} at every iteration.</br>
     * Decreasing {@code heapSize} will ignore the already sorted elements of the
     * array</li>
     * <li>Follow Step - 2 through Step - 4 till the end of the loop
     * </ol>
     * </p>
     * <p>
     * Note: Sorting operation is performed on the passed array itself.
     * </p>
     * 
     * @param array
     *            Input array that needs to be sorted.</br>
     */
    public void heapSort(int[] array) {
        maxHeap.buildMaxHeap(array);

        for (int i = array.length - 1; i > 0; i--) {
            int temp = array[0];
            array[0] = array[i];
            array[i] = temp;
            maxHeap.setHeapSize(maxHeap.getHeapSize() - 1);
            maxHeap.maxHeapify(array, 0, maxHeap.getHeapSize());
        }
    }

    public static void main(String[] args) {
        int[] array = new int[] { 1, 16, 10, 8, 14, 9, 3, 2, 4, 7 };
        int[] array1 = new int[] { 17, 27, 3, 16, 10, 13, 1, 5, 0, 12, 4, 8, 9, 7 };

        HeapSort heapSort = new HeapSort(new MaxHeap());
        heapSort.heapSort(array);
        heapSort.heapSort(array1);
        System.out.println(Arrays.toString(array));
        System.out.println(Arrays.toString(array1));
    }
}

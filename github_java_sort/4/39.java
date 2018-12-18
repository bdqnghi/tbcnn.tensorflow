package clrs.sort;

import java.util.Arrays;

import clrs.heap.MaxHeap;


public class HeapSort {

    
    private MaxHeap maxHeap;

    
    public HeapSort(MaxHeap maxHeap) {
        this.maxHeap = maxHeap;
    }

    
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

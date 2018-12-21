package com.company;

import java.util.Random;

public class Main {

    public static void main(String[] args) {


























        copmpareSorts();
    }

    static void copmpareSorts() {
        int size = 10_000_000;
        BaseSort selectionSort = new SelectionSort(size);
        BaseSort bubbleSort = new BubbleSort(size);
        BaseSort insertionSort = new InsertionSort(size);
        BaseSort mergeSort = new MergeSort(size);
        BaseSort bookMergeSort = new BookMergeSort(size);
        BaseSort quickSort = new QuickSort(size);

        HeapSort heapSort = new HeapSort(size);
        HeapSort heapSort2 = new HeapSort(size);
        for (int i = 0; i < size; i++) {
            int random = new Random().nextInt(1_000_000) + 1;
            bubbleSort.insert(random);
            selectionSort.insert(random);
            insertionSort.insert(random);
            mergeSort.insert(random);
            bookMergeSort.insert(random);
            quickSort.insert(random);
            heapSort.insert(random);
            heapSort2.insertToArray(random);
        }




        testBaseSort(mergeSort, "Merge");
        testBaseSort(bookMergeSort, "bookMerge");
        testBaseSort(quickSort, "QuickSort");
        testHeapSort(heapSort, "HeapSort", size);
        testHeapSort(heapSort2, "HeapSort2", size);
    }

    static void testBaseSort(BaseSort sort, String name) {
        long before = System.currentTimeMillis();
        long counterBubble = sort.sort();
        long after = System.currentTimeMillis();
        System.out.println("\n" + name + " counter =\t" + counterBubble + "\t time = " + (after - before));
    }

    static void testHeapSort(HeapSort heapSort, String name, int size) {
        int[] result = new int[size];
        long before = System.currentTimeMillis();
        heapSort.sort();
        for (int i = 0; i < size; i++) {
            result[i] = heapSort.removeHead();
        }
        long after = System.currentTimeMillis();
        System.out.println("\n" + name + " counter =\t" + 0 + "\t time = " + (after - before));
    }

    static void testSelection() {
        BaseSort sort = new SelectionSort(15);
        for (int i = 0; i < 15; i++) {
            int random = new Random().nextInt(100) + 1;
            sort.insert(random);
        }

        sort.print();
        long count = sort.sort();
        sort.print();
    }

    static void testBubble() {
        BubbleSort bubbleSort = new BubbleSort(15);
        for (int i = 0; i < 15; i++) {
            int random = new Random().nextInt(100) + 1;
            bubbleSort.insert(random);
        }

        bubbleSort.print();
        long count = bubbleSort.sort();
        bubbleSort.print();
    }

}

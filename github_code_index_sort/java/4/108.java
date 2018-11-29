package org.ventry.commons.algorithm;

import org.ventry.commons.utils.ArrayUtils;
import org.ventry.commons.utils.Console;

import java.util.Arrays;

public class App {

    public static void main(String[] args) {
        int arraySize = 10000000;
        int[] arrays = ArrayUtils.randomIntArrays(arraySize);
        // Console.write(20, arrays);

        int iterator = 1;
        long start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            // InsertionSort.order(Arrays.copyOf(arrays, arraySize));
        }
        Console.writeLine("insertion sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        // array.size in [500, *), merge-sort faster than insertion-sort
        start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            MergeSort.order(Arrays.copyOf(arrays, arraySize), 0, arraySize);
        }
        Console.writeLine("merge sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        // array.size in (0, 500) heap-sort's performance approaches to insertion-sort
        // array.size in [500, 10000) heap-sort's performance is far better than two former
        // array.size in [10000, *) heap-sort's performance is worse than merge-sort
        start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            HeapSort.order(Arrays.copyOf(arrays, arraySize));
        }
        Console.writeLine("heap sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        // array.size in [300, *) quick sort's performance approaches to insertion-sort, worse than heap sort
        start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            QuickSort.tailRecursiveOrder(Arrays.copyOf(arrays, arraySize), 0, arraySize - 1);
        }
        Console.writeLine("quick sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            CountingSort.order(Arrays.copyOf(arrays, arraySize), arraySize);
        }
        Console.writeLine("counting sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        // The fastest and the most restrictive, such as discarding satellite data
        BitmapSort bitmapSort = new BitmapSort(4);
        start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            bitmapSort.order(Arrays.copyOf(arrays, arraySize), arraySize + 1);
        }
        Console.writeLine("bitmap sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        Console.writeLine(OrderStatistics.select(arrays, 0, arraySize - 1, 4));
    }
}

package org.ventry.commons.algorithm;

import org.ventry.commons.utils.ArrayUtils;
import org.ventry.commons.utils.Console;

import java.util.Arrays;

public class App {

    public static void main(String[] args) {
        int arraySize = 10000000;
        int[] arrays = ArrayUtils.randomIntArrays(arraySize);
        

        int iterator = 1;
        long start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            
        }
        Console.writeLine("insertion sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        
        start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            MergeSort.order(Arrays.copyOf(arrays, arraySize), 0, arraySize);
        }
        Console.writeLine("merge sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        
        
        
        start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            HeapSort.order(Arrays.copyOf(arrays, arraySize));
        }
        Console.writeLine("heap sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        
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

        
        BitmapSort bitmapSort = new BitmapSort(4);
        start = System.nanoTime();
        for (int i = 0; i < iterator; i++) {
            bitmapSort.order(Arrays.copyOf(arrays, arraySize), arraySize + 1);
        }
        Console.writeLine("bitmap sort cost:" + (System.nanoTime() - start) / 1000000 + "ms");

        Console.writeLine(OrderStatistics.select(arrays, 0, arraySize - 1, 4));
    }
}

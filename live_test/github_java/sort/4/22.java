package com.zhangwen.learn.zhangwenit.algorithm.heap.map_heap;

import com.zhangwen.learn.zhangwenit.algorithm.util.SortTestHelper;

import java.util.Arrays;


public class HeapSort {

    public static void sort(Comparable[] arr) {
        int n = arr.length;
        
        
        
        
        for (int i = (n - 1 - 1) / 2; i >= 0; i--) {
            
            shiftDown(arr, n, i);
        }
        
        for (int j = n - 1; j > 0; j--) {
            SortTestHelper.swap(arr, 0, j);
            shiftDown(arr, j, 0);
        }
    }

    
    private static void shiftDown(Comparable[] arr, int n, int i) {
        
        while (i * 2 + 1 < n) {
            
            int j = i * 2 + 1;
            
            if (j + 1 < n && arr[j + 1].compareTo(arr[j]) > 0) {
                j += 1;
            }
            
            if (arr[i].compareTo(arr[j]) >= 0) {
                break;
            }
            SortTestHelper.swap(arr, i, j);
            i = j;
        }
    }

    public static void main(String[] args) {
        System.out.println("普通数组排序结果：");
        int n = 1000000;
        Integer[] arr1 = SortTestHelper.generateRandomArray(n, 0, 1000000);
        Integer[] arr2 = Arrays.copyOf(arr1, arr1.length);
        Integer[] arr3 = Arrays.copyOf(arr1, arr1.length);
        Integer[] arr4 = Arrays.copyOf(arr1, arr1.length);
        Integer[] arr5 = Arrays.copyOf(arr1, arr1.length);
        Integer[] arr6 = Arrays.copyOf(arr1, arr1.length);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.merge_sort.MergeSort", arr1);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.quick_sort.QuickSort2Ways", arr2);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.quick_sort.QuickSort3Ways", arr3);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort1", arr4);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort2", arr5);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort", arr6);

        System.out.println("近乎有序数组排序结果：");
        arr1 = SortTestHelper.generateNearlyOrderedArray(n, 10);
        arr2 = Arrays.copyOf(arr1, arr1.length);
        arr3 = Arrays.copyOf(arr1, arr1.length);
        arr4 = Arrays.copyOf(arr1, arr1.length);
        arr5 = Arrays.copyOf(arr1, arr1.length);
        arr6 = Arrays.copyOf(arr1, arr1.length);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.merge_sort.MergeSort", arr1);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.quick_sort.QuickSort2Ways", arr2);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.quick_sort.QuickSort3Ways", arr3);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort1", arr4);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort2", arr5);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort", arr6);

        System.out.println("大量重复数组排序结果：");
        arr1 = SortTestHelper.generateRandomArray(n, 0, 100);
        arr2 = Arrays.copyOf(arr1, arr1.length);
        arr3 = Arrays.copyOf(arr1, arr1.length);
        arr4 = Arrays.copyOf(arr1, arr1.length);
        arr5 = Arrays.copyOf(arr1, arr1.length);
        arr6 = Arrays.copyOf(arr1, arr1.length);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.merge_sort.MergeSort", arr1);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.quick_sort.QuickSort2Ways", arr2);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "sorting_advance.quick_sort.QuickSort3Ways", arr3);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort1", arr4);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort2", arr5);
        SortTestHelper.testSort("com.zhangwen.learn.zhangwenit.algorithm." +
                "heap.map_heap.HeapSort", arr6);
    }
}

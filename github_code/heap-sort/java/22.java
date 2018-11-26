package com.zhangwen.learn.zhangwenit.algorithm.heap.map_heap;

import com.zhangwen.learn.zhangwenit.algorithm.util.SortTestHelper;

import java.util.Arrays;

/**
 * 原地堆排序（无需额外开辟空间）
 *
 * @author zhangwen at 2018-06-24 13:46
 **/
public class HeapSort {

    public static void sort(Comparable[] arr) {
        int n = arr.length;
        // 注意，此时我们的堆是从0开始索引的
        // 从(最后一个元素的索引-1)/2开始!!!!!!
        // 最后一个元素的索引 = n-1
        //将arr构造为堆结构，heapify操作
        for (int i = (n - 1 - 1) / 2; i >= 0; i--) {
            //将每一个非叶子节点进行shiftDown操作
            shiftDown(arr, n, i);
        }
        //arr[0]即为最大元素，将arr[0]和arr[n]交换，再将arr[0...n-1]构造为堆，循环下去
        for (int j = n - 1; j > 0; j--) {
            SortTestHelper.swap(arr, 0, j);
            shiftDown(arr, j, 0);
        }
    }

    /**
     * shiftDown
     *
     * @param arr 数组
     * @param n   数组长度
     * @param i   进行shiftDown的元素下标
     */
    private static void shiftDown(Comparable[] arr, int n, int i) {
        //如果有子节点
        while (i * 2 + 1 < n) {
            //子节点中最大的元素
            int j = i * 2 + 1;
            //如果有右子节点，且大于左子节点
            if (j + 1 < n && arr[j + 1].compareTo(arr[j]) > 0) {
                j += 1;
            }
            //如果比子节点小，交换父子节点，否则，跳出循环
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

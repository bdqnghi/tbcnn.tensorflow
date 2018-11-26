package com.haogrgr.test.topn;

public class HeapSort {

    public static void main(String[] args) {
        int a[] = new int[] { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
        buildHeap(a);
        System.out.println("构建好的最大堆是:");
        for (int x : a)
            System.out.print(x + " ");
        System.out.println();
        System.out.println("排序的结果是:");
        heapMain(a);
        for (int x : a)
            System.out.print(x + " ");
    }

    public static void buildHeap(int a[]) {
        int n = a.length;
        for (int i = n / 2 - 1; i >= 0; i--) {//i从第一个非叶子结点开始  
            maxHeapify(a, i, a.length);
        }
    }

    public static void maxHeapify(int a[], int i, int heapSize) {
        int maxIndex = i;
        if (2 * i + 1 <= heapSize - 1 && a[2 * i + 1] > a[i])
            maxIndex = 2 * i + 1;
        if (2 * i + 2 <= heapSize - 1 && a[i * 2 + 2] > a[maxIndex])
            maxIndex = 2 * i + 2;
        if (maxIndex != i) {
            int tmp = a[maxIndex];
            a[maxIndex] = a[i];
            a[i] = tmp;
            maxHeapify(a, maxIndex, heapSize);
        }
    }

    public static void heapMain(int a[]) {
        int heapSize = a.length;
        for (int i = a.length - 1; i > 0; i--) {
            int tmp = a[0];
            a[0] = a[i];
            a[i] = tmp;
            heapSize -= 1;
            maxHeapify(a, 0, heapSize); //在heapSize范围内根结点的左右子树都已经是最大堆  
        }
    }

}

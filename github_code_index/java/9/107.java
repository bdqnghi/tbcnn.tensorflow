package edu.learn.java.ds.sort;

import java.util.Arrays;

public class Heapsort {

    private int total;
    int[] arr = { 23, 17, 14, 6, 27, 13, 10, 1, 5, 7, 12 };

    private void swap(int i, int j) {
        int temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }

    private void heapify(int i) {

        // i - index of the parent element
        // left - index of the left child
        // right - index of the right child.

        int left=getLeftIndex(i);
        int right=getRightIndex(i);
        int max=i;

        if(left<=total && arr[left]<arr[i]) {
            max=left;
        }
        if(right<=total && arr[right]<arr[max]) {
            max=right;
        }

        if(max!=i) {
            swap(i,max);
            heapify(max);
        }
    }

    public void sort() {
        total=arr.length-1;
        System.out.println(java.util.Arrays.toString(arr));
        for (int i = total / 2; i >= 0; i--) {
            heapify(i);
        }

        for (int i = total; i > 0; i--) {
            swap(0, i);
            total--;
            heapify(0);
        }
        total=arr.length-1;
        System.out.println(java.util.Arrays.toString(arr));
    }

    public int getParentIndex(int index) {
        return index/2;
    }

    public int getLeftIndex(int index) {
        return 2 * index;
    }

    public int getRightIndex(int index) {
        return (2 * index) + 1;
    }

    public int getMaxElementInHeap() {
        return arr[0];
    }

    public int extractMaxElementInHeap() {
        int max=getMaxElementInHeap();
        printArray();
        //arr[0]=arr[total];
        //heapify(arr,0);
        arr = Arrays.copyOfRange(arr, 1, arr.length);
        printArray();
        return max;
    }

    public void heapIncreaseKey(int i, int key) {
        if(i<0 || i>arr.length) {
            System.out.println("Sorry : Invalid Index ");
        }
        arr[i]=key;
        //If the newly inserted element is greater than its parent, swap them and continue till root.
        while( (i>0) && ( arr[i] > arr[getParentIndex(i)] )) {
            swap(i,getParentIndex(i));
            i = getParentIndex(i);
        }
    }

    public void printArray() {
        System.out.println(java.util.Arrays.toString(arr));
    }

    public static void main(final String[] args)
    {
        //Heapsort hs=new Heapsort();
        //hs.sort();
        //System.out.println("Max Element of Heap : "+hs.getMaxElementInHeap());
        //System.out.println("Extract Element of Heap : "+hs.extractMaxElementInHeap());
        //System.out.println("Extract Element of Heap : "+hs.extractMaxElementInHeap());
        //System.out.println("Extract Element of Heap : "+hs.extractMaxElementInHeap());
        //hs.heapIncreaseKey(2, 40);
        //hs.printArray();
    }
}

































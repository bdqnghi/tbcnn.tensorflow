package com.jbwang.recursive;

/**
 * Created by jbwang0106 on 2017/5/15.
 */
public class MergeSort {

    public long [] theArray;
    public int nElems;

    public MergeSort(int maxSize) {
        theArray = new long[maxSize];
        nElems = 0;
    }

    public void insert(long value) {
        theArray[nElems++] = value;
    }

    public void display() {

        for (int i = 0; i < nElems; i++) {
            System.out.print(theArray[i] + " ");
        }
        System.out.println();

    }

    public void mergeSort() {
        long [] workArray = new long[nElems];
        reMergeSort(workArray,0,nElems-1);
    }

    private void reMergeSort(long[] workArray, int lowerBound, int upperBound) {
        if (lowerBound == upperBound)
            return;
        else {
            int mid = (lowerBound + upperBound)/2;
            reMergeSort(workArray, lowerBound, mid);
            reMergeSort(workArray, mid+1, upperBound);
            merge(workArray, lowerBound, mid+1, upperBound);
        }
    }

    private void merge(long[] workArray, int lowerBound, int highPatr, int upperBound) {

        int j = 0;
        int mid = highPatr-1;
        int low = lowerBound;
        int n = upperBound - lowerBound + 1;

        while (lowerBound <= mid && highPatr <= upperBound) {
            if (theArray[lowerBound] < theArray[highPatr])
                workArray[j++] = theArray[lowerBound++];
            else
                workArray[j++] = theArray[highPatr++];
        }

        while (lowerBound <= mid)
            workArray[j++] = theArray[lowerBound++];

        while (highPatr <= upperBound)
            workArray[j++] = theArray[highPatr++];

        for (j = 0; j < n; j++) {
            theArray[low+j] = workArray[j];
        }

    }

    public static void main(String [] args) {
        MergeSort mergeSort = new MergeSort(100);

        mergeSort.insert(27);
        mergeSort.insert(76);
        mergeSort.insert(45);
        mergeSort.insert(86);
        mergeSort.insert(34);
        mergeSort.insert(17);
        mergeSort.insert(87);
        mergeSort.insert(65);
        mergeSort.insert(59);
        mergeSort.insert(97);

        mergeSort.mergeSort();
        mergeSort.display();

    }
}

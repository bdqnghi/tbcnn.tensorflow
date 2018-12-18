package com.sort;

import java.util.Random;

import com.array.ArrayHelper;


public class MergeSort {
	
	private static final boolean DEBUG = true;

    private int[] temp;
    
    public void sort(int[] arr) {
    	temp = new int[arr.length];
        doSort(arr,0,arr.length-1);
    }
    
    private void doSort(int[] arr, int low, int high) {
    	printLine("Sorting low = " + low + "; high = " + high);
        
        if (high <= low) return;
        
        int mid = low + (high - low) / 2;
        doSort(arr,low,mid);
        doSort(arr,mid+1, high);
        mergeArrays(arr, low, mid, high);
    }
    
    public void mergeArrays(int[] arr, int low, int mid, int high) {
        
    	printLine("\nReceived low = " + low + "; mid = " + mid + "; high = " + high);
        
        for (int i = low; i <= high; i++) {
            temp[i] = arr[i];
        }
        
        int i = low;
        int j = mid + 1;
        int k = low;
        
        while (i <= mid && j <= high) {
        	
        	if (temp[j] < temp[i]) {
        		arr[k++] = temp[j++]; 
        	} else {
        		arr[k++] = temp[i++]; 
        	}
        }
       
        if (i > mid) {
        	
        	while (j <= high) {
        		arr[k++] = temp[j++];
        	}
        }
        
        if (j > high) {
        	
        	while (i <= mid) {
        		arr[k++] = temp[i++];
        	}
        }
        if (DEBUG) {
        	System.out.print("Merged Array...   ");
        	ArrayHelper.printArray(arr);
        }
    }

    public static void main(String[] args) {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        test7();
        test8();
    }
    
    private static void test1() {
        MergeSort ms = new MergeSort();
        int[] arr = {10,12, 5,7,8};
        ms.sort(arr);
        assert ArrayHelper.isSorted(arr);
    }
    
    private static void test2() {
        MergeSort ms = new MergeSort();
        int[] arr = {1,3,2,4};
        ms.sort(arr);
        assert ArrayHelper.isSorted(arr);
    }

    private static void test3() {
        MergeSort ms = new MergeSort();
        int[] arr = {1,3,5,7,10,12};
        ms.sort(arr);
        assert ArrayHelper.isSorted(arr);
    }

    private static void test4() {
        MergeSort ms = new MergeSort();
        int[] arr = {1,3,2,10,20,30,40,50,60,23,24,35,45,90,11,12};
        ms.sort(arr);
        assert ArrayHelper.isSorted(arr);
    }
    
    private static void test5() {
        int[] arr = {1,13,34,71,8,0,12,-1,100,-12,99};
        MergeSort ms = new MergeSort();
        ms.sort(arr);
        assert ArrayHelper.isSorted(arr);
    }
    
    private static void test6() {
        int[] arr = new int[1000];
        
        Random rand = new Random();
        
        for (int i = 0; i < 1000; i++) {
        	arr[i]  = rand.nextInt();
        }
        MergeSort ms = new MergeSort();
        ms.sort(arr);
        assert ArrayHelper.isSorted(arr);
    }

    private static void test7() {
    	int numCount = 1000000;
        int[] arr = new int[numCount];
        
        Random rand = new Random();
        
        for (int i = 0; i < 100; i++) {
        	arr[i]  = rand.nextInt();
        }
        MergeSort ms = new MergeSort();
        ms.sort(arr);
        assert ArrayHelper.isSorted(arr);
    }
    
    private static void test8() {
        int[] arr = {64, 12, 17, 28, 29, 20, 68, 21, 18, 84, 61, 34};
        MergeSort ms = new MergeSort();
        ms.sort(arr);
        assert ArrayHelper.isSorted(arr);
    }

    private static void printLine(String s) {
		if (DEBUG) {
			System.out.println(s);
		}
	}

}

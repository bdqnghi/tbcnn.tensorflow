package com.algorithm.sort;

/**
 * Insertion Sort
 *
 * Strategy: Iterate through the list by consuming one element at each repetition and growing a sorted output list.
 *
 * Execution Staps:
 * 1. Remove one element from input data
 * 2. Find location in sorted list
 * 3. Insert in that location
 * 4. Repeat until no more elments remain
 *
 * http://www.java2novice.com/java-sorting-algorithms/insertion-sort/
 * https://www.geeksforgeeks.org/insertion-sort/
 */


public class MyInsertionSort {

    public static void main(String a[]){
        int[] arr1 = {10,34,2,56,7,67,88,42};
        int[] arr2 = doInsertionSort(arr1);
        for(int i:arr2){
            System.out.print(i);
            System.out.print(", ");
        }
    }

    public static int[] doInsertionSort(int[] input){

        int temp;
        for (int i = 1; i < input.length; i++) {
            for(int j = i ; j > 0 ; j--){
                if(input[j] < input[j-1]){
                    temp = input[j];
                    input[j] = input[j-1];
                    input[j-1] = temp;
                }
            }
        }
        return input;
    }
}

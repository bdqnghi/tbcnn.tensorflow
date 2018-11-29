package com.haowei.codinginterview;

import java.util.Scanner;

/**
 * Created by hao on 7/24/17.
 * https://www.hackerrank.com/challenges/ctci-bubble-sort
 */
public class SortBubbleSort {
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int numbers[] = new int[N];
        for(int i = 0; i < N; i++){
            numbers[i] = in.nextInt();
        }

        int numberOfSwap = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N-1; j++){
                if(numbers[j] > numbers[j+1]){
                    swap(numbers, j, j+1);
                    numberOfSwap++;
                }
            }
        }

        bubbleSortPrinter(numbers, numberOfSwap);

    }

    static void swap(int[] array, int pos1, int pos2){
        int temp = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = temp;
    }

    static void bubbleSortPrinter(int[] array, int numberOfSwap){
        System.out.println("Array is sorted in " + numberOfSwap + " swaps.");
        System.out.println("First Element: " + array[0]);
        System.out.println("Last Element: " + array[array.length - 1]);
    }
}

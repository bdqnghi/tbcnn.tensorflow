package com.nanyin.shellSort;

import java.util.Arrays;


public class ShellSort {
    public void shellSort(int[] array) {
        int increment, i, j;
        for (increment = array.length / 2; increment > 0; increment /= 2) {

            System.out.println(increment);
            for (i = increment; i < array.length; i++) {
                int temp = array[i];

                for (j = i - increment; j >= 0; j = j - increment) {
                    if (array[j] > temp) {

                        array[j + increment] = array[j];
                    } else {
                        break;
                    }
                }
                
                array[j + increment] = temp;
            }
        }
    }

    public static void main(String[] args) {
        int[] sortArray = new int[]{1, 3, 2, 5, 4, 9, 7, 6, 8};
        ShellSort shellSort = new ShellSort();
        shellSort.shellSort(sortArray);
        System.out.println(Arrays.asList(shellSort).toString());
    }
}

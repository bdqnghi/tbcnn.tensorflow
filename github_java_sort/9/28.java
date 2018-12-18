package com.liyafeng.algorithm.basic.sort;



public class N_Sort_SelectionSort {

    
    public static void main(String[] args) {
        int[] array = {1, 124, 54, 34, 34, 6, 5};
        sort(array);
        Util.print(array);
    }

    private static void sort(int[] array) {
        int length = array.length;

        for (int i = 0; i < length; i++) {
            int min = i;
            for (int j = i + 1; j < length; j++) {
                if (array[j] < array[min]) {
                    min = j;
                }
            }

            Util.exchange(array, i, min);
        }
    }


}

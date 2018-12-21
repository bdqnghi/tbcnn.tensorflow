package Quicksort;

import sun.plugin.javascript.navig.Array;


public class Quicksort {

    private int array[];

    private void sort(int[] inputArr) {

        if (inputArr == null || inputArr.length == 0) {
            return;
        }
        this.array = inputArr;
        int length = inputArr.length;
        quickSort(0, length - 1);
    }

    private void quickSort(int lowerIndex, int higherIndex) {

        int i = lowerIndex;
        int j = higherIndex;
        
        int pivot = array[lowerIndex + (higherIndex - lowerIndex) / 2];
        
        while (i <= j) {






            while (array[i] < pivot) {
                i++;
            }
            while (array[j] > pivot) {
                j--;
            }
            if (i <= j) {
                exchangeNumbers(i, j);
                
                i++;
                j--;
            }
        }
        
        if (lowerIndex < j)
            quickSort(lowerIndex, j);
        if (i < higherIndex)
            quickSort(i, higherIndex);
    }

    private void exchangeNumbers(int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static void main(String arg[]) {

        Quicksort sorter = new Quicksort();
        int[] input = { 24, 2, 45, -20, 56, 75, 7, -56, 99, 53, 12 };
        sorter.sort(input);

        for(int i : input) {
            System.out.print(i);
            System.out.print(" ");
        }

    }

}

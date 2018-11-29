package javapvt.lesson3;

import java.util.*;

public class Main {
    public static void main(String[] args) {

        int[] a = fulfillArray(10);       // getting a new array from user;
        printfArray(a);                      // print the initial array formatted;
        printfArray(bubbleSort(a));          // bubble-sort the array and print it formatted;
        even(a);                             // print even numbers of the array a;
        Arrays.sort(a);                      // sorting using Java method
        printfArray(a);
        int[] b = fulfillArray(5);        // just a new unsorted array
        printfArray(selectionSort(b));       // print selection-sorted array
    }


    // Fulfill the array from the keyboard
    //int n = number of elements in array;
    public static int[] fulfillArray (int n){
        Scanner scan = new Scanner(System.in);
        int[] array = new int[n];

        for (int i = 0; i < n; i++){
            System.out.print("Введите " + i + " элемента массива: ");
            array[i] = scan.nextInt();
        }
        return array;
    }

    // print formatted array (with "|")
    public static void printfArray (int[] array){
        for (int i = 0; i < array.length; i++){
            System.out.print(array[i] + " | ");
        }
        System.out.println("\n");
    }

    //bubble-sort
    public static int[] bubbleSort (int[] array) {
        for (int i = array.length - 1; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
        return array;
    }

    //selectionSort
    public static int[] selectionSort (int[] array){

        for(int i = 0; i < array.length - 1; i++){
            int min = array[i];
            int minIndex = i;

            // looking for the element less then assumed minimum
            for (int j = i + 1; j < array.length; j++){
                if (array[j] < min){
                    min = array[j];
                    minIndex = j;
                }
            }
            // if assumed min is not the smallest, swap
            if (i != minIndex){
                int temp = array[i];
                array[i] = array[minIndex];
                array[minIndex] = temp;
            }
        }
        return array;
    }


    //looking for even numbers in array;
    public static void even (int[] array){
        for (int i = 0; i < array.length; i++){
            if (array[i] % 2 == 0)
                System.out.print(array[i] + " | ");
        }
        System.out.println("\n");
    }

}

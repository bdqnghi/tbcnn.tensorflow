package javapvt.lesson3;

import java.util.*;

public class Main {
    public static void main(String[] args) {

        int[] a = fulfillArray(10);       
        printfArray(a);                      
        printfArray(bubbleSort(a));          
        even(a);                             
        Arrays.sort(a);                      
        printfArray(a);
        int[] b = fulfillArray(5);        
        printfArray(selectionSort(b));       
    }


    
    
    public static int[] fulfillArray (int n){
        Scanner scan = new Scanner(System.in);
        int[] array = new int[n];

        for (int i = 0; i < n; i++){
            System.out.print("Введите " + i + " элемента массива: ");
            array[i] = scan.nextInt();
        }
        return array;
    }

    
    public static void printfArray (int[] array){
        for (int i = 0; i < array.length; i++){
            System.out.print(array[i] + " | ");
        }
        System.out.println("\n");
    }

    
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

    
    public static int[] selectionSort (int[] array){

        for(int i = 0; i < array.length - 1; i++){
            int min = array[i];
            int minIndex = i;

            
            for (int j = i + 1; j < array.length; j++){
                if (array[j] < min){
                    min = array[j];
                    minIndex = j;
                }
            }
            
            if (i != minIndex){
                int temp = array[i];
                array[i] = array[minIndex];
                array[minIndex] = temp;
            }
        }
        return array;
    }


    
    public static void even (int[] array){
        for (int i = 0; i < array.length; i++){
            if (array[i] % 2 == 0)
                System.out.print(array[i] + " | ");
        }
        System.out.println("\n");
    }

}

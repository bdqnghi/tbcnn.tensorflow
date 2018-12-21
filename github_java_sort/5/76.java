package pers.vin.base.dataStructure;

import java.util.Arrays;


public class Sort_BubbleSort {

    static void bubbleSort(int[] arr) {

        
        

        
        
        
        
        
        


        
        int temp;
        
        for (int j = 0; j < arr.length-1; j++) {
            
            
            for (int i = 0; i < arr.length - 1 -j; i++) {
                if (arr[i] > arr[i + 1]) {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        }












    }

    public static void main(String[] args) {
        int[] arr = new int[]{2, 1, 3, 1,4,5,8,6,10,9};

        bubbleSort(arr);
        System.out.println(Arrays.toString(arr));

    }
}

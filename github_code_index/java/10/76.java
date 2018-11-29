package pers.vin.base.dataStructure;

import java.util.Arrays;

/**
 * Created by vin on 05/02/2018.
 */
public class Sort_BubbleSort {

    static void bubbleSort(int[] arr) {

        // thought and principle
        // like bubble in water that will float in top(head)

        // steps
        // 1. compare two value which is close if the first is bigger then swap them
        // 2. two by two until the end and the last value will be the largest
        //    (the light float and the heave down)
        // 3. repeat 1,2 . except for the last one (the largest)
        // 4. repeat 1,2,3


        //code
        int temp;
        // arr.length-1 (step 3)
        for (int j = 0; j < arr.length-1; j++) {
            // after every loop  those elements which needed to be sorted  will reduce one
            // so after every loop the compare elements arr.length - 1 -j (step 3)
            for (int i = 0; i < arr.length - 1 -j; i++) {
                if (arr[i] > arr[i + 1]) {
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        }



//        for (int i = 0; i < arr.length - 1; i++) {
//            for (int j = i + 1; j < arr.length; j++) {
//                if (arr[i] > arr[j]) {
//                    temp = arr[i];
//                    arr[i] = arr[j];
//                    arr[j] = temp;
//                }
//            }
//        }
    }

    public static void main(String[] args) {
        int[] arr = new int[]{2, 1, 3, 1,4,5,8,6,10,9};

        bubbleSort(arr);
        System.out.println(Arrays.toString(arr));

    }
}

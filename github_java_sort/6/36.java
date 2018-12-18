package com.jnu.sortDemo;

import java.util.ArrayList;
import java.util.List;


public class RadixSort {

    public static void radixSort(int[] arr){
        int radix = getRadix(arr);
        sort(arr, radix);
    }

    private static void sort(int[] arr, int radix){
        
        List<List<Integer>> list = new ArrayList<List<Integer>>();
        for(int i = 0; i < 10; i ++){
            List<Integer> item = new ArrayList<>();
            list.add(item);
        }

        
        for(int i = 0; i < radix; i ++){
            
            for(int j = 0; j < arr.length; j ++){
                int index = arr[j] % (int)Math.pow(10, i+1) / (int)Math.pow(10, i);
                list.get(index).add(arr[j]);
            }
            
            int count = 0;
            for(int k = 0; k < 10; k ++){
                if(list.get(k).size() > 0){
                    for(int temp : list.get(k)){
                        arr[count] = temp;
                        count ++;
                    }
                    
                    list.get(k).clear();
                }
            }
        }
    }

    
    private static int getRadix(int[] arr) {
        int max = getMax(arr);
        int time = 0;
        while ( max > 0){
            max /= 10;
            time ++;
        }
        return time;
    }

    private static int getMax(int[] arr){
        int flag = 0;
        for(int i = 0; i < arr.length; i ++){
            flag = i;
            for(int j = i + 1; j < arr.length; j ++){
                if(arr[j] > arr[flag]){
                    flag = j;
                }
            }
            if(flag != i){
                break;
            }
        }
        return arr[flag];
    }

}

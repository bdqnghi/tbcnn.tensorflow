package com.nichao.sorts;

import java.util.Arrays;

/**
 * Created by root on 16-7-29.
 * 功能：希尔排序
 */
public class InsertSort_ShellSort {
    public static void main(String[] args) {
        int[] arr={4,2,9,23,22,5,1};
        int[] delta={4,2,1};

        shellSort(arr,delta);
        System.out.println(Arrays.toString(arr));

    }

    public static void shellSort(int[] arr,int[] deltas){
        for(int delta:deltas){

            for(int i=0;i<arr.length;i+=delta){
                int j=i-delta;
                int tmp=arr[i];
                while(j>=0&& arr[j]>tmp){
                    arr[j+delta]=arr[j];
                    j-=delta;
                }
                arr[j+delta]=tmp;
            }
        }
    }
}

package cn.wkq.algorithm.sort;

import java.util.Arrays;


public class ShellSort {

    
    public static int[] shellSort(int[] arr) {
        int gap = 1, i, j, len = arr.length;
        int temp;
        while (gap < len / 3) {
            
            gap = gap * 3 + 1;
        }
        
        for (; gap > 0; gap /= 3) {
            
            for (i = gap; i < len; i++) {
                temp = arr[i];
                
                for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap) {
                    arr[j + gap] = arr[j];
                }
                arr[j + gap] = temp;
            } 

            print(arr);
        } 

        return arr;
    }

    
    public static int[] shellSort2(int[] arr) {
        int i, j, gap, len = arr.length;
        for (gap = len / 2; gap > 0; gap /= 2) {
            for (i = gap; i < len; i++) {
                for (j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap) {
                    swap(arr, arr[j], arr[j + gap]);
                }
            }
        }
        return arr;
    }

    
    public static int[] shellSort3(int[] arr) {

        int length = arr.length;
        for (int gap = length / 2; gap > 0; gap /= 2) {
            System.out.println("gap:" + gap);

            
            
            
            for (int i = gap; i < length; i++) {
                System.out.println("i:" + i);
                int j = i;

                
                if (j - gap < 0) {
                    System.out.println("比较  第" + j + "个元素 与  第" + (j - gap) + "个元素    数组越界，    跳过");
                    continue;
                }

                System.out.println("比较  第" + j + "个元素 与  第" + (j - gap) + "个元素。");
                while (j - gap >= 0 && arr[j] < arr[j - gap]) {
                    System.out.println("交换  第" + j + "个元素:" + arr[j] + "  与  第" + (j - gap) + "个元素:" + arr[j - gap]);
                    swap(arr, j, j - gap);
                    
                    j -= gap;

                    print(arr);
                }

            }

            System.out.println("----一趟排序完，打印数组----");
            print(arr);
        }

        return arr;
    }



    
    public static int[] shellSort4(int[] arr) {

        int length = arr.length;

        
        for (int gap = length / 2; gap > 0; gap /= 2) {

            
            for (int i = gap; i < length; i++) {
                int j = i;

                
                int temp = arr[j];
                if (arr[j] < arr[j - gap]) {
                    while (j - gap >= 0 && temp < arr[j - gap]) {
                        
                        arr[j] = arr[j - gap];
                        j -= gap;
                    }
                    arr[j] = temp;
                }

            } 

        } 

        return arr;
    }


    
    public static void swap(int[] arr, int a, int b) {
        int tmp = 0;
        tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
    }

    
    public static void swapUseCpu(int[] arr, int a, int b) {
        arr[a] = arr[a] + arr[b];
        arr[b] = arr[a] - arr[b];
        arr[a] = arr[a] - arr[b];
    }

    
    private static void print(int[] arr) {
        System.out.println(Arrays.toString(arr));
    }

    
    public static void main(String[] args) {

        int[] a = null;
        a = new int[]{2, 7, 8, 2, 7, 6, 1, 3, 0};
        
        
        
        
        
        System.out.println("---------------排序前--------------------");
        print(a);

        System.out.println("--------------开始排序--------------------");
        a = shellSort(a);

        System.out.println("---------------排序后---------------------");
        print(a);
    }


}

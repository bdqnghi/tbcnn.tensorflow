package com.jnu.sortDemo;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Damon on 2017/7/27.
 * 基数排序 一种非比较型整数排序算法
 * 原理是将整数按位数切割成不同的数字，然后按每个位数分别比较。
 * 将整数按位数切割成不同的数字，然后按每个位数分别比较。
 *
 * 基数排序的时间复杂度是O(k·n)，其中n是排序元素个数，k是数字位数。
 * 注意这不是说这个时间复杂度一定优于O(n·log(n))，k的大小取决于数字位的选择和待排序数据所属数据类型的全集的大小；
 * k决定了进行多少轮处理，而n是每轮处理的操作数目。
 * 最差空间复杂度是O(k·n)
 *
 * 将所有带比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零，从最低位开始，依次进行依次排序。
 * 如此从最低位一直到最高位排序完后，数列就完成了一个有序序列
 */
public class RadixSort {

    public static void radixSort(int[] arr){
        int radix = getRadix(arr);
        sort(arr, radix);
    }

    private static void sort(int[] arr, int radix){
        //初始化10个链表，用来暂存
        List<List<Integer>> list = new ArrayList<List<Integer>>();
        for(int i = 0; i < 10; i ++){
            List<Integer> item = new ArrayList<>();
            list.add(item);
        }

        //进行radix次分配和收集
        for(int i = 0; i < radix; i ++){
            //分配元素
            for(int j = 0; j < arr.length; j ++){
                int index = arr[j] % (int)Math.pow(10, i+1) / (int)Math.pow(10, i);
                list.get(index).add(arr[j]);
            }
            //收集元素
            int count = 0;
            for(int k = 0; k < 10; k ++){
                if(list.get(k).size() > 0){
                    for(int temp : list.get(k)){
                        arr[count] = temp;
                        count ++;
                    }
                    //清除数据
                    list.get(k).clear();
                }
            }
        }
    }

    /**
     * 确定排序的趟数，由数组中，位数最长的元素决定
     * @param arr
     * @return
     */
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
        int flag = 0;//用来记录最大的数
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

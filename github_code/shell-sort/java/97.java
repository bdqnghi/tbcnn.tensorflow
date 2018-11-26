package com.nanyin.shellSort;

import java.util.Arrays;

/**
 * 希尔排序是将待排序的数组按照增量分割分为多个子序列，然后每个子序列内部惊醒直接插入排序
 * 希尔排序是对直接插入排序的升级
 * 其实对比来看直接插入排序 ，希尔排序还是比较容易理解的，
 */
public class ShellSort {
    public void shellSort(int[] array) {
        int increment, i, j;
        for (increment = array.length / 2; increment > 0; increment /= 2) {
//            根据增量的值构建子序列
            System.out.println(increment);
            for (i = increment; i < array.length; i++) {
                int temp = array[i];
//                在这里跳一跳 分小组 小组内进行直接插入排序
                for (j = i - increment; j >= 0; j = j - increment) {
                    if (array[j] > temp) {
//                      向后挪
                        array[j + increment] = array[j];
                    } else {
                        break;
                    }
                }
                //然后放到正确的位置上也就是循环到 array[j]<temp 的前一个位置上，也就是array[j+increment]
                array[j + increment] = temp;
            }
        }
    }

    public static void main(String[] args) {
        int[] sortArray = new int[]{1, 3, 2, 5, 4, 9, 7, 6, 8};
        ShellSort shellSort = new ShellSort();
        shellSort.shellSort(sortArray);
        System.out.println(Arrays.asList(shellSort).toString());
    }
}

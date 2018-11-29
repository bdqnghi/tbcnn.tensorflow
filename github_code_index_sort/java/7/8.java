package com.example.tsnt.algorithm.sort;

/**
 * @Author: tingshuonitiao
 * @Date: 2018-06-17 18:31
 * @Description: 希尔排序
 */

public class ShellSort implements SortInterface {
    @Override
    public void sort(int[] nums) {
        if (nums == null) return;
        int d = nums.length;
        while (d != 0) {
            d /= 2;
            for (int x = 0; x < d; x++) {
                for (int i = x + d; i < nums.length; i += d) {
                    int insertNum = nums[i];
                    int j = i - d;
                    for (; j >= 0 && insertNum < nums[j]; j -= d) {
                        nums[j + d] = nums[j];
                    }
                    nums[j + d] = insertNum;
                }
            }
        }
    }
}

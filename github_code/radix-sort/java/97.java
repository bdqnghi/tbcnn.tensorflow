package com.ccsi.sorts;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by gxliu on 2017/5/17.
 */
public class RadixSort {
    public static void main(String[] args) {
        int[] nums={342,356,58,576,123};
        radixSort(nums);
        for (int i = 0; i < nums.length; i++) {
            System.out.println(nums[i]);
        }
    }
    public static void radixSort(int[] nums){
        if(nums==null||nums.length<=1)return;
        int max=Integer.MIN_VALUE;
        for (int i = 0; i < nums.length; i++) {
            max=max>nums[i]?max:nums[i];           //找出最大值
        }

        int count=0;                               //计算出最大位数
        while(max>0){
            max/=10;
            count++;
        }

        int dev=10;
        for (int i = 0; i < count; i++) {
            List<Integer>[] buckets=new ArrayList[10];   //声明桶
            for (int j = 0; j < 10; j++) {               //桶初始化，没有会出问题
                buckets[j]=new ArrayList<>();
            }

            for (int j = 0; j < nums.length; j++) {      //元素入桶，根据外循环来决定那哪位（个十百千...）入桶
                int idx=nums[j]%dev*10/dev;
                buckets[idx].add(nums[j]);
            }

            int index=0;
            for (int j = 0; j < 10; j++) {               //出桶
                for (Integer ele:buckets[j]
                     ) {
                    nums[index++]=ele;
                }
            }
            dev*=10;                                     //从个位开始，然后十位，然后百位...
        }
    }
}

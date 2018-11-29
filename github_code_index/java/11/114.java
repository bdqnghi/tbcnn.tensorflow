package com.xdc.basic.algorithm.basic.sort;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * 基数排序，多关键字排序，最低位优先排序(LSD，Least Significant Digit first)
 * 思路：将一个完整的数字关键字拆分成由各位上的数字组成的多关键字，然后对多关键字排序
 * 稳定性的好处：排序算法如果是稳定的，那么从一个键上排序，然后再从另一个键上排序，第一个键排序的结果可以为第二个键排序所用。基数排序就是这样，先按低位排序，逐次按高位排序，低位相同的元素其顺序再高位也相同时是不会改变的。
 */
public class RadixSort
{
    public static void sort(int[] n)
    {
        // 临时存储，可以看成是二重链表结构。 因为关键字可能取值是0-9，共十个数字，所以初始化十个空的列表。
        ArrayList<ArrayList<Integer>> ll = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < 10; i++)
        {
            ll.add(new ArrayList<Integer>());
        }

        // 确定关键字的个数，也即数组中最大元素的位数(10的幂次)。
        int maxPower = getMaxPower(n);

        // 按最低位优先依次对各关键字进行分配和收集，而关键字的个数决定了要进行分配和收集。
        for (int power = 0; power <= maxPower; power++)
        {
            // 分配
            distribute(n, ll, power);

            // 搜集
            collect(n, ll);
        }
    }

    /**
     * 搜集
     */
    private static void collect(int[] n, ArrayList<ArrayList<Integer>> ll)
    {
        int k = 0;
        for (ArrayList<Integer> l : ll)
        {
            for (Integer i : l)
            {
                n[k] = i;
                k++;
            }
            l.clear();
        }
    }

    /**
     * 分配
     */
    private static void distribute(int[] n, ArrayList<ArrayList<Integer>> ll, int power)
    {
        for (int i = 0; i < n.length; i++)
        {
            int digit = (n[i] / ((int) (Math.pow(10, power)))) % 10;
            ll.get(digit).add(n[i]);
        }
    }

    /**
     * 获得数组中最大元素的位数(10的幂次)。
     */
    private static int getMaxPower(int[] n)
    {
        // 获得数组中最大的元素。
        int max = n[0];
        for (int i = 1; i < n.length; i++)
        {
            if (n[i] > max)
            {
                max = n[i];
            }
        }

        // 最大元素的位数。
        int digitalCount = 0;
        while (max != 0)
        {
            digitalCount++;
            max /= 10;
        }

        return digitalCount;
    }

    public static void main(String[] args)
    {
        int[] n = new int[] { 44, 22, 46, 47, 82, 76, 96, 82, 79, 35, 8, 75, 85, 84, 78, 98, 59, 72, 81, 44 };
        RadixSort.sort(n);
        System.out.println(Arrays.toString(n));
    }
}

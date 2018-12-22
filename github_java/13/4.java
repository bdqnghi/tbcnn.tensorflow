package org.learning.algorithm.sort;

/**
 * @ClassName: ShellSort
 * @Description: 希尔排序，原理：算法先将要排序的数组按某个增量d(n/2,n为要排序的个数)分成若干组，魅族记录的下标相差d,对每组中全部元素进行直接插入排序，然后再进行分组
 * @author carlos.chu
 * @date 2016年3月21日 上午11:27:09
 *
 */
public class ShellSort {

    public static void main(String[] args) {
        int a[] = { 1, 54, 6, 3, 78, 34, 12, 45, 56, 100 };
        double d1 = a.length;
        int temp = 0;
        while (true) {
            d1 = Math.ceil(d1 / 2);
            int d = (int) d1;
            for (int x = 0; x < d; x++) {
                for (int i = x + d; i < a.length; i += d) {
                    int j = i - d;
                    temp = a[i];
                    for (; j >= 0 && temp < a[j]; j -= d) {
                        a[j + d] = a[j];
                    }
                    a[j + d] = temp;
                    for (int k = 0; k < a.length; k++) {
                        System.out.print(a[k] + " ");
                    }
                    System.out.println();
                }
            }
            if (d == 1) {
                break;
            }
        }
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + " ");
        }
    }
}

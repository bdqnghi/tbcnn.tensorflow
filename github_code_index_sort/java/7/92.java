package com.liyafeng.algorithm.basic.sort;

/**
 * Created by liyafeng on 2018/2/12.
 */

public class N_Sort_ShellSort {

    /**
     * 希尔排序
     * 时间复杂度：未得出结论，但是大约是n^4/3 或者n^5/4，达不到平方级别
     * ============原理===============
     * 一个变种的插入排序，因为插入排序中一个元素如果是最小的，那么它要移动到数组的最前面
     * 就要交换很多次。我们还可以采用分治法，将数组隔开分为很多子数组，然后每个都采用插入排序
     * -------------------
     * 希尔排序的目的就是将后面较小的元素能少交换的移动到数组前面
     * ==============优缺点=================
     * 优点：能处理大型数组，而且对于任意类型的数组（比如逆序）也能有好的表现
     *
     * @param args
     */
    public static void main(String[] args) {
        int[] array = {1, 124, 54, 34, 34, 6, 5};
        sort(array);
        Util.print(array);
    }

    private static void sort(int[] array) {
        int length = array.length;
        int h = 1;
        while (h < length / 3) {//得出一个递增序列 （1 ,4,13,40.....）
            h = 3 * h + 1;
        }

        while (h >=1) {//修改h，最终h为1，变为传统的插入排序
            for (int i = h; i < length; i++) {//外层选中的是要插入的元素
                //将array[i] 插入到 array[i-h] ,array[i-2h],array[i-3h]...中
                for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {//里层是选中的元素和前面的元素比较，交换
                    Util.exchange(array, j, j - h);
                }
            }
            h /= 3;
        }

    }
}

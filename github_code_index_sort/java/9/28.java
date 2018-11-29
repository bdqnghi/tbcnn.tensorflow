package com.liyafeng.algorithm.basic.sort;

/**
 * Created by liyafeng on 2018/2/12.
 */

public class N_Sort_SelectionSort {

    /**
     * 选择排序(需要n^2/2次比较，和n次交换)
     * 时间复杂度：O(n^2)
     * ===========原理=============
     * 在数组中找出最小的那个元素，和第一个元素交换
     * 再从第二个开始找出最小的，和第二个元素交换
     * 依次类推
     * ===========优缺点=============
     * 缺点：发现一个有序的数组或者所有元素都相等的数组也需要很长时间
     * 优点：移动元素的次数和n是线性关系，移动次数比较少，这是其他排序算法不具备的
     * @param args
     */
    public static void main(String[] args) {
        int[] array = {1, 124, 54, 34, 34, 6, 5};
        sort(array);
        Util.print(array);
    }

    private static void sort(int[] array) {
        int length = array.length;

        for (int i = 0; i < length; i++) {
            int min = i;
            for (int j = i + 1; j < length; j++) {
                if (array[j] < array[min]) {
                    min = j;
                }
            }

            Util.exchange(array, i, min);
        }
    }


}

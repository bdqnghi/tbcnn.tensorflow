package com.ericzong.algorithm.sort;

import java.lang.reflect.Array;
import java.util.Comparator;

/**
 * @author Eric Zong
 *
 * 冒泡排序
 * 算法逻辑：
 *    依次将相临2个元素比较，如果前者比后者大，就交换
 *    第1趟：依次比较a[0]-a[n-1]相临元素，根据比较结果交换，完成时最大元素换到了a[n-1]；
 *    第2趟：依次比较a[0]-a[n-2]相临元素，根据比较结果交换，完成时次大元素换到了a[n-2]；
 *    ...
 *    第i趟：依次比较a[0]-a[n-i]相临元素，根据比较结果交换，完成时次大元素换到了a[n-i]；
 *    ...
 *    理论上，n个元素的序列需要经过 n-1 趟排序，但是实际上当某一趟排序没有元素交换时序列已是有序的，就可以结束排序了
 *
 * 应用范围：
 * 1. 仅支持数组排序；
 * 2. 仅支持 int、Comparable 及其他任意类类型（需指定比较器）排序。
 */
public class Bubble {
    public static <E extends Comparable<E>> void sort(E[] data) {
        sortImpl(data, null);
    }

    public static void sort(int[] data) {
        sortImpl(data, null);
    }

    public static <E> void sort(E[] data, Comparator<E> comparator) {
        sortImpl(data, comparator);
    }

    private static void sortImpl(Object data, Comparator comparator) {
        int length = Array.getLength(data);
        if (length <= 1) return;

        for (int i = 0; i < length; i++) {
            boolean swap = false;
            for (int j = 0; j < length - i - 1; j++) {
                swap |= swap(data, j, j + 1, comparator);
            }

            if (!swap) { // 优化排序，没有发生交换，则数据已有序
                break;
            }
        }
    }

    private static boolean swap(Object data, int i, int j, Comparator comparator) {
        if (!data.getClass().isArray()) {
            throw new RuntimeException("Not Array");
        }

        Object first = Array.get(data, i);
        Object second = Array.get(data, j);

        if (isOrdered(first, second, comparator)) {
            return false;
        }

        Array.set(data, i, second);
        Array.set(data, j, first);

        return true;
    }

    private static boolean isOrdered(Object first, Object second, Comparator comparator) {
        if (comparator != null) {
            return comparator.compare(first, second) <= 0;
        } else if (first instanceof Comparable) {
            return ((Comparable) first).compareTo(second) <= 0;
        }

        throw new RuntimeException("Uncomparable!");
    }
}

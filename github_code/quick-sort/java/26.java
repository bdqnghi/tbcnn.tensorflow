package com.nero.algorithm.quicksort;

import java.util.Random;

/**
 * Created with IntelliJ IDEA.
 * User: nero
 * Date: 13-7-9
 * Time: 下午5:24
 * Introduction
 */

public class QuickSortDemo {

    static final int SIZE = 30;
    private int[] randomNub = new int[SIZE];

    private int[] generateRandomNum() {
        Random random = new Random();
        for (int i = 0; i < SIZE; i++) {
            randomNub[i] = random.nextInt(100) + 1; //随即1到100之间的整数
        }
        return randomNub;
    }

    private void print() {
        for (int i : randomNub) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    private static void print(String str) {
        System.out.println(str);
    }

    /**
     * 快速排序之
     * 随即基值 这种算法是三种里面最慢的，因为每次产生交换都要多一次无效比较
     * @param numbers 排序数组
     * @param left 左边索引
     * @param right 右边索引
     */
    private void quickSortAlgWithRd(int[] numbers, int left, int right) {
        if (left < right) {
            //取一个随机数
            int index = (int) (Math.random() * (right - left + 1) + left);
            int flag = numbers[index];
            int i = left;
            int j = right;
            int k = index;
            while (i < j) {
                //右边值大于基值则继续循环
                while (j > i && numbers[j] > flag) j--;
                //左边值小于等于基值则继续循环
                while (i < j && numbers[i] <= flag) i++;
                numbers[k] = numbers[j];
                numbers[j] = numbers[i];
                k = i;
            }
            //把取出的基值放回数组
            numbers[k] = flag;
            quickSortAlgWithRd(numbers, left, k - 1);
            quickSortAlgWithRd(numbers, k + 1, right);
        }
    }

    /**
     * 快速排序之
     * 基值从左开始取
     * @param numbers 排序数列
     * @param left  左边索引
     * @param right 右边索引
     */
    private void quickSortAlgFromLeft(int[] numbers, int left, int right) {
        if (left < right) {
            int flag = numbers[left]; //取基值
            int i = left;
            int j = right;
            while (i < j) {
                while (j > i && numbers[j] > flag) j--;
                if (j > i) numbers[i++] = numbers[j];
                while (i < j && numbers[i] <= flag) i++;
                if (i < j) numbers[j--] = numbers[i];
            }
            numbers[i] = flag;
            quickSortAlgFromLeft(numbers, left, i - 1);
            quickSortAlgFromLeft(numbers, i + 1, right);
        }
    }

    /**
     * 快速排序之
     * 基值从右开始取
     * @param numbers 排序数列
     * @param left  左边索引
     * @param right 右边索引
     */
    private void quickSortAlgFromRight(int[] numbers, int left, int right) {
        if (left < right) {
            int flag = numbers[right];
            int i = left;
            int j = right;
            while (i < j) {
                while (i < j && numbers[i] <= flag) i++;
                if (i < j) numbers[j--] = numbers[i];
                while (j > i && numbers[j] > flag) j--;
                if (j > i) numbers[i++] = numbers[j];
            }
            numbers[j] = flag;
            quickSortAlgFromRight(numbers, left, j - 1);
            quickSortAlgFromRight(numbers, j + 1, right);
        }
    }

    private static class DemoTest {
        public static void main(String[] args) {
            QuickSortDemo quickSortDemo = new QuickSortDemo();
            print("============ LEFT ============");
            //generate numbers
            print("Generate number.....");
            int[] array1 = quickSortDemo.generateRandomNum();
            quickSortDemo.print();
            //sort
            quickSortDemo.quickSortAlgFromLeft(array1, 0, array1.length - 1);
            print("After sort.....");
            quickSortDemo.print();

            print("============ RIGHT ============");
            //generate numbers
            print("Generate number.....");
            int[] array2 = quickSortDemo.generateRandomNum();
            quickSortDemo.print();
            //sort
            quickSortDemo.quickSortAlgFromRight(array2, 0, array2.length - 1);
            print("After sort.....");
            quickSortDemo.print();

            print("============ RANDOM ============");
            //generate numbers
            print("Generate number.....");
            int[] array3 = quickSortDemo.generateRandomNum();
            quickSortDemo.print();
            //sort
            quickSortDemo.quickSortAlgWithRd(array3, 0, array3.length - 1);
            print("After sort.....");
            quickSortDemo.print();

        }
    }
}


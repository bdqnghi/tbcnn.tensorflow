package com.nero.algorithm.quicksort;

import java.util.Random;



public class QuickSortDemo {

    static final int SIZE = 30;
    private int[] randomNub = new int[SIZE];

    private int[] generateRandomNum() {
        Random random = new Random();
        for (int i = 0; i < SIZE; i++) {
            randomNub[i] = random.nextInt(100) + 1; 
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

    
    private void quickSortAlgWithRd(int[] numbers, int left, int right) {
        if (left < right) {
            
            int index = (int) (Math.random() * (right - left + 1) + left);
            int flag = numbers[index];
            int i = left;
            int j = right;
            int k = index;
            while (i < j) {
                
                while (j > i && numbers[j] > flag) j--;
                
                while (i < j && numbers[i] <= flag) i++;
                numbers[k] = numbers[j];
                numbers[j] = numbers[i];
                k = i;
            }
            
            numbers[k] = flag;
            quickSortAlgWithRd(numbers, left, k - 1);
            quickSortAlgWithRd(numbers, k + 1, right);
        }
    }

    
    private void quickSortAlgFromLeft(int[] numbers, int left, int right) {
        if (left < right) {
            int flag = numbers[left]; 
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
            
            print("Generate number.....");
            int[] array1 = quickSortDemo.generateRandomNum();
            quickSortDemo.print();
            
            quickSortDemo.quickSortAlgFromLeft(array1, 0, array1.length - 1);
            print("After sort.....");
            quickSortDemo.print();

            print("============ RIGHT ============");
            
            print("Generate number.....");
            int[] array2 = quickSortDemo.generateRandomNum();
            quickSortDemo.print();
            
            quickSortDemo.quickSortAlgFromRight(array2, 0, array2.length - 1);
            print("After sort.....");
            quickSortDemo.print();

            print("============ RANDOM ============");
            
            print("Generate number.....");
            int[] array3 = quickSortDemo.generateRandomNum();
            quickSortDemo.print();
            
            quickSortDemo.quickSortAlgWithRd(array3, 0, array3.length - 1);
            print("After sort.....");
            quickSortDemo.print();

        }
    }
}


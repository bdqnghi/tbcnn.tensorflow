package pers.vin.base.dataStructure;

import java.util.Arrays;

/**
 * Created by vin on 05/02/2018.
 */
public class Sort_QuickSort {

    static void bubbleSort(int[] arr) {
        // 原理 the principle
        // 1 like bubble in water that will float in top
        //
        // 1
        // 2
        int temp;
        for (int i = 0; i < arr.length - 1; i++) {
            for (int j = i + 1; j < arr.length; j++) {
                if (arr[i] > arr[j]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }

    static void chooseSort(int[] arr) {
        int temp;
        for (int i = 0; i < arr.length - 1; i++) {
            int least = i;
            for (int j = i + 1; j < arr.length; j++) {
                if (arr[j] < arr[least]) {
                    least = j;
                }

            }
            temp = arr[i];
            arr[i] = arr[least];
            arr[least] = temp;
        }
    }


    //快速排序
    public static void sort(int a[], int low, int hight) {
        int i, j, index;
        if (low > hight) {
            return;
        }
        i = low;
        j = hight;
        index = a[i]; // 用子表的第一个记录做基准
        int loop = 0;
        while (i < j) { // 从表的两端交替向中间扫描
            while (i < j && a[j] >= index) {
                j--;

            }

            if (i < j) {

                a[i++] = a[j];// 用比基准小的记录替换低位记录

            }


            while (i < j && a[i] < index) {
                i++;

            }

            if (i < j) // 用比基准大的记录替换高位记录
            {
                a[j--] = a[i];
            }

            System.out.println("i is " + i);
            System.out.println("j is " + j);
            loop++;
            System.out.println(loop+" loop " + Arrays.toString(a));

        }
        System.out.println("===");

        a[i] = index;// 将基准数值替换回 a[i]
        sort(a, low, i - 1); // 对低子表进行递归排序
        sort(a, i + 1, hight); // 对高子表进行递归排序

    }

    public static void quickSort(int a[]) {
        sort(a, 0, a.length - 1);
    }

    public static void main(String[] args) {
        int[] arr = new int[]{2, 1, 3, 1};
        int[] arr2 = arr.clone();
        int[] arr3 = arr.clone();

        bubbleSort(arr);
        System.out.println(Arrays.toString(arr));

        chooseSort(arr2);

        System.out.println(Arrays.toString(arr2));

        int a[] = {49, 38, 65, 97, 76, 13, 27, 49};
        int i = 0;
        System.out.println(a[i]);
        quickSort(a);
        System.out.println(Arrays.toString(a));
    }
}

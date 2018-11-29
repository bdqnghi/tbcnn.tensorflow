package lw.learn.algorithm.sort.sort1;

import lw.learn.utils.SortUtil;

import java.util.Arrays;
import java.util.Random;

/**
 * @Author lw
 * @Date 2018-09-26 08:30:18
 **/
public class Bubble {

    public static void main(String[] args) {
        int count = 15;
        for (int i = 0; i < count; i++) {
            int arrLength = new Random().nextInt(30) + 1;
            int[] arr = new int[arrLength];
            for (int j = 0; j < arrLength; j++) {
                arr[j] = new Random().nextInt(100);
            }
            System.out.println(Arrays.toString(sort(arr)) + " is order ? " + SortUtil.isOrder(arr));

        }

    }


    public static int[] sort(int[] arr) {

        for (int i = arr.length - 1; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (arr[j] > arr[j + 1]) {
                    SortUtil.swap(arr, j, j + 1);
                }
            }
        }

        return arr;
    }
}

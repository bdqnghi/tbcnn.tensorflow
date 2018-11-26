package io.loper.algorithm.sort;

/**
 * @author JoongWon
 */
public class ShellSort {

    public static void shellSort(int[] arr) {
        if (SortUtil.isEmpty(arr)) {
            return;
        }

        final int length = arr.length;
        int interval = length / 2;

        while (interval >= 1) {
            for (int i = 0; i < length; i++) {
                intervalSort(arr, i, length - 1, interval);
            }

            interval /= 2;
        }
    }

    private static void intervalSort(int[] arr, int begin, int end, int interval) {
        for (int i = begin + interval; i <= end; i += interval) {
            final int key = arr[i];
            int position = i;

            while (position >= interval && key < arr[position - interval]) {
                arr[position] = arr[position - interval];
                position -= interval;
            }

            arr[position] = key;
        }
    }
}

package pl.coderstrust.sort;

import java.util.Arrays;

/**
 * Created by Adam on 2018-02-13.
 */
public class SelectionSortSort {
    public static void main(String[] args) {

        int[] array = {5, 4, 1, 2, 9, 2, 7};

        System.out.println(Arrays.toString(array));

        SelectionSortSort myObject = new SelectionSortSort();
        myObject.sort(array);

        System.out.println(Arrays.toString(array));

    }

    public int[] sort(int[] array) {
        for (int j = 0; j < array.length; ++j) {
            int minimumNumberIndex = getMinimumNumberIndex(array, j);
            swap(array, j, minimumNumberIndex);

        }
        return array;
    }

    public int getMinimumNumberIndex(int[] array, int j) {
        int minimumNumberIndex = j;
        for (int i = j; i < array.length; ++i)
            if (array[i] < array[minimumNumberIndex]) {
                minimumNumberIndex = i;
            }
        return minimumNumberIndex;
    }

    public static void swap(int[] array, int j, int minimumNumberIndex) {
        int temp = array[j];
        array[j] = array[minimumNumberIndex];
        array[minimumNumberIndex] = temp;
    }


}


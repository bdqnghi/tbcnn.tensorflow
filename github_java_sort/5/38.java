package com.gerrard.sort.compare.cocktail;

import com.gerrard.sort.Sort;
import com.gerrard.util.ArrayHelper;


public class CocktailSort implements Sort {

    @Override
    public void sort(int[] array) {
        int left = 0;
        int right = array.length - 1;
        while (left < right) {
            for (int i = left; i < right; ++i) {
                if (array[i] > array[i + 1]) {
                    ArrayHelper.swap(array, i, i + 1);
                }
            }
            right--;
            for (int i = right; i > left; --i) {
                if (array[i] < array[i - 1]) {
                    ArrayHelper.swap(array, i, i - 1);
                }
            }
            left++;
        }
    }
}

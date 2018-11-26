package com.gerrard.sort.compare.cocktail;

import com.gerrard.sort.Sort;
import com.gerrard.util.ArrayHelper;

/**
 * Cocktail-Sort is a slight variation of Bubble-Sort, also with complexity O(n^2).
 * Different from Bubble-Sort(which repeatedly passing through the list from bottom to top),
 * Cocktail-Sort passes alternately from bottom to top and then from top to bottom.
 * <p>
 * Bubble-Sort gives a tendency for larger elements to the bottom,
 * however Cocktail-Sort gives both tendency for larger elements to the bottom and smaller elements to the top.
 * So the whole array can be more efficient to be ordered.
 * <p>
 * A typical array for Cocktail-Sort is like [2,3,4,5,1].
 */
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

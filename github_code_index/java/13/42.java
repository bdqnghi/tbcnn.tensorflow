package com.gerrard.sort.compare.shell;

import com.gerrard.sort.Sort;

/**
 * Shell-Sort is based on Insertion-Sort, also with complexity O(n^2).
 * First, give a variable: gap, usually starts with array.length/2.
 * Consider every gap element as an array(means the array is separated into gap parts).
 * On every array, use Insertion-Sort.
 * Shrink variable gap, usually gap/2, do as previous until gap=1.
 * <p>
 * Although Shell-Sort doesn't decrease the complexity, its average-complexity is about O(n^1.3),
 * better than other O(n^2)-complexity sort method.
 * <p>
 * Its good average-complexity is based on a feature of Insertion-Sort:
 * Insertion-Sort plays a good performance on mainly-well-ordered array.
 */
public class ShellSort implements Sort {

    private int shrink = 2;

    public int getShrink() {
        return shrink;
    }

    public void setShrink(int shrink) {
        this.shrink = shrink;
    }

    @Override
    public void sort(int[] array) {
        int gap = array.length / shrink;
        while (gap > 0) {
            for (int i = 0; i < gap; i++) {
                insertionSortWithGap(array, gap, i);
            }
            gap /= shrink;
        }
    }

    private void insertionSortWithGap(int[] array, int gap, int startIndex) {
        for (int i = startIndex + gap; i < array.length; i += gap) {
            int cur = array[i];
            boolean flag = false;
            for (int j = i - gap; j >= 0; j -= gap) {
                if (cur < array[j]) {
                    array[j + gap] = array[j];
                } else {
                    array[j + gap] = cur;
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                array[startIndex] = cur;
            }
        }
    }
}

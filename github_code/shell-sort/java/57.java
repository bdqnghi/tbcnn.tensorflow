package org.algorithmprac.sort;

/**
 * 希尔排序 [!stable] [!online].
 * 时间复杂度的分析很复杂, 至今仍是一项挑战. 该实现的最坏时间复杂度为 O(N^(3/2)).
 */
public class ShellSorter extends AbstractCostAwareSorter {

    @Override
    protected void sortInternal(Comparable[] a) {
        int h = 1;
        while (h < a.length / 3) {
            h = 3 * h + 1;
        }
        // 逐渐缩小排序间隔
        while (h >= 1) {
            // 与插入排序相同, 对 h 个子数组同时做插入排序, 每次排序完成后数组为 h 有序的
            for (int i = h; i < a.length; ++i /* ++i 不够直观; 更直观的是 i+=h, 而 i 的起始值为 [h, 2h), 效果是等价的 */) {
                for (int j = i; j >= h && less(a[j], a[j - 1]); j -= h) {
                    swap(a, j, j - h);
                }
            }
            h /= 3;
        }
    }

    @Override
    public String getName() {
        return "shell-sort";
    }
}

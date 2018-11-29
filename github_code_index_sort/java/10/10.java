package net.tanpeng.arithmetic.arithmetic4.sort;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * 桶排序
 * 桶排序类似于计数排序，但不完全一样：
 * 计数排序是一种特殊的桶排序，它里面每个桶内的数据大小是相同的
 */
public class Bucket {
    public static void main(String[] args) {
        int[] a = new int[]{5, 2, 4, 6, 7};
        bucketSort(a);
        for (int i : a) {
            System.out.println(i);
        }
    }

    public static void bucketSort(int[] a) {
        int n = a.length;
        //创建桶
        List<List<Integer>> bucket = new ArrayList<>();
        //初始化桶，这里就当做 10 个吧
        for (int i = 0; i < n; i++) {
            bucket.add(new ArrayList<>());
        }

        // 划分桶
        for (int i = 0; i < n; i++) {
            bucket.get(f(i)).add(a[i]);
        }

        // 对每个桶里的数据进行排序
        for (int i = 0; i < bucket.size(); i++) {
            if (!bucket.get(i).isEmpty())
                Collections.sort(bucket.get(i)); // 调用系统自带的快排
        }

        // 还原数组
        int k = 0;
        for (int i = 0; i < bucket.size(); i++) {
            for (int item : bucket.get(i)) {
                a[k++] = item;
            }
        }
    }

    private static int f(int x) {
        return x / 10;
    }


}

package sort.uncomparison;

import java.util.ArrayList;
import java.util.Collections;

/**
 * 桶排序
 * *********************
 * 可用于最大最小值相差较大的情况
 * 非比较排序,不受NlogN下限影响
 * 1.设置一定量的数组当空桶
 * 2.遍历，把每个元素放入对应的桶中
 * 3.对每个不是空的桶排序
 * 4.不是空桶的放回去
 *
 * @author Noblel
 */
public class BucketSort {
    public static void sort(int[] arr) {
        int max = Integer.MAX_VALUE;
        int min = Integer.MIN_VALUE;

        for (int i = 0; i < arr.length; i++) {
            max = Math.max(max, arr[i]);
            min = Math.min(min, arr[i]);
        }
        
        //桶数
        int bucketNum = (max - min) / arr.length + 1;
        ArrayList<ArrayList<Integer>> bucketArr = new ArrayList<>(bucketNum);
        for (int i = 0; i < bucketNum; i++) {
            bucketArr.add(new ArrayList<>());
        }

        //将每个元素放入桶中
        for (int i = 0; i < arr.length; i++) {
            int num = (arr[i] - min) / (arr.length);
            bucketArr.get(num).add(arr[i]);
        }

        //对每个桶排序
        for (int i = 0; i < bucketArr.size(); i++) {
            Collections.sort(bucketArr.get(i));
        }

        System.out.println(bucketArr.toString());
    }
}

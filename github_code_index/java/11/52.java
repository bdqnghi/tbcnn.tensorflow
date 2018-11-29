package sort;

/**
 * Created by zhanglei on 2015/1/7.
 * 基数排序
 * 多关键字排序，多关键字排序的思路是将待排数据里德排序关键字拆分成多个排序关键字，根据子关键字对待排序数据进行排序。
 * 多关键字排序时有两种解决方案：最高位优先法，最低位优先法。
 * 将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。
 * 然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序完成以后,数列就变成一个有序序列。
 * 例如序列：135,242,192,93，345,11，24,19
 * 个位收集：11,242,192,93,24,135,345,19
 * 十位收集：11,19,24,135,242,345,192,93
 * 百位收集：11,19,24,93,135,192,242,345
 */

import java.util.LinkedList;
import java.util.Queue;

public class RadixSort implements Solution {
    @Override
    public int[] sort(int[] num) {
        //确定位数
        int max = num[0], count = 0;
        for (int i = 1; i < num.length; i++) {
            if (num[i] > max)
                max = num[i];
        }

        for (; max > 0; max /= 10)
            count++;

        radixSort(num, count);
        return num;
    }

    private void radixSort(int[] num, int count) {
        Queue<Integer>[] bucket = new Queue[10];
        for (int i = 0; i < 10; i++)
            bucket[i] = new LinkedList<Integer>();

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < num.length; j++) {  //依次按照个位、十位等放入桶中
                int key = num[j] % (int) Math.pow(10, i + 1) / (int) Math.pow(10, i);
                bucket[key].add(num[j]);
            }

            int index = 0;
            for (int k = 0; k < 10; k++) {  //出桶，数组重排
                if (bucket[k].size() == 0)
                    continue;

                while (!bucket[k].isEmpty())
                    num[index++] = bucket[k].poll();
            }
        }
    }
}

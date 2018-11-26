package cn.wkq.algorithm.sort;

import java.util.Arrays;

/**
 * 希尔排序
 * <p>
 * References
 * https://zh.wikipedia.org/wiki/%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F
 * http://www.cnblogs.com/chengxiao/p/6104371.html
 * http://bubkoo.com/2014/01/15/sort-algorithm/shell-sort/
 * https://blog.csdn.net/morewindows/article/details/6668714
 *
 * @author: weikeqin.cn@gmail.com
 */
public class ShellSort {

    /**
     * 希尔排序 针对有序序列在插入时采用交换法
     * <pre>
     *
     *   基本思想：先将整个待排元素序列分割成若干子序列(由相隔某个"增量"的元素组成的)分别进行直接插入排序，
     *            然后依次缩减增量再进行排序，待整个序列中的元素基本有序(增量足够小)时，
     *            再对全体元素进行一次直接插入排序(增量为1)。
     *
     *   原始数据        2  7  8  2  7  6  1  3  0
     *   第一趟排序结果  0  6  1  2  2  7  8  3  7
     *   第二趟排序结果  0  1  2  2  3  6  7  7  8
     *
     *   在希尔排序时，先对数据进行分组，然后对每组的数据做插入排序，然后合并多组的数据
     *   在代码实现时，对每组做插入排序要稍微转一下弯
     *
     *   希尔排序时增量(步长)选择是一个难题
     *   当增量序列为 dlta[k] = (2^(t-k+1)) - 1 时，其时间复杂度为O(n^(3/2))，其中t为排序趟数， 1 <= k <= t < log2^(n+1)
     * 　当n在特定范围内，希尔排序所需的比较和移动次数约为n^1.3，当n -> 无穷， 可减少到n(log2^n)^(2^[2]) 。
     *
     * </pre>
     *
     * @param arr
     * @author weikeqin.cn@gmail.com
     */
    public static int[] shellSort(int[] arr) {
        int gap = 1, i, j, len = arr.length;
        int temp;
        while (gap < len / 3) {
            // <O(n^(3/2)) by Knuth,1973>: 1, 4, 13, 40, 121, ...
            gap = gap * 3 + 1;
        }
        // 循环趟
        for (; gap > 0; gap /= 3) {
            // 插入排序
            for (i = gap; i < len; i++) {
                temp = arr[i];
                // 同一组循环比较，目的是把最小的放到该组最前面
                for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap) {
                    arr[j + gap] = arr[j];
                }
                arr[j + gap] = temp;
            } // end for

            print(arr);
        } // end for

        return arr;
    }

    /**
     * @author weikeqin.cn@gmail.com
     */
    public static int[] shellSort2(int[] arr) {
        int i, j, gap, len = arr.length;
        for (gap = len / 2; gap > 0; gap /= 2) {
            for (i = gap; i < len; i++) {
                for (j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap) {
                    swap(arr, arr[j], arr[j + gap]);
                }
            }
        }
        return arr;
    }

    /**
     * @author weikeqin.cn@gmail.com
     */
    public static int[] shellSort3(int[] arr) {

        int length = arr.length;
        for (int gap = length / 2; gap > 0; gap /= 2) {
            System.out.println("gap:" + gap);

            // 每一趟相当于插入排序，把每组的小的往前放
            // 这个i从gap开始的目的是为了避免后面数组越界异常
            // i从0开始也可以，但是试了就会发现，从0 ~ (gap-1) 全部数组越界，还要跳过，相当于i从gap开始
            for (int i = gap; i < length; i++) {
                System.out.println("i:" + i);
                int j = i;

                // 可以把上面的for循环改成从0开始，发现 0 ~ (gap-1) 全部跳过
                if (j - gap < 0) {
                    System.out.println("比较  第" + j + "个元素 与  第" + (j - gap) + "个元素    数组越界，    跳过");
                    continue;
                }

                System.out.println("比较  第" + j + "个元素 与  第" + (j - gap) + "个元素。");
                while (j - gap >= 0 && arr[j] < arr[j - gap]) {
                    System.out.println("交换  第" + j + "个元素:" + arr[j] + "  与  第" + (j - gap) + "个元素:" + arr[j - gap]);
                    swap(arr, j, j - gap);
                    // 同一组迭代比较，目的是把最小的放到该组最前面
                    j -= gap;

                    print(arr);
                }

            }

            System.out.println("----一趟排序完，打印数组----");
            print(arr);
        }

        return arr;
    }



    /**
     * 希尔排序 针对有序序列在插入时采用移动法。
     *
     * @param arr
     */
    public static int[] shellSort4(int[] arr) {

        int length = arr.length;

        //增量gap，并逐步缩小增量
        for (int gap = length / 2; gap > 0; gap /= 2) {

            //从第gap个元素，逐个对其所在组进行直接插入排序操作
            for (int i = gap; i < length; i++) {
                int j = i;

                // 同一组的整体处理
                int temp = arr[j];
                if (arr[j] < arr[j - gap]) {
                    while (j - gap >= 0 && temp < arr[j - gap]) {
                        //移动法
                        arr[j] = arr[j - gap];
                        j -= gap;
                    }
                    arr[j] = temp;
                }

            } // end for

        } // end for

        return arr;
    }


    /**
     * 交换数组元素
     *
     * @param arr
     * @param a
     * @param b
     */
    public static void swap(int[] arr, int a, int b) {
        int tmp = 0;
        tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
    }

    /**
     * 交换数组元素
     *
     * @param arr
     * @param a
     * @param b
     */
    public static void swapUseCpu(int[] arr, int a, int b) {
        arr[a] = arr[a] + arr[b];
        arr[b] = arr[a] - arr[b];
        arr[a] = arr[a] - arr[b];
    }

    /**
     * @param arr
     */
    private static void print(int[] arr) {
        System.out.println(Arrays.toString(arr));
    }

    /**
     * @param args
     */
    public static void main(String[] args) {

        int[] a = null;
        a = new int[]{2, 7, 8, 2, 7, 6, 1, 3, 0};
        //a = new int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        //a = new int[]{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        //a = new int[]{49, 38, 65, 97, 76, 13, 27, 49, 55, 4};
        //a = new int[]{8, 9, 1, 7, 2, 3, 5, 4, 6, 0};
        //a = new int[]{49, 38, 65, 97, 26, 13, 27, 49, 55, 4};
        System.out.println("---------------排序前--------------------");
        print(a);

        System.out.println("--------------开始排序--------------------");
        a = shellSort(a);

        System.out.println("---------------排序后---------------------");
        print(a);
    }


}

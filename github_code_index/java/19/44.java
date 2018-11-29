package com.meiliinc.mls.algorithm.sort;

/**
 * 桶排序
 * Created with IntelliJ IDEA.
 * User: jiexiu
 * Date: 16/9/1
 * Time: 上午10:06
 * Email:jiexiu@mogujie.com
 */
public class SortAlgoBucketSort {
    /**
     * 算法基本思想: 桶排序的思想近乎彻底的分治思想。假设现在需要对一亿个数进行排序。
     * 我们可以将其等长地分到10000个虚拟的“桶”里面，这样，平均每个桶只有10000个数。
     * 如果每个桶都有序了，则只需要依次输出为有序序列即可。具体思路是这样的：
     * 1. 将待排数据按一个映射函数f(x)分为连续的若干段。理论上最佳的分段方法应该使数据平均分布；
     * 实际上，通常采用的方法都做不到这一点。显然，对于一个已知输入范围在【0，10000】的数组，
     * 最简单的分段方法莫过于x/m这种方法，例如，f(x)=x/100。
     * "连续的”这个条件非常重要，它是后面数据按顺序输出的理论保证
     * 2. 分配足够的桶，按照f(x)从数组起始处向后扫描，并把数据放到合适的桶中。对于上面的例子，
     * 如果数据有10000个，则我们需要分配101个桶（因为要考虑边界条件：f(x)=x/100会产生【0，100】共101种情况），
     * 理想情况下，每个桶有大约100个数据
     *3. 对每个桶进行内部排序，例如，使用快速排序。注意，如果数据足够大，这里可以继续递归使用桶排序，
     * 直到数据大小降到合适的范围。
     * 4. 按顺序从每个桶输出数据。例如，1号桶【112，123，145，189】，2号桶【234，235，250，250】，3号桶【361】，
     * 则输出序列为【112，123，145，189，234，235，250，250，361】。
     * 5. 排序完成
     *
     * @param arr 输入的待排序数组
     * @return 排序后的数组
     */
    public static int[] bucketSort(int[] arr){
        //10个桶, 每个桶里面10个元素
        int bucketNum = 10;
        Integer[][] buckets = new Integer[bucketNum][arr.length];
        for (int num : arr){
            int bucketIdx = num / 10;
            //查找空位,并放入指定编号的桶
            for (int j = 0; j < arr.length; j++){
                if (buckets[bucketIdx][j] == null){
                    buckets[bucketIdx][j] = num;
                    break;
                }
            }
        }

        //对每个桶进行排序
        //小桶排序
        for (int i = 0; i < buckets.length; i++){
            //insertion sort
            for (int j = 1; j < buckets[i].length; ++j){
                if(buckets[i][j] == null){
                    break;
                }
                int value = buckets[i][j];
                int position = j;
                while (position > 0 && buckets[i][position-1] > value){
                    buckets[i][position] = buckets[i][position-1];
                    position--;
                }
                buckets[i][position] = value;
            }
        }
        int k = 0;
        //输出
        for (int i = 0; i < bucketNum; i++){
            for (int j = 0; j < buckets[i].length; j++){
                if (null == buckets[i][j]){
                    continue;
                }
                arr[k++] = buckets[i][j];
            }
        }
        return arr;
    }

    private static void printArray(int[] arr){
        for (int num : arr){
            System.out.printf("%d,", num);
        }
    }
    public static void main(String[] args) {
        int[] arr = new int[]{3,1,41,62,73,22};
        arr = bucketSort(arr);
        printArray(arr);
    }
}

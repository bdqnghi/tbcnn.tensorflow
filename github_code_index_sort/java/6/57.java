package sort;

/**
 * 桶排序的思想,不基于比较
 * 基数排序 f(N)=O(N)  s(N)=O(M) (M为桶的数量)  稳定
 * 准备0~9号十个桶，把数组中的每个数都看做是十进制的，首先根据个位上的数放入0~9号桶中，然后从0~9号桶中依次
 * 倒出所有的数；接下来在根据十位上的数重复上述过程....... 直到数组中最大数的最高位结束。
 * 最后一次倒出的顺序就排好序了。
 */
public class Sort_09_RadixSort {

    public static int[] radixSort(int[] arr) {
        if (arr == null || arr.length < 2)
            return null;
        int a = 1;//除数，分离出关键字的各个整数位
        int m = 1;//指向的位数
        int k = 0;// 最后输出的结果
        //高维表示0-9个桶，低维表示每个关键字各个位上的余数,每个桶内可能有n个值
        int[][] number = new int[10][arr.length];
        //创建一个数组表示number数组的每一个桶里面的数目，
        int[] count = new int[10];
        while (m <= 4) {
            for (int j = 0; j < arr.length; j++) {
                int lsd = ((arr[j] / a) % 10);//得到余数
                number[lsd][count[lsd]] = arr[j];
                count[lsd]++;//余数为lsd,在哪个桶内也确定，因此将桶内的数目自加
            }
            for (int p = 0; p < 10; p++) {
                //将桶内的值取出，重新放入到数组中
                if (count[p] != 0) {//判断在哪个桶内的并且在该桶内的关键字的个数不为0
                    for (int q = 0; q < count[p]; q++) {
                        arr[k] = number[p][q];
                        k++;
                    }
                }
                count[p] = 0;
            }
            k = 0;
            a *= 10;
            m++;
        }
        return arr;
    }

    public static void printArray(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
    }

    public static void main(String[] args) {
        int[] arr = {21, 5, 4, 8, 2, 3, 0, 9, 7, 4, 5, 10};
        printArray(radixSort(arr));
    }
}

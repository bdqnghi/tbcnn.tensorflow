package sort;

/**
 * 希尔排序   O(N*logN) s(N)=O(1) 不稳定
 * 改良的插入排序，步长可调整(由大到小)，......，最后过程仍为步长为1的插入排序
 * 希尔排序的关键在于步长的选择
 */
public class Sort_07_ShellSort {

    public static int[] shellSort(int[] arr) {
        if (arr == null || arr.length == 0) {
            return arr;
        }
        shell(arr);
        return arr;
    }

    public static void shell(int[] arr) {
        int cur = 0;
        for (int i = arr.length / 2; i > 0; i--) {    //i代表为步长，从n/2开始递减，知道为1（即插入排序）
            for (int j = i; j < arr.length; j++) {
                cur = j;
                for (int k = j - i; k >= 0; k -= i) {
                    if (arr[cur] >= arr[k]) {
                        break;
                    } else {
                        swap(arr, cur, k);
                        cur = k;
                    }
                }
            }
        }
    }

    public static void swap(int[] arr, int index1, int index2) {
        int temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }

    public static void printArray(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
    }

    public static void main(String[] args) {
        int[] arr = {21, 5, 4, 8, 2, 3, 0, 9, 7, 4, 5, 10};
        printArray(shellSort(arr));
    }
}

package sort;

/**
 * 选择排序--只会移动N次  f(N)=O(N*N) s(N)=O(1)  不稳定   N小时较好
 * 选择排序的主要思想：首先找到数组中最小的那个元素，其次，将它和第一个元素交换。
 * 接下来找第二小和第二个交换。运行时间和输入无关，数据移动最少。当数据量较小的时候适用。
 */
public class Sort_02_SelectionSort {

    public static int[] selectionSort(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            int index = i;
            int min = arr[i];
            for (int j = i; j < arr.length; j++) {
                if (arr[j] < min) {
                    index = j;
                    min = arr[j];
                }
            }
            swap(arr, i, index);
        }
        return arr;
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
        int[] arr = {1, 5, 4, 8, 2, 3, 0, 9, 7, 4, 5};
        printArray(selectionSort(arr));
    }
}

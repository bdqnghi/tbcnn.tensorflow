package sort;

/**
 * 插入排序  f(N)=O(N*N) s(N)=O(1)  稳定  大部分已经排好序是较好
 * 数据量小时使用。并且大部分已经被排序。
 */
public class Sort_03_InsertionSort {

    public static int[] insertionSort(int[] arr) {
        for (int i = 1; i < arr.length; i++) {
            for (int j = i; j != 0; j--) {
                if (arr[j-1] > arr[j]) {
                    swap(arr, j-1, j);
                } else {
                    break;
                }
            }
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
        printArray(insertionSort(arr));
    }
}

package com.meiliinc.mls.algorithm.sort;

/**
 * 堆排序
 * Created with IntelliJ IDEA.
 * User: jiexiu
 * Date: 16/9/1
 * Time: 下午4:22
 * Email:jiexiu@mogujie.com
 */
public class SortAlgoHeapSort {

    /**
     * 移动节点i
     * @param arr
     * @param i
     */
    private static void shiftUp(int[] arr, int i){
        int temp = arr[i];
        int j = (i - 1) / 2; //父节点
        while (j >= 0 && i != 0){
            if (arr[j] <= temp){ //父节点小于等于子节点
                break;
            }
            arr[i] = arr[j]; // 值较大的下移
            i = j;
            j = (i - 1) / 2;
        }
        arr[i] = temp;
    }

    /**
     * 添加都是添加到最后
     * @param arr 堆数组
     * @param n 添加元素的下标
     * @param num 待添加的元素
     */
    private static void heapInsert(int[] arr, int n, int num){
        arr[n] = num;
        shiftUp(arr, n);
    }

    /**
     *
     * @param arr 待调整的堆化数组
     * @param i 待调整的节点下标
     * @param n 堆化数组大小
     */
    private static void shiftDown(int[] arr, int i, int n){
        int temp = arr[i];
        int j = 2 * i + 1;
        while (j < n) {
            //在左右孩子中找最小的
            if (j + 1 < n && arr[j + 1] < arr[j]) {
                j++;
            }
            if (arr[j] >= temp){
                break;
            }
            arr[i] = arr[j];     //把较小的子结点往上移动,替换它的父结点
            i = j;
            j = 2 * i + 1;
        }
        arr[i] = temp;
    }

    /**
     * 删除都是从顶部开始删
     * @param arr
     */
    private static void heapDelete(int[] arr, int n){
        //删除第一个元素
        int temp = arr[n - 1];
        arr[n - 1] = arr[0];
        arr[0] = temp;
        //向下调整
        shiftDown(arr, 0, n - 1);
    }

    /**
     * 建立堆
     * @param arr
     * @param n
     */
    private static void createHeap(int[] arr, int n) {
        for (int i = n / 2 - 1; i >= 0; i--){
            shiftDown(arr, i, n);
        }
    }

    public static int[] heapSort(int[] arr, int n){
        for (int i = n - 1; i >= 1; i--) {
            int temp = arr[0];
            arr[0] = arr[n - 1];
            arr[n - 1] = temp;
            shiftDown(arr, 0, i);
        }
        return arr;
    }

    public static void main(String[] args) {
        int[] arr = new int[]{3,1,41,62,73,22};
        int n = arr.length;
        createHeap(arr, n);
        heapSort(arr, n);
        System.out.println(arr);
    }
}

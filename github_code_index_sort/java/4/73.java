package sort;

/**
 * 堆排序  O(N*logN) s(N)=O(1) 不稳定
 * <p>
 * （1）根据初始数组去构造初始堆（构建一个完全二叉树，保证所有的父结点都比它的孩子结点数值大）。
 * （2）每次交换第一个和最后一个元素，输出最后一个元素（最大值），然后把剩下元素重新调整为大根堆。
 * <p>
 * 堆是一棵顺序存储的完全二叉树。
 * 其中每个结点的关键字都不大于其孩子结点的关键字，这样的堆称为小根堆。
 * 其中每个结点的关键字都不小于其孩子结点的关键字，这样的堆称为大根堆。
 * <p>
 * 设当前元素在数组中以R[i]表示，那么，
 * (1) 它的左孩子结点是：R[2*i+1];
 * (2) 它的右孩子结点是：R[2*i+2];
 * (3) 它的父结点是：R[(i-1)/2];
 * <p>
 * 当想得到一个序列中第k个最小的元素之前的部分排序序列，最好采用堆排序。
 * 因为堆排序的时间复杂度是O(n+klog2n)，若k≤n/log2n，则可得到的时间复杂度为O(n)。
 */
public class Sort_06_HeapSort {

    public static int[] heapSort(int[] arr) {
        //1,建立大根堆
        arr = buildMaxHap(arr);
        //2,调整排序
        for (int i = arr.length - 1; i > 0; i--) {
            //堆顶和堆底元素交换
            swap(arr, 0, i);
            heapAdjust(arr, 0, i);//将剩余的元素整理成堆
        }
        return arr;
    }

    private static int[] buildMaxHap(int[] arr) {
        for (int i = arr.length / 2; i >= 0; i--) {
            heapAdjust(arr, i, arr.length);
        }
        return arr;
    }

    //堆的调整
    public static void heapAdjust(int[] arr, int parent, int length) {
        int temp = arr[parent]; // temp保存当前父节点
        int child = 2 * parent + 1; // 先获得左孩子
        while (child < length) {
            // 如果有右孩子结点，并且右孩子结点的值大于左孩子结点，则选取右孩子结点
            if (child + 1 < length && arr[child] < arr[child + 1]) {
                child++;
            }
            // 如果父结点的值已经大于孩子结点的值，则直接结束
            if (temp >= arr[child]) {
                break;
            }
            // 把孩子结点的值赋给父结点
            arr[parent] = arr[child];
            // 选取孩子结点的左孩子结点,继续向下筛选
            parent = child;
            child = 2 * child + 1;
        }
        arr[parent] = temp;
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
        printArray(heapSort(arr));
    }
}

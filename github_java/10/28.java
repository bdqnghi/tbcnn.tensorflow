package structure;

//冒泡排序
public class BubbleSort {

    public static void main(String[] args) {
        BubbleSort bubbleSort = new BubbleSort();
        bubbleSort.insert(1);
        bubbleSort.insert(3);
        bubbleSort.insert(2);
        bubbleSort.insert(8);
        bubbleSort.insert(5);
        bubbleSort.display();
        bubbleSort.bubbleSort();
        bubbleSort.display();
        bubbleSort.delete(2);
        bubbleSort.display();
    }

    //数组
    private long[] arr;
    //实际元素个数
    private int nElements;
    //默认初始化元素个数
    private int DEFAULT_SIZE = 10;

    //空参构造函数
    public BubbleSort() {
        arr = new long[DEFAULT_SIZE];
        nElements = 0;
    }

    //得到实际元素的个数
    public int size() {
        return this.nElements;
    }

    //将新元素插入到末尾
    public void insert(long element) {
        arr[nElements] = element;
        nElements++;
    }

    // 1 2 3 5 8
    //二分查找删除元素
    public void delete(long element) {
        int start = 0;
        int end = nElements - 1;
        int middle;
        while (true) {
            if (start > end) {
                throw new RuntimeException("元素未找到");
            }
            middle = (start + end) / 2;
            if (arr[middle] == element) {
                for (int i = middle; i < nElements; i++) {
                    arr[i] = arr[i + 1];
                }
                return;
            } else if (arr[middle] > element) {
                end = middle - 1;
            } else if (arr[middle] < element) {
                start = middle + 1;
            }
        }
    }

    //展示数组元素
    private void display() {
        for (int i = 0; i < nElements; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    //冒泡排序
    public void bubbleSort() {
        for (int i = nElements - 1; i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(j, j + 1);
                }
            }
        }
    }

    public void swap(int one, int two) {
        long temp = arr[one];
        arr[one] = arr[two];
        arr[two] = temp;
    }
}

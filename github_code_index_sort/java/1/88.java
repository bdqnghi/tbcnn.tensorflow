package structure;

//简单插入排序
public class InsertionSort {
    public static void main(String[] args) {
        InsertionSort insertionSort = new InsertionSort();
        insertionSort.insert(0);
        insertionSort.insert(7);
        insertionSort.insert(2);
        insertionSort.insert(3);
        insertionSort.insert(5);
        insertionSort.insert(1);
        insertionSort.display();
        insertionSort.insertSort();
        insertionSort.display();
    }

    private long[] arr;
    private int nElements;
    private final int DEFALUT_SIZE = 10;

    public InsertionSort() {
        this.arr = new long[DEFALUT_SIZE];
        this.nElements = 0;
    }

    public void insert(long element) {
        arr[nElements] = element;
        nElements++;
    }

    public void display() {
        for (int i = 0; i < nElements; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    // 2 6 7 _ 8 9
    //插入排序
    public void insertSort() {
        for (int i = 1; i < nElements; i++) {
            //用作比较的数据
            long temp = arr[i];
            //保存空位的下标
            int j;
            for (j = i - 1; j >= 0; j--) {
                if (temp < arr[j]) {
                    arr[j + 1] = arr[j];
                } else {
                    break;
                }
            }
            //把temp放到空位上
            arr[j + 1] = temp;
        }
    }
}

package structure;


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

    
    private long[] arr;
    
    private int nElements;
    
    private int DEFAULT_SIZE = 10;

    
    public BubbleSort() {
        arr = new long[DEFAULT_SIZE];
        nElements = 0;
    }

    
    public int size() {
        return this.nElements;
    }

    
    public void insert(long element) {
        arr[nElements] = element;
        nElements++;
    }

    
    
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

    
    private void display() {
        for (int i = 0; i < nElements; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    
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

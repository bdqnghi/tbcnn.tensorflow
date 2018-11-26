/**
 * Created by Phil on 8/15/2015.
 */
public class HeapSort<Key> extends MyMaxPQ<Key> {

    @Override
    public Key deleteMax() {
        if(size == 0) {
            System.out.println("empty PQ!");
            return null;
        }
        Key retVal = heap[1];
        heap[1] = heap[size--];
        heap[size+1] = retVal;
        sink(1);

        return null;
    }

    public void sort() {
        int heapSize = size;
        for(int j = 0; j < heapSize; j++)
            deleteMax();
    }

    public static void main(String[] args) {

        HeapSort heapSort = new HeapSort();

        heapSort.insert(12);

        heapSort.insert(5);
        heapSort.insert(3);
        heapSort.insert(21);

        heapSort.insert(1);
        heapSort.insert(8);
        heapSort.insert(11);
        heapSort.insert(2);
        heapSort.insert(6);
        heapSort.insert(15);
        heapSort.insert(4);

        for(int i = 0; i < heapSort.heap.length; i++) {
            if(heapSort.heap[i] != null) System.out.print(heapSort.heap[i] + " ");
        }
        System.out.println();

        heapSort.sort();

        for(int i = 0; i < heapSort.heap.length; i++) {
            if(heapSort.heap[i] != null) System.out.print(heapSort.heap[i] + " ");
        }
        System.out.println();

    }

}

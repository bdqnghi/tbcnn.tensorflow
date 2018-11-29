package PukyungUniv;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;

import org.junit.Test;

public class Sort_HeapSort {

    @Test
    public void testGetParentIdx() {
        assertEquals(-1, getParentIdx(0));
        assertEquals(0, getParentIdx(1));
        assertEquals(0, getParentIdx(2));
        assertEquals(2, getParentIdx(5));
        assertEquals(2, getParentIdx(6));
        assertEquals(3, getParentIdx(7));
        assertEquals(3, getParentIdx(8));
    }

    @Test
    public void testGetLeftChildIdx() {
        assertEquals(1, getLeftChildIdx(0));
        assertEquals(3, getLeftChildIdx(1));
        assertEquals(5, getLeftChildIdx(2));
        assertEquals(7, getLeftChildIdx(3));
    }

    @Test
    public void testHeapify1() {
        int[] data = { 1, 2 };
        maxHeapify(data, 0, data.length - 1);
        assertEquals(Arrays.toString(new int[] { 2, 1 }), Arrays.toString(data));
    }

    @Test
    public void testHeapify2() {
        int[] data = { 1, 2, 3 };
        maxHeapify(data, 0, data.length - 1);
        assertEquals(Arrays.toString(new int[] { 3, 2, 1 }), Arrays.toString(data));
    }

    @Test
    public void testHeapify3() {
        int[] data = { 4, 16, 15, 8, 7, 13, 14, 2, 5 };
        maxHeapify(data, 0, data.length - 1);
        assertEquals(Arrays.toString(new int[] { 16, 8, 15, 5, 7, 13, 14, 2, 4 }),
                Arrays.toString(data));
    }
    
    @Test
    public void testMakeHeap() {
        int[] data = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
        makeHeap(data);
        assertEquals(Arrays.toString(new int[] { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 }),
                Arrays.toString(data));
    }

    @Test
    public void test1() {
        int[] data = { 1, 3, 5, 7, 2, 4, 6, 8 };
        sort(data);
        assertEquals(Arrays.toString(new int[] { 1, 2, 3, 4, 5, 6, 7, 8 }), Arrays.toString(data));
    }

    @Test
    public void test2() {
        int[] data = { 4, 16, 15, 8, 7, 13, 14, 2, 5 };
        sort(data);
        assertEquals(Arrays.toString(new int[] { 2, 4, 5, 7, 8, 13, 14, 15, 16 }),
                Arrays.toString(data));
    }

    private static int getLeftChildIdx(int parent) {
        return (parent + 1) * 2 - 1;
    }

    private int getParentIdx(int child) {
        if (child < 1) {
            return -1;
        } else {
            return (child + 1) / 2 - 1;
        }
    }

    private static void maxHeapify(int[] data, int i, int end) {
        int leftChild = getLeftChildIdx(i);
        while (leftChild <= end) {
            int largeChild;
            if (leftChild == end) {
                largeChild = leftChild;
            } else {
                largeChild = data[leftChild] > data[leftChild + 1] ? leftChild : leftChild + 1;
            }
            if (data[i] >= data[largeChild]) {
                return;
            }
            swap(data, i, largeChild);
            i = largeChild;
            leftChild = getLeftChildIdx(i);
        }
    }

    private static void swap(int[] data, int i, int j) {
        int t = data[i];
        data[i] = data[j];
        data[j] = t;
    }

    public static void sort(int[] data) {
        makeHeap(data);
        sortFromHeap(data);
    }

    private static void makeHeap(int[] data) {
        for (int i = data.length / 2 - 1; i >= 0; i--) {
            maxHeapify(data, i, data.length - 1);
        }
    }

    private static void sortFromHeap(int[] data) {
        int last = data.length - 1;
        while (last > 0) {
            swap(data, 0, last);
            last--;
            maxHeapify(data, 0, last);
        }
    }

}

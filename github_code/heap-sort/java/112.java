package heapsort;

import java.util.Random;
import java.util.Scanner;

/**
 * Created by csh9196 on 2017-04-16.
 */
public class HeapSortEx {
    public static void main(String[] args) {
        int[] array;
        Scanner scanner = new Scanner(System.in);
        System.out.println("배열의 크기를 입력해주세요.");
        array = new int[scanner.nextInt()];
        System.out.println("최대값을 입력하세요.");
        int k = scanner.nextInt();
        Random random = new Random();
        for(int i = 0; i < array.length; i++){
            array[i] = random.nextInt(k+1);
        }
        HeapSort heapSort = new HeapSort(array);
        heapSort.print();
        heapSort.heapSort();
        heapSort.ascendingPrintf();
        heapSort.descendingPrintf();
//
//        MaxHeapSort maxHeapSort = new MaxHeapSort(array);
//        maxHeapSort.print();
//        maxHeapSort.heapSort();
//        maxHeapSort.ascendingPrintf();
//        maxHeapSort.descendingPrintf();
    }
}

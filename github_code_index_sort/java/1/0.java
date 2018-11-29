package insertionSort;

import java.util.Random;

/**
 * @author Pavel Belevich
 */
public class SillyInsertionSortBenchmark {

    private final Sort insertionSort1 = new InsertionSort1();
    private final Sort insertionSort2 = new InsertionSort2();

    private final int[] array = new Random().ints(100).toArray();
    private int[] sorting = new int[array.length];

    private void init() {
        System.arraycopy(array, 0, sorting, 0, array.length);
    }

    private long measureInsertionSort1() {
        return measureSort(insertionSort1);
    }

    private long measureInsertionSort2() {
        return measureSort(insertionSort2);
    }

    private long measureSort(Sort sort) {
        int ITERATIONS = 10000;
        for (int i = 0; i < ITERATIONS; i++) {
            init();
            sort.sort(sorting);
        }
        long result = 0;
        for (int i = 0; i < ITERATIONS; i++) {
            init();
            final long start = System.nanoTime();
            sort.sort(sorting);
            final long end = System.nanoTime();
            result += end - start;
        }
        return result / ITERATIONS;
    }

    public static void main(String[] args) {
        SillyInsertionSortBenchmark insertionSortBenchmark = new SillyInsertionSortBenchmark();
        long sort1 = insertionSortBenchmark.measureInsertionSort1();
        long sort2 = insertionSortBenchmark.measureInsertionSort2();
        System.out.println("insertionSort.InsertionSortBenchmark.measureInsertionSort1 " + sort1 + " ns/op");
        System.out.println("insertionSort.InsertionSortBenchmark.measureInsertionSort1 " + sort2 + " ns/op");
    }

}

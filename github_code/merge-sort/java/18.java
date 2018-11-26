package avramenko.lab01.analyzer;

import avramenko.lab01.fillers.GenerateArrays;
import avramenko.lab01.sorters.BubbleSort;
import avramenko.lab01.sorters.MergeSort;
import avramenko.lab01.sorters.QuickSort;
import avramenko.lab01.sorters.StandardSort;

import java.util.TreeMap;

public class Analysis {

    private final String BUBBLE_SORT_START = "Bubble sort from start";
    private final String BUBBLE_SORT_END = "Bubble sort from end";
    private final String QUICK_SORT = "Quick sort";
    private final String STANDARD_SORT = "Standard sort";
    private final String BUBBLE_SORT_START_MERGE = "Merge sort with Bubble sort from start";
    private final String BUBBLE_SORT_END_MERGE = "Merge sort with Bubble sort from end";
    private final String QUICK_SORT_MERGE = "Merge sort with Quick sort";
    private final String STANDARD_SORT_MERGE = "Merge sort with Standard sort";

    private final String SORTED_ARRAY = "Sorted array";
    private final String SORTED_ARRAY_X = "Sorted array with element X at the end";
    private final String REVERSE_ARRAY = "Reversed array";
    private final String RANDOM_ARRAY = "Random filled array";

    public TreeMap<String, Long> startAnalysis(int length, int elementX) {
        GenerateArrays generateArrays = new GenerateArrays();
        BubbleSort bubbleSort = new BubbleSort();
        QuickSort quickSortObj = new QuickSort();
        StandardSort standardSortObj = new StandardSort();
        MergeSort mergeSortObj = new MergeSort();

        TreeMap<String, Long> treeMap = new TreeMap<>();
        long before = System.nanoTime();
        bubbleSort.bubbleSortFromBeginning(generateArrays.generateSortedArray(length));
        long after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_START + " " + SORTED_ARRAY, after - before);

        before = System.nanoTime();
        bubbleSort.bubbleSortFromBeginning(generateArrays.generateArrayX(length, elementX));
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_START + " " + SORTED_ARRAY_X, after - before);

        before = System.nanoTime();
        bubbleSort.bubbleSortFromBeginning(generateArrays.generateAnotherSortedArray(length));
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_START + " " + REVERSE_ARRAY, after - before);

        before = System.nanoTime();
        bubbleSort.bubbleSortFromBeginning(generateArrays.generateRandomArray(length));
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_START + " " + RANDOM_ARRAY, after - before);

        before = System.nanoTime();
        bubbleSort.bubbleSortFromEnd(generateArrays.generateSortedArray(length));
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_END + " " + SORTED_ARRAY, after - before);

        before = System.nanoTime();
        bubbleSort.bubbleSortFromEnd(generateArrays.generateArrayX(length, elementX));
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_END + " " + SORTED_ARRAY_X, after - before);

        before = System.nanoTime();
        bubbleSort.bubbleSortFromEnd(generateArrays.generateAnotherSortedArray(length));
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_END + " " + REVERSE_ARRAY, after - before);

        before = System.nanoTime();
        bubbleSort.bubbleSortFromEnd(generateArrays.generateRandomArray(length));
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_END + " " + RANDOM_ARRAY, after - before);

        before = System.nanoTime();
        quickSortObj.quickSort(generateArrays.generateSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(QUICK_SORT + " " + SORTED_ARRAY, after - before);

        before = System.nanoTime();
        quickSortObj.quickSort(generateArrays.generateArrayX(length, elementX), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(QUICK_SORT + " " + SORTED_ARRAY_X, after - before);

        before = System.nanoTime();
        quickSortObj.quickSort(generateArrays.generateAnotherSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(QUICK_SORT + " " + REVERSE_ARRAY, after - before);

        before = System.nanoTime();
        quickSortObj.quickSort(generateArrays.generateRandomArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(QUICK_SORT + " " + RANDOM_ARRAY, after - before);

        before = System.nanoTime();
        standardSortObj.standardSort(generateArrays.generateSortedArray(length));
        after = System.nanoTime();
        treeMap.put(STANDARD_SORT + " " + SORTED_ARRAY, after - before);

        before = System.nanoTime();
        standardSortObj.standardSort(generateArrays.generateArrayX(length, elementX));
        after = System.nanoTime();
        treeMap.put(STANDARD_SORT + " " + SORTED_ARRAY_X, after - before);

        before = System.nanoTime();
        standardSortObj.standardSort(generateArrays.generateAnotherSortedArray(length));
        after = System.nanoTime();
        treeMap.put(STANDARD_SORT + " " + REVERSE_ARRAY, after - before);

        before = System.nanoTime();
        standardSortObj.standardSort(generateArrays.generateRandomArray(length));
        after = System.nanoTime();
        treeMap.put(STANDARD_SORT + " " + RANDOM_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortFromBeginning(generateArrays.generateSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_START_MERGE + " " + SORTED_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortFromBeginning(generateArrays.generateArrayX(length, elementX), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_START_MERGE + " " + SORTED_ARRAY_X, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortFromBeginning(generateArrays.generateAnotherSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_START_MERGE + " " + REVERSE_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortFromBeginning(generateArrays.generateRandomArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_START_MERGE + " " + RANDOM_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortFromEnd(generateArrays.generateSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_END_MERGE + " " + SORTED_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortFromEnd(generateArrays.generateArrayX(length, elementX), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_END_MERGE + " " + SORTED_ARRAY_X, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortFromEnd(generateArrays.generateAnotherSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_END_MERGE + " " + REVERSE_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortFromEnd(generateArrays.generateRandomArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(BUBBLE_SORT_END_MERGE + " " + RANDOM_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortQuickSort(generateArrays.generateSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(QUICK_SORT_MERGE + " " + SORTED_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortQuickSort(generateArrays.generateArrayX(length, elementX), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(QUICK_SORT_MERGE + " " + SORTED_ARRAY_X, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortQuickSort(generateArrays.generateAnotherSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(QUICK_SORT_MERGE + " " + REVERSE_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortQuickSort(generateArrays.generateRandomArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(QUICK_SORT_MERGE + " " + RANDOM_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortStandardSort(generateArrays.generateSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(STANDARD_SORT_MERGE + " " + SORTED_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortStandardSort(generateArrays.generateArrayX(length, elementX), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(STANDARD_SORT_MERGE + " " + SORTED_ARRAY_X, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortStandardSort(generateArrays.generateAnotherSortedArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(STANDARD_SORT_MERGE + " " + REVERSE_ARRAY, after - before);

        before = System.nanoTime();
        mergeSortObj.mergeSortStandardSort(generateArrays.generateRandomArray(length), 0, length - 1);
        after = System.nanoTime();
        treeMap.put(STANDARD_SORT_MERGE + " " + RANDOM_ARRAY, after - before);

        return treeMap;
    }
}

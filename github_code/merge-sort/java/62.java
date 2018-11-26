/**
* SortingComparison.java
* This class implements four sorting algorithms: insertion-sort, merge-sort, quick-sort, and heap-sort
* It calculates the elapsed time for each algorithm for 10 different n sizes of random integers
* between 1 and 1,000,000. n = 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000
* Prints resulst to a table.
* @author  Andrés Bretón
* @version 1.0
*
* SOURCES: Sources for algorithms were obtained from the following:
* Insertionsort and mergesort -- from the "Data Structures & Algorithms in Java"
* textbook by Michael T. Goodrich, Roberto Tamassia, and Michael H. Goldwasser
* Quicksort -- from Programcreek https://www.programcreek.com/2012/11/quicksort-array-in-java/
* Heapsort -- from Sanfoundry https://www.sanfoundry.com/java-program-implement-heap-sort/
*/

import java.io.*;
import java.util.*;

public class SortingComparison {

    /**
    * This is the main method that calls each sorting algorithm with ten different
    * sizes of random integers, calculating the elapsed time taken as the size
    * of nubmers to sort increases.
    * @param args Unused.
    * @return Void.
    * @exception IOException On input error.
    * @see IOException
    * Output: Table of results for all four algorithms tested with 10 difference
    * input sizes of random numbers.
    */
    public static void main(String args[]) throws IOException {
        // List of sizes to run algorithms with
        List<Integer> sizes = Arrays.asList(10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000);
        // Store results of each sorting algorithm
        ArrayList<Long> insertionResults = new ArrayList<Long>();
        ArrayList<Long> mergeResults = new ArrayList<Long>();
        ArrayList<Long> quickResults = new ArrayList<Long>();
        ArrayList<Long> heapResults = new ArrayList<Long>();
        long startTime = 0; // initialize starting time
        long endTime = 0; // initialize end time
        long elapsedTime = 0; // initialize elapsed

        // Test sorting algorithms on each size array
        for (int n : sizes) {
            // Generate random numbers between 1-1,000,000
            int[] rn = new int[n]; // hold random numbers
            Random r = new Random();
            for (int i = 0; i < n - 1 ; i++) {
                rn[i] = r.nextInt(1000000) + 1;
            }

            System.out.println("Running insertion sort using " + n + " random numbers...");
            // Run INSERTIONSORT and calculate the elapsed time
            int[] insertionSortRN = rn; // copy new random set of numbers
            startTime = System.currentTimeMillis();  // start time for insertion sort
            // SOURCE: Insertion sort code sourced from page 111 of textbook and modified for use here
            insertionSort(insertionSortRN); // insertionsort the n number of random integers
            endTime = System.currentTimeMillis(); // end time of insertion sort
            elapsedTime = endTime - startTime; // elapsed time running insertion sort with n numbers
            insertionResults.add(elapsedTime); // store elapsed time for current n numbers

            System.out.println("Running merge-sort using " + n + " random numbers...");
            // Run MERGESORT and calculate the elapsed time
            int[] mergeSortRN = rn; // copy new random set of numbers
            startTime = System.currentTimeMillis(); // start time for merge sort
            mergeSort(mergeSortRN); // merge-sort the n number of random integers
            endTime = System.currentTimeMillis(); // end time of merge sort
            elapsedTime = endTime - startTime; // elapsed time running merge sort with n numbers
            mergeResults.add(elapsedTime); // store elapsed time for current n numbers


            System.out.println("Running quicksort using " + n + " random numbers...");
            // Run QUICKSORT and calculate the elapsed time
            int[] quickSortRN = rn; // copy new random set of numbers
            startTime = System.currentTimeMillis(); // start time for quick sort
            quickSort(quickSortRN, 0, n -1); // quicksort the n number of random integers
            endTime = System.currentTimeMillis(); // elapsed time running quicksort with n numbers
            elapsedTime = endTime - startTime; // elapsed time running quick sort with n numbers
            quickResults.add(elapsedTime); // store elapsed time for current n numbers


            System.out.println("Running heap-sort using " + n + " random numbers...");
            // Run HEAPSORT and calculate the elapsed time
            int[] heapSortRN = rn; // copy new random set of numbers
            startTime = System.currentTimeMillis(); // start time for heap sorting
            sortHeap(heapSortRN); // execute heap sort
            endTime = System.currentTimeMillis(); // end time of heap sorting
            elapsedTime = endTime - startTime; // elapsed time running heap sort with n numbers
            heapResults.add(elapsedTime); // store elapsed time for current n numbers

            System.out.println();
        }

        // Print results
        System.out.print("\nAlgorithm");
        for (Integer n : sizes) {
            System.out.print("\t" + n);
        }
        System.out.println();
        System.out.print("Insertion \t");
        for (int j = 0; j < 10; j++ ) {
            System.out.print(insertionResults.get(j) + "\t");
        }
        System.out.println();
        System.out.print("Merge \t\t");
        for (int j = 0; j < 10; j++ ) {
            System.out.print(mergeResults.get(j) + "\t");
        }
        System.out.println();
        System.out.print("Quick \t\t");
        for (int j = 0; j < 10; j++ ) {
            System.out.print(quickResults.get(j) + "\t");
        }
        System.out.println();
        System.out.print("Heapsort \t");
        for (int j = 0; j < 10; j++ ) {
            System.out.print(heapResults.get(j) + "\t");
        }
        System.out.println();
    }

    /** ~~~~~~~~~~~~~~~~~~~~~~~ ALGORITHMS SOURCES ~~~~~~~~~~~~~~~~~~~~~~~*/
    /** Insertionsort */
    /**
     * This method utilizes an insertion sort algorithm to sort an array of n
     * number of random integers.
     * SOURCE: Insertion sort code sourced from page 111 of textbook and modified for use here
     * @param int[] array of random numbers
     * @return Void.
     */
     public static void insertionSort(int[] data) {
         int n = data.length;
         for (int k = 1; k < n; k++) { // begin with second character
             int cur = data[k]; // time to insert cur=data[k]
             int j = k; // find correct index j for cur
             while (j > 0 && data[j-1] > cur) { // thus, data[j-1] must go after cur
                 data[j] = data[j-1]; // slide data[j-1] rightward
                 j--; // and consider previous j for cur
             }
             data[j] = cur; // this is the proper place for cur
         }
     }

    /** Quicksort */
    /**
     * This method utilizes a quick sort algorithm to sort an array of n
     * number of random integers.
     * SOURCE: https://www.programcreek.com/2012/11/quicksort-array-in-java/
     * @param int[] array of random numbers
     * @param int a leftmost index
     * @param int b rightmost index
     * @return Void.
     */
     public static void quickSort(int[] arr, int low, int high) {
        if (arr == null || arr.length == 0)
            return;

        if (low >= high)
            return;

        // pick the pivot
        int middle = low + (high - low) / 2;
        int pivot = arr[middle];

        // make left < pivot and right > pivot
        int i = low, j = high;
        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
            }

            while (arr[j] > pivot) {
                j--;
            }

            if (i <= j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }

        // recursively sort two sub parts
        if (low < j)
            quickSort(arr, low, j);

        if (high > i)
            quickSort(arr, i, high);
    }

    /** Merge-sort */
    /**
     * These methods utilizes a merge-sort algorithm to sort an array of n
     * number of random integers.
     * SOURCE: Merge-sort code sourced from page 538 of textbook and modified for use here
     * @param int[] array of random numbers
     * @return Void.
     */
     // Merge-sort contents of array S
     public static void mergeSort(int[] S) {
         int n = S.length;
         if (n < 2) return; // array is trivially sorted
         // divide
         int mid = n/2;
         int[] S1 = Arrays.copyOfRange(S, 0, mid); // copy of first half
         int[] S2 = Arrays.copyOfRange(S, mid, n); // copy of second half
         // conquer (with recursion)
         mergeSort(S1); // sort copy of first half
         mergeSort(S2); // sort copy of second half
         // merge results
         merge(S1, S2, S); // merge sorted halves back into original
     }
     // Merge contents of arrays S1 and S2 into properly sized array S
     public static void merge(int[] S1, int[] S2, int[] S) {
         int i = 0, j = 0;
         while (i + j < S.length) {
             if (j == S2.length || (i < S1.length && S1[i] - S2[j] < 0))
         S[i+j] = S1[i++]; // copy ith element of S1 and increment i
         else
             S[i+j] = S2[j++]; // copy jth element of S2 and increment j
         }
     }


    /** Heap Sort */
    /**
     * These methods utilizes a heap sort algorithm to sort an array of n
     * number of random integers.
     * SOURCE: https://www.sanfoundry.com/java-program-implement-heap-sort/
     * @param int[] array of random numbers
     * @param n number of random numbers
     * @return Void.
     */
    /* Sort Function */
    public static void sortHeap(int arr[])
    {
        int N = arr.length-1;
        heapify(arr);
        for (int i = N; i > 0; i--)
        {
            swap(arr,0, i);
            N = N-1;
            maxheap(arr, 0);
        }
    }
    /* Function to build a heap */
    public static void heapify(int arr[])
    {
        int N = arr.length-1;
        for (int i = N/2; i >= 0; i--)
            maxheap(arr, i);
    }
    /* Function to swap largest element in heap */
    public static void maxheap(int arr[], int i)
    {
        int N = arr.length-1;
        int left = 2*i ;
        int right = 2*i + 1;
        int max = i;
        if (left <= N && arr[left] > arr[i])
            max = left;
        if (right <= N && arr[right] > arr[max])
            max = right;

        if (max != i)
        {
            swap(arr, i, max);
            maxheap(arr, max);
        }
    }
    /* Function to swap two numbers in an array */
    public static void swap(int arr[], int i, int j)
    {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

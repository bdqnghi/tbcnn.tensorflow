/*
 * PROGRAMMER: Ethan Hann
 * COURSE: CSCI 3352
 * DATE: 2/12/2018
 * PROGRAMMING ASSIGNMENT: 1 - QuickSort and HeapSort
 * ENVIRONMENT: IntelliJ IDEA x64 on Windows 10 with Java 1.8
 * OBJECTIVE: To demonstrate the quickSort and heapSort algorithms
 * on a set of data.
 * LIMITATIONS: This program has a hard time with huge data sets
 * such as 9999999 elements
 * INPUT: a randomly generated array of 30 elements; user can supply an array size
 * via command line arguments; 30 is used by default if no argument is supplied
 * PRECONDITIONS: NONE
 * OUTPUT: the original (unsorted array), the sorted array using quickSort,
 * the sorted array using heapSort, the execution times of both the quickSort
 * and the heapSort
 * POSTCONDITIONS: NONE
 * ALGORITHMS:
 *     QUICKSORT:
 *     Given an array A, and the length of the array n (A.length),
 *     quickSort function:
 *     p = 0, r = n
 *     if (p < r) then
 *         q = partition(A, p, r)
 *         quickSort(A, p, q-1)
 *         quickSort(A, q+1, r)
 *     partition function:
 *     Given an array A, start index p, and end index r,
 *     x = A[r], i = p - 1
 *     for j = p to r - 1
 *         if A[j] less than or equal to x
 *             i += 1
 *             exchange the values at A[i] with A[j]
 *     exchange the values at A[i+1] with A[r]
 *     return the value of i+1
 *
 *     HEAPSORT:
 *     1. Build max heap from input data (rearrange array according to heap rules)
 *     2. Replace the root of the heap with the last item
 *     and reduce the size of the heap by 1
 *     3. Repeat 1 and 2 while size of heap is greater than 1
 */

import java.util.Random;

public class Sort
{
    private static final int DEFAULT_SIZE = 30;
    
    public static void main(String[] args)
    {
        //Variables to track the execution time of the quickSort and the heapSort
        long startTime;
        double elapsedQuickSort;
        double elapsedHeapSort;
        int[] quick;
        
        /*
        Checking user supplied command line arguments and using them as the
        array size if they exist and are valid. Otherwise, the default size of 30 will be used.
         */
        if (args.length != 0)
        {
            try
            {
                quick = generateIntArray(Integer.parseInt(args[0]));
            } catch (NumberFormatException n)
            {
                System.out.println("'array size' argument must be greater than 0 and be an Integer.");
                System.out.printf("You entered as an argument: %s\n", args[0]);
                System.out.println("Continuing with default size of 30...");
                quick = generateIntArray(DEFAULT_SIZE);
            }
        }
        else
        {
            quick = generateIntArray(DEFAULT_SIZE);
        }
        
         //array used for quickSort
        int[] heap = quick; //same array used for heapSort

        int n = quick.length;

        printArray(quick, "original", 0);

        //Sorting original array using quickSort
        startTime = System.nanoTime();
        QuickSort.sort(quick, 0, n - 1); //do the quickSort
        elapsedQuickSort = (System.nanoTime() - startTime) * 1e-6; //to milliseconds

        printArray(quick, "quickSort", elapsedQuickSort);

        //Sorting original array using heapSort
        startTime = System.nanoTime();
        HeapSort.sort(heap); //do the heapSort
        elapsedHeapSort = (System.nanoTime() - startTime) * 1e-6; //to milliseconds

        printArray(heap, "heapSort", elapsedHeapSort);
    }

    /**
     * Utility method to generate a random Integer array for test data
     * @param size : the desired size of the array
     * @return : a populated int[size] array
     */
    private static int[] generateIntArray(int size)
    {
        Random rand = new Random(System.currentTimeMillis());
        int[] arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = rand.nextInt(size);
        }
        return arr;
    }

    /**
     * Utility method to print an array of size n
     * @param a : the array to print to the console
     */
    private static void printArray(int a[], String sortMethod, double executionTime)
    {
        int n = a.length;

        switch (sortMethod)
        {
            case "quickSort":
            {
                System.out.printf("QuickSort took %.3f ms: ", executionTime);
                for (int i = 0; i < n; i++)
                {
                    System.out.printf("%d ", a[i]);
                }
                System.out.print("\n");
                break;
            }

            case "heapSort":
            {
                System.out.printf("HeapSort took %.3f ms: ", executionTime);
                for (int i = 0; i < n; i++)
                {
                    System.out.printf("%d ", a[i]);
                }
                System.out.print("\n");
                break;
            }

            case "original":
            {
                System.out.print("Original (Unsorted): ");
                for (int i = 0; i < n; i++)
                {
                    System.out.printf("%d ", a[i]);
                }
                System.out.print("\n");
                break;
            }

            default:
            {
                System.out.println("Something went wrong...");
                break;
            }
        }
    }
}

/**
 * Berlin Brown 
 * Insertion Sort. 
 */
package org.berlin.algo.basic;

import java.util.Random;

/**
 * Insertion Sort with simple cost and time statistics.
 * Based on logic from "Introduction to algorithms", coreman, stein.
 * 
 * Using recursion.
 */
public class InsertionSortRecursionWithCost {

  private final CalledTimesCount times = new CalledTimesCount();
  
  /**
   * Add a count of cost.     
   */
  private class CalledTimesCount {
    private int c1N = 0;
    private int c2N = 0;
    private int c4N = 0;
    private int c5N = 0;
    private int c6N = 0;
    private int c7N = 0;
    private int c8N = 0;
    
    public String toString() {
      return "{Cost and Times T(n): N-for-C2=" + c2N + ", N-for-C6=" + c6N + ", N-for-C8=" + c8N + "}";
    }
  }
  public InsertionSortRecursionWithCost insertionSort(final int [] A) {                  
    times.c1N = A.length;           
    return insertionSort(A, 1);    
  }
  public InsertionSortRecursionWithCost insertionSort(final int [] A, int j) {
    if (j >= A.length) {
      return this;
    }
    int key = A[j];              
    int i = j - 1;
    times.c2N++;
    times.c4N = times.c2N;
    i = insertionSort(A, key, i);
    A[i + 1] = key;
    times.c8N++;
    return insertionSort(A, j + 1);
  }
  public int insertionSort(final int [] A, int key, int i) {
    if (!(i >= 0 && A[i] > key)) {
      return i;
    }        
    times.c6N++;
    A[i + 1] = A[i];    
    return insertionSort(A, key, i-1);
  }    
  public String toString() {
    return String.valueOf(times);
  }
  
  public static void logBefore(final int [] A) {
    System.out.print("A {N=" + A.length + "}= [");
    for (int i = 0; i < A.length; i++) {
      System.out.print(A[i] + ", " );
    }
    System.out.println("].");    
  }  
  public static void logAfter(final int [] A, final InsertionSortRecursionWithCost insertionSort) {

    System.out.print("A(after sort) = [");
    for (int i = 0; i < A.length; i++) {
      System.out.print(A[i] + ", " );
    }
    System.out.println("].");
    System.out.println(insertionSort);
    System.out.println();     
  }
  
  public static void main(final String [] args) {
    System.out.println("Running main - insertion sort - with recursion");
    {
      final int A [] = {
          5, 2, 4, 6, 1, 3
      };
      logBefore(A);
      // Run the insertion sort and update the entries for the array A
      final InsertionSortRecursionWithCost insertionSort = new InsertionSortRecursionWithCost().insertionSort(A);
      logAfter(A, insertionSort);          
    }
    {
      // With random N
      final int A2 [] = new int [30];
      final Random rand = new Random(System.currentTimeMillis());
      for (int i = 0; i < A2.length; i++) {
        A2[i] = rand.nextInt(1000);
      }
      logBefore(A2);    
      final InsertionSortRecursionWithCost insertionSort2 = new InsertionSortRecursionWithCost().insertionSort(A2);
      logAfter(A2, insertionSort2);
    }
    {
      // Best case with sorted values.
      final int A3 [] = {
          1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
      };
      logBefore(A3);
      // Run the insertion sort and update the entries for the array A
      final InsertionSortRecursionWithCost insertionSort = new InsertionSortRecursionWithCost().insertionSort(A3);
      logAfter(A3, insertionSort);          
    }
    System.out.println("Done");
  }  
  
} // End of the Class //

/**
 * MIT License
 * Copyright (c) 2018 Baldeep Hira
 * Contact @ https://bhira.net/
 */

 /**
  * This class implements the insertion sort algorithm for sorting a given set of numbers.
  * https://www.khanacademy.org/computing/computer-science/algorithms/insertion-sort/a/insertion-sort
  * https://www.geeksforgeeks.org/insertion-sort/
  * <p>
  * The program uses a fixed array of numbers as input, it can be changed in main method.
  */
public class InsertionSort {


  /**
   * Main method used to execute insertion sort.  The program used a fixed array of numbers as
   * input.  To change, please update main method and re-compile.  It is meant as an illustrative
   * implementation of the insertion sort algorithm.
   *
   * @param args the standard command line arguments are not used.
   */
  public static void main (String[] args) {
    int[] array = {10,23,49,2,49,29,85,14,9,48,60,30};
    System.out.println("Original Array = " + toString(array));
    insertionSort(array);
    System.out.println("Sorted Array   = " + toString(array));
  }

  /**
   * This method sorts the given array of numbers using insertion sort algorithm.
   * It does an in-place sort, the input array will have sorted results.
   * @param arr the array of numbers to be sorted.
   */
  static void insertionSort(int[] arr) {
    if (arr == null || arr.length <= 0) {
      return;
    }
    for (int i = 0; i < arr.length; i++) {
      insertValue(arr, i);
    }
  }

  /**
   * Insert the data value at specified index in the array at the right location
   * within the array so that entire array is sorted.  The focus of this method
   * is to find the right array position for the data element at given index.
   * @param arr the data array to be sorted.
   * @param index the index of data element to be positioned.
   */
  static void insertValue(int[] arr, int index) {
    if (index <= 0) {
      return;
    }
    int insertIndex = index;
    int value = arr[index];
    for (int i = index-1; i >= 0; i--) {
      if (value < arr[i]) {
        slide(arr, i);
        insertIndex = i;
      } else {
        break;
      }
    }
    arr[insertIndex] = value;
  }

  /**
   * Slide the data value at given index to one position to the right.
   * It will overwrite the contents at position index+1.  If the end
   * of array is reached, it will do nothing.
   * @param arr the array of data values.
   * @param index the index of data values to slide right.
   */
  static void slide(int[] arr, int index) {
    if (index+1 >= arr.length) {
      return; //overflow
    }
    arr[index+1] = arr[index];
  }

  /**
   * Helper method that is used to convert an array into comma separated list.
   * @param arr the array containing data values.
   * @return the comma separated list of values in the array.
   */
  static String toString(int[] arr) {
    StringBuilder b = new StringBuilder("[");
    if (arr != null && arr.length > 0) {
      for (int i=0; i < arr.length; i++) {
        if (i != 0) {
          b.append(',');
        }
        b.append(arr[i]);
      }
    }
    b.append("]");
    return b.toString();
  }

}
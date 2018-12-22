/*
  Write a sort method that uses the bubble-sort algorithm. The bubble-sort
  algorithm makes several passes through the array. On each pass, successive
  neighboring pairs are compared. If a pair is not in order, its values are
  swapped; otherwise, the values remain unchanged. The technique is called
  bubble sort or sinking sort because the smaller values gradually bubble their
  way to the top and the larger values sink to the bottom. Write a test program
  that reads in ten double numbers, invokes the method, and displays the
  sorted numbers.
*/

import java.util.Scanner;

public class E7_18 {
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    System.out.print("Enter ten numbers: ");
    double[] nums = new double[10];
    for (int i = 0; i < nums.length; i++) {
      nums[i] = input.nextDouble();
    }

    bubblesort(nums);

    for (double num: nums) {
      System.out.print(num + " ");
    }
    System.out.println();
  }

  public static void bubblesort(double[] arr) {
    boolean didSwap;
    do {
      didSwap = false;
      for (int i = 0; i < arr.length - 1; i++) {
        if (arr[i] > arr[i + 1]) {
          double temp = arr[i + 1];
          arr[i + 1] = arr[i];
          arr[i] = temp;
          didSwap = true;
        }
      }
    } while (didSwap);
  }
}

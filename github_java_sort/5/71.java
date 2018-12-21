

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

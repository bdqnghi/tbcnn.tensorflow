import java.util.Arrays;

public class Example {

   public static void main(String a[]) {

      int[] arr = {93, 75, 52, 37, 15, 80, 66, 41, 27, 2};
      System.out.println("Unsorted: " + Arrays.toString(arr));

      insertionSort(arr);
      System.out.println("Sorted  : " + Arrays.toString(arr));
   }

   public static void insertionSort(int[] arr) {

      for (int i = 1; i < arr.length; i++) {
         for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
               int temp = arr[j];
               arr[j] = arr[j - 1];
               arr[j - 1] = temp;
            }
         }
      }
   }
}



import java.util.*;

public class Example {

   public static void main(String[] args) {
      int max = 100;
      int[] data = {99, 77, 55, 33, 11, 88, 66, 44, 22};
      System.out.println("Unsorted: " + Arrays.toString(data));

      bucketSort(data, max);
      System.out.println("Sorted  :  " + Arrays.toString(data));
   }

   public static void bucketSort(int[] arr, int max) {
      int[] bucket = new int[max + 1];

      for (int i = 0; i < bucket.length; i++) {
         bucket[i] = 0;
      }

      for (int i = 0; i < arr.length; i++) {
         bucket[arr[i]]++;
      }

      int x = 0;
      for (int i = 0; i < bucket.length; i++) {
         for (int j = 0; j < bucket[i]; j++) {
            arr[x++] = i;
         }
      }
   }

}



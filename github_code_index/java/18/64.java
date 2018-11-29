import java.util.Arrays;

public class Example {

   public static void main(String[] args) {

      int[] arr = {95,74,58,32,11,88,64,42,23,3};
      System.out.println("Unsorted: " + Arrays.toString(arr));

      selectionSort(arr);
      System.out.println("Sorted  : " + Arrays.toString(arr));
   }

   public static void selectionSort(int[] arr) {

      for (int i = 0; i < arr.length - 1; i++) {
         int index = i;
         for (int j = i + 1; j < arr.length; j++) {
            if (arr[j] < arr[index]) {
               index = j;
            }
         }

         int tmp = arr[index];
         arr[index] = arr[i];
         arr[i] = tmp;
      }
   }
}



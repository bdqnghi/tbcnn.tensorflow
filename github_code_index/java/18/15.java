public class Solution {
    /**
     * @param A an integer array
     * @return void
     */
    public void sortIntegers(int[] A) {
        // Write your code here
        if (A == null) {
          return;
        }
        for (int i = 0; i < A.length; i++) {
          int minIndex = i;
          for (int j = i + 1; j < A.length; j++) {
            if (A[j] < A[minIndex]) {
              minIndex = j;
            }
          }
          if (minIndex != i) {
            swap(A, i, minIndex);
          }
        }
    }
    private void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
}
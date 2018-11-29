public class Solution {
  private static int[] shellSort(int[] ar, int h) {
    for (int i = h; i < ar.length; i += h) {
      for (int j = i; j > 0; j -= h) {
        if (ar[j - h] > ar[j]) {
          int buf = ar[j];
          ar[j] = ar[j - h];
          ar[j - h] = buf;
        } else {
          break;
        }
      }
    }
    return ar;
  }
  
  private static void printArray(int[] ar) {
    for (int i = 0; i < ar.length; i++) {
      System.out.print(ar[i] + " ");
    }
    System.out.println();
  }

  public static void main(String[] args) {
    int[] ar = shellSort( new int[]{ 90, 3, 6, 4, 5, 18, 32, 18, 24, 1 }, 4);
    printArray(ar);
    ar = shellSort(ar, 2);
    printArray(ar);
    ar = shellSort(ar, 1);
    printArray(ar);
  }
}

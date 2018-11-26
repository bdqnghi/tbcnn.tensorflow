public class Solution {
  private static void iterate(int[] ar) {   
    for (int i = 0; i < ar.length; i++) {
      for (int j = i; j > 0; j--) {
        if (ar[j - 1] > ar[j]) {
          int buf = ar[j];
          ar[j] = ar[j - 1];
          ar[j - 1] = buf;
        } else {
          // no need to go all the way to the begining.
          break;
        }
      }
    }
    
    for (int i = 0; i < ar.length; i++) {
      System.out.print(ar[i] + " ");
    }
  }

  public static void main(String[] args) {
    iterate( new int[]{ 1, 5, 3, 6, 4, 90, 18, 32, 18, 24 } );
  }
}

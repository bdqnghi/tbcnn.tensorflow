/**
 * JavaStringReverse.java
 *
 * - In this problem, given a string A, print "Yes" if it is a palindrome, print
 *   "No" otherwise. The strings will consist lower case english letters only.
 *   The strings will have at most 50 characters.
 */

import java.io.*;
import java.util.*;

public class JavaStringReverse {

   public static void main(String[] args) {
      Scanner sc = new Scanner(System.in);
      String A   = sc.next();
      boolean isPalindrome = true;
      int i1 = 0;
      int i2 = A.length()-1;

      while (i1 < i2) {
         if (A.charAt(i1) != A.charAt(i2)) {
            isPalindrome = false;
         }
         i1++;
         i2--;
      }

      if (isPalindrome) {
         System.out.println("Yes");
      }
      else {
         System.out.println("No");
      }
   }
}

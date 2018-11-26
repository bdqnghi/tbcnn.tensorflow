/////////////////////////////////////
// Solution 1 Compare two pointers //
/////////////////////////////////////

import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /**
         * we can use two pointer to do this
         * and condition is <= mid
         */
        int start = 0, end = A.length() - 1;
        int mid = start + (end - start) / 2;
        while (start <= mid) {
            if (A.charAt(start) != A.charAt(end)) {
                break;
            }
            start++;
            end--;
            
        }
        System.out.println((start > end) ? "Yes" : "No");
    }
}

//////////////////
// Solution 1.1 //
//////////////////

public class Solution {
    public static void main(String[] args) {
        /* Read input */
        Scanner scan = new Scanner(System.in);
        String s = scan.nextLine();
        scan.close();
        
        int i, j;
        for (i = 0, j = s.length() - 1; i < j; i++, j--) {
            if (s.charAt(i) != s.charAt(j)) {
                break;
           }
            
        }
        
        if (i >= j) {
           System.out.println("Yes");
        } else {
           System.out.println("No");        

        }

    }
}

////////////////////////////////////
// Solution 2 Using StringBuilder //
////////////////////////////////////

import java.util.Scanner;

/* If a String is equivalent to itself when reversed, it's a palindrome */
public class Solution {
    public static void main(String[] args) {
        /* Read input */
        Scanner scan = new Scanner(System.in);
        String str = scan.nextLine();
        scan.close();
        
        /* Reverse string and compare to original */
        String reversed = new StringBuilder(str).reverse().toString();
        System.out.println(str.equals(reversed) ? "Yes" : "No");
    }
}




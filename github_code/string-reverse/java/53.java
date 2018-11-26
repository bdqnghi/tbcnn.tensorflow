//https://www.hackerrank.com/challenges/java-string-reverse

import java.util.Scanner;

/* If a String is equivalent to itself when reversed, it's a palindrome */
public class Solution {

    public static void main(String[] args) {
        /* Read input */
        Scanner scan = new Scanner(System.in);
        String s = scan.next();
        scan.close();
        
        /* Reverse string and compare to original */
        String rev = new StringBuilder(s).reverse().toString();
        System.out.println(s.equals(rev) ? "Yes" : "No");
    }
}
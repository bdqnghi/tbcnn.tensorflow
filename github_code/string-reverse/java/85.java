// https://www.hackerrank.com/challenges/java-string-reverse

import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        String A = sc.next();
        
        for (int i = 0, n = A.length()-1; i <= n; ++i) {
            if (A.charAt(i) != A.charAt(n)) 
            { 
                sc.close();
                System.out.println("No"); 
                return; 
            }
            n--;
        }
        
        sc.close();
        System.out.println("Yes");
    }
}

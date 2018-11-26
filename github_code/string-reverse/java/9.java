/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javastringreverse;

import java.util.*;

/**
 *
 * @author IMG
 */
public class JavaStringReverse {
//    https://www.hackerrank.com/challenges/java-string-reverse/problem

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        /* Enter your code here. Print output to STDOUT. */
        Scanner in = new Scanner(System.in);
        // Store word to be checked
        String A = in.next();
        
        // Store reversed string
        String B = "";
        // Array list of Characters
        ArrayList<Character> list = new ArrayList<>();
        
        // Store word in reverse to ArrayList
        for (int i = A.length(); i > 0; i--) {
            list.add(A.charAt(i-1));
        }
        
        // Move ArrayList Characters to new string
        for (int i = 0; i < list.size(); i++) {
            B += list.get(i);
        }
        
        // Check if word is a palindrome
        if ( B.equals(A) ) {
            System.out.println("Yes");
        }
        else {
            System.out.println("No");
        }
    }
    
}

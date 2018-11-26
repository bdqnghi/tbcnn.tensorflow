/**
 Link to Original Problem:
 https://www.hackerrank.com/challenges/java-string-reverse/problem
 **/


import java.io.*;
import java.util.*;

public class Java_String_Reverse {

    public static void main(String[] args) {

        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /* Enter your code here. Print output to STDOUT. */
        StringBuilder s = new StringBuilder(A);
        String B = s.reverse().toString();
        if(A.equals(B))
            System.out.println("Yes");
        else
            System.out.println("No");
    }
}




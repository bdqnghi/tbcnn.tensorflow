package Java;

import java.io.*;
import java.util.*;

public class JavaStringReverse {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        
        String A=sc.next();
        sc.close();
        StringBuilder ab=new StringBuilder(A);
        StringBuilder abr=ab.reverse();
        String B=abr.toString();
        if(A.equals(B)){
            System.out.println("Yes");
        }else{
            System.out.println("No");
        }
        /* Enter your code here. Print output to STDOUT. */
        
    }
}

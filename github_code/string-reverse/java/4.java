import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /* Enter your code here. Print output to STDOUT. */
        String reverseA = new StringBuilder(A).reverse().toString();
        int ok = 1;
        char[] charA = A.toCharArray();
        char[] charReverse = reverseA.toCharArray();
        for (int i = 0; i < charA.length; i++) {
            if (charA[i] != charReverse[i]) {
                ok = 0;
                break;
            }
        }
        if (ok == 1) {
            System.out.println("Yes");
        }
        if (ok == 0) {
            System.out.println("No");
        }
        
    }
}


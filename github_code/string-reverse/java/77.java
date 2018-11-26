import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /* Enter your code here. Print output to STDOUT. */
        boolean isPalindrome = true;
        int limit = (int)A.length() / 2;
        int i;
        
        for(i = 0; i < limit; i ++) {
            if(A.charAt(i) != A.charAt(A.length() - 1 - i)) {
                System.out.println("No");
                break;
            }
        }
        if (i == limit) System.out.println("Yes");
    }
}

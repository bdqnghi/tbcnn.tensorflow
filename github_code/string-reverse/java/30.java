import java.io.*;
import java.util.*;

public class JavaStringReverse {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /* Enter your code here. Print output to STDOUT. */
        char[] arr = A.toCharArray();
        boolean flag = true;
        for(int i=0, j= arr.length-1; i<arr.length/2;i++, j--){
            if(arr[i]!=arr[j]){
                flag = false;
                break;
            }
        }
        if(flag)
            System.out.println("Yes");
        else
            System.out.println("No");
    }
}

import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        
        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        sc.close();
        String rev="";
        for(int i=A.length();i>0;i--)
            {
            String temp = A.substring(i-1,i);

            rev = rev+temp;
            
        }
        boolean res = rev.equals(A);
        if(res){
        	System.out.printf("Yes");
        }
        else System.out.printf("No");
        
    }
}
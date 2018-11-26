package Strings;

import java.util.Scanner;

public class Java_String_Reverse 
{
	 public static void main(String[] args)
	    {
		    System.out.println("Enter a String:");
	        Scanner sc=new Scanner(System.in);
	        String A=sc.next();
	        String B=A;
	        
	        System.out.println("String Before Reverse is : " +B);
	        String C= "";
	        char[] arr=A.toCharArray();
	        
	        for(int i=arr.length-1;i>=0 ;i--)
	        {
	            C+=arr[i];
	        }
	        
	        System.out.println("String Aftere Reverse is : " +C);
	        
	        if (B.equals(C))
	        System.out.println("Yes");
	        else
	        System.out.println("No");
	    }
}

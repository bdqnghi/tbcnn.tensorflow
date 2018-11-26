package myPrograms;

import java.util.Scanner;

public class stringreverse {
	public static void main(String[] args) {
	    Scanner s = new Scanner(System.in);
	    String original, contain ="";
	    original=s.nextLine();
	    int length = original.length();
		  for(int i=length-1;i>=0;i--)
		  {
			contain= contain+original.charAt(i);  
		  }
	  System.out.println(contain);
	  if(original.equals(contain))
	  {
		  System.out.println("It is palindrome");
	  }
	  else
	  {
		  System.out.println("Not palindrome");
	  }
		}

}



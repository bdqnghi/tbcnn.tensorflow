package my.tutorial.basic;

import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.function.Function;

public class StringReverse {
	
	public static String reverseIteratively(String str) {
		
		StringBuilder sb = new StringBuilder();
		char [] charArr = str.toCharArray();
		
		for(int i = charArr.length-1; i >= 0; i--) {
			sb.append(charArr[i]);
		}
		return sb.toString();
	}
	
	public static String reverseRecursively(String str) {
		//System.out.println("Str : "+ str);
		if(str.length() < 2) {
			return str;
		}
		return reverseRecursively(str.substring(1)) +str.charAt(0);
	}

	public static void main(String[] args) {
		//original string
        String str = "Sony is going to introduce Internet TV soon";
        System.out.println("Original String: " + str);
       
        //reversed string using Stringbuffer
        //String reverseStr = new StringBuffer(str).reverse().toString();
        //System.out.println("Reverse String in Java using StringBuffer: " + reverseStr);

        //iterative method to reverse String in Java
        //reverseStr = reverseIteratively(str);
        //System.out.println("Reverse String in Java using Iteration: " + reverseStr);

        //recursive method to reverse String in Java
        String reverseStr = reverseRecursively(str);
        System.out.println("Reverse String in Java using Recursion: " + reverseStr);

        //Read more: https://javarevisited.blogspot.com/2012/01/how-to-reverse-string-in-java-using.html#ixzz5UjcJY3js
	}

}

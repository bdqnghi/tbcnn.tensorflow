package com.zwli.algorithm;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * How to reverse Java String using Iteration and Recursionif you are from C background and new to Java then you get surprise that java
 * Strings are not character array instead they are object and Strings in Java are not null terminated but still you can use your C skill to
 * write iterative reverse function for string by getting character array by calling String.toCharArray() and getting length of String by
 * calling String.length(). Now if you succeed in writing String reverse function, an iterative version without using StringBuffer reverse
 * than they finally ask you to write a recursive one. Since recursion is a tricky concept and not many Java developer think recursive as
 * compared to C++ dudes, you may see many of Java programmer stuck here by doing doodling around subString, indexOf etc. So its better to
 * prepare in advance. here I have given example of reversing string using StringBuffer, iterative version of String reversal and reversing
 * string in Java using recursion. As I said recursive solution is always tricky to come up you need to found a suitable base case and than
 * repetitive call recursive method with each call reducing length of argument. anyway mine way is just one way of reversing string using
 * recursion, there are many solution out there. so don’t forget to try out yourself.
 */
public class StringReverse {

	public static void main(String args[]) throws FileNotFoundException, IOException {
		// original string
		String str = "Sony is going to introduce Internet TV soon";
		System.out.println("Original String: " + str);

		// reversed string using Stringbuffer
		String reverseStr = new StringBuffer(str).reverse().toString();
		System.out.println("Reverse String in Java using StringBuffer: " + reverseStr);

		// iterative method to reverse String in Java
		reverseStr = reverse(str);
		System.out.println("Reverse String in Java using Iteration: " + reverseStr);

		// recursive method to reverse String in Java
		reverseStr = reverseRecursively(str);
		System.out.println("Reverse String in Java using Recursion: " + reverseStr);
	}

	public static String reverse(String str) {
		StringBuilder strBuilder = new StringBuilder();
		char[] strChars = str.toCharArray();

		for (int i = strChars.length - 1; i >= 0; i--) {
			strBuilder.append(strChars[i]);
		}
		return strBuilder.toString();
	}

	public static String reverseRecursively(String str) {
		// base case to handle one char string and empty string
		if (str.length() < 2) {
			return str;
		}
		return reverseRecursively(str.substring(1)) + str.charAt(0);
	}
}

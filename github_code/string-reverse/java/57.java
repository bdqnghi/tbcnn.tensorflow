package com.nano.core.string;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Stack;

public class StringReverseExample
{

	/**
	 * @param args
	 */
	public static void main(String args[]) // throws FileNotFoundException,
											// IOException
	{
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

	public static String reverse(String str)
	{
		StringBuilder strBuilder = new StringBuilder();
		char[] strChars = str.toCharArray();

		for (int i = strChars.length - 1; i >= 0; i--)
		{
			strBuilder.append(strChars[i]);
		}

		return strBuilder.toString();
	}

	public static String reverseRecursively(String str)
	{

		// base case to handle one char string and empty string
		if (str.length() < 2)
		{
			return str;
		}
		System.out.println((str.substring(1)) + str.charAt(0));
		return reverseRecursively(str.substring(1)) + str.charAt(0);

	}

	// Read more:
	// http://javarevisited.blogspot.com/2012/01/how-to-reverse-string-in-java-using.html#ixzz2zsqNBYra

}

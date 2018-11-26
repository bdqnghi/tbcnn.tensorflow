package com.java;

public class CrunchifyReverseString {

	public static void main(String[] args) {
		String testString = "Jyotsna";
		System.out.println("String: " + testString);
		System.out.println("\nReverse Using reverseStringBuffer: " + reverseStringBuffer(testString));
		System.out.println("Reverse Using reverseCharArray: " + reverseCharArray(testString));
		System.out.println("Reverse Using reverseStringVariable: " + reverseStringVariable(testString));
		System.out.println("Reverse Using reverseRecursion: " + reverseRecursion(testString));
	}

	// Solution1: Reverse using StringBuffer Example
	public static String reverseStringBuffer(String s) {
		return new StringBuffer(s).reverse().toString();
	}

	// Solution2: Reverse using Char Array Example
	public static String reverseCharArray(String s) {
		char[] reverseStringArray = new char[s.length()];
		for (int i = s.length() - 1, j = 0; i != -1; i--, j++) {
			reverseStringArray[j] = s.charAt(i);
		}
		return new String(reverseStringArray);
	}

	// Solution3: Reverse using String Variable Example
	public static String reverseStringVariable(String s) {
		String reverseStringVariable = "";
		for (int i = s.length() - 1; i != -1; i--) {
			reverseStringVariable += s.charAt(i);
		}
		return reverseStringVariable;
	}

	// Solution4: Reverse using Recursion Example
	public static String reverseRecursion(String s) {
		if (s.length() <= 1) {
			return s;
		}
		return reverseRecursion(s.substring(1, s.length())) + s.charAt(0);
	}
}

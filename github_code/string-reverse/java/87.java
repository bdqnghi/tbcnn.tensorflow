package com.string;

import javax.print.attribute.standard.RequestingUserName;

public class JavaStringReverse {

	public boolean testPalindrome(String str) {

		int j = str.length() - 1;
		for (int i = 0; i < str.length() / 2; i++) {
			if (str.charAt(i) != str.charAt(j))
				return false;
			j--;
		}

		return true;
	}

	
	public boolean testPalindromeByReverse(String str) {

	
		String reverse= new StringBuffer(str).reverse().toString();
		if (str.equals(reverse)) {
			return true;
		}

		return false;
	}
	public static void main(String[] args) {
		boolean result= new JavaStringReverse().testPalindrome("madam1");
		System.out.println(result);
		boolean result1= new JavaStringReverse().testPalindromeByReverse("madam");
		System.out.println(result1);

	}

}

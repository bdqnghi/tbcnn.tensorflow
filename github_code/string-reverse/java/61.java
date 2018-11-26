package com.sunilpandey.demos;

public class StringReverseExample {

	
	public static void main(String args[]) {
		
		
		/*Prerequisite : String vs StringBuilder vs StringBuffer in Java

		Following are some interesting facts about String and StringBuffer classes :
	1. Objects of String are immutable. if you try to alter their values, 
		another object gets created, whereas StringBuffer and StringBuilder are mutable 
		so they can change their values
	2. String class in Java does not have reverse() method, 
		however StringBuilder class has built in reverse() method.
	3. StringBuilder class do not have toCharArray() method,
		while String class does have toCharArray() method.*/
		
		/*It is recommended to use StringBuilder whenever possible
		because it is faster than StringBuffer. However, 
		if the thread safety is necessary, the best option is StringBuffer objects.*/
		

        //original string
        String str = "Sunil pandey is a good boy";
        System.out.println("Original String: " + str);

        //reversed string using Stringbuffer
        String reverseStr = new StringBuffer(str).reverse().toString();
        System.out.println("Reverse String in Java using StringBuffer: " + reverseStr);

        //iterative method to reverse String in Java
        reverseStr = reverse(str);
        System.out.println("Reverse String in Java using Iteration: " + reverseStr);

        //recursive method to reverse String in Java
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

        //base case to handle one char string and empty string
        if (str.length() < 2) {
            return str;
        }

        return reverseRecursively(str.substring(1)) + str.charAt(0);

    }



}

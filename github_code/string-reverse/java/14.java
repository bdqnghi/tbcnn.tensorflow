package com.thy.studylearn.algorithm.stringarray;

public class ReverseString {
	
	public static String stringReverse(String in){
		if(in == null) return null;
		if(in.length() <= 1) return in;
		
		char[] content = in.toCharArray();		
		for(int i=0,j=content.length-1; i<j; i++,j--){
			char temp = content[i];
			content[i] = content[j];
			content[j] = temp;
		}		
		return String.valueOf(content);		
	}	
	
	public static void main(String... arg){
		System.out.println("1. " + stringReverse("Hello World"));
		System.out.println("2. " + stringReverse("Hello World!"));
		System.out.println("3. " + stringReverse("H"));
		System.out.println("4. " + stringReverse(""));
	}
}

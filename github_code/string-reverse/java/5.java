package com.java;

import java.util.Arrays;
import java.util.StringTokenizer;

public class Stringreverse {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str = "Hey whats up buddy";
		StringTokenizer str1 = new StringTokenizer(str," ");
		int len = str1.countTokens();
		String[] rev = new String[len];
		int i = len-1;
		while(str1.hasMoreElements() && i>=0)
		{
			rev[i] = str1.nextElement().toString();
			i--; 
		}
		//System.out.println(java.util.Collections.reverseOrder().toString());
		java.util.Collections.reverse(Arrays.asList(rev));
		for(String s: rev)
			System.out.println(s+ " ");
		for(String s: rev)
			System.out.print(s+" ");

}
}
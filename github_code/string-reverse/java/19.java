package com.markit.demo;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Stringreverse {

	/*public static void main(String[] args) {
	
	Scanner sc=new Scanner(System.in);
	StringBuilder sb=new StringBuilder();
	while(sc.hasNext()){
		String s=sc.next();
		if(s.equals("exit")) {
	        break;
	    }
		char[] array= s.toCharArray();
		int j=0;
		char[] newArray = new char[array.length];
		for (int i=array.length-1; i>=0;i--){
			newArray[j]=array[i];
			j++;
						
     	}sb.append(newArray);
		sb.append(" ");
				
	}	
	
	System.out.println(sb.toString());
	
	sc.close();}*/

	
	
	public static void main(String args[]){
/*		Scanner sc=new Scanner(System.in);
		StringBuilder sb=new StringBuilder();
		String s=sc.nextLine();
		StringTokenizer st=new StringTokenizer(s, " ");
	
		while(st.hasMoreTokens()){
			String bef=st.nextToken();
			char[] array= bef.toCharArray();
			int j=0;
			char[] newArray = new char[array.length];
			for (int i=array.length-1; i>=0;i--){
				newArray[j]=array[i];
				j++;
							
	     	}sb.append(newArray);
			sb.append(" ");
		}					
		System.out.println(sb.toString());		
		sc.close();
		*/
		LinkedList list=new LinkedList();
		
		list.add("s1");
		list.add("s2");
		list.add("s3");
		list.add("s4");
		System.out.println(list.getFirst());
		System.out.println(list.getLast());
		Iterator i=list.descendingIterator();
		while(i.hasNext()){
		System.out.println(i.next());
		
	
		}
		
	}
	
}



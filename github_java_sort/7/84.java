package com.algo3.sort;

import java.util.Arrays;
import java.util.Scanner;


public class ShellSort {

	
	public static boolean  isLess(int a, int b){
		if(a<b) return true;
				else if(a>b) return false;
						else return false; 
	}

	public static void swap(int[] ary, int posa, int posb){
		
		int swap = ary[posa];
		ary[posa] = ary[posb];
		ary[posb] = swap;
		
	}
	
	
	public static void main(String[] args) {


		System.out.println("Enter ints seperated by space: ");
		Scanner scn = new Scanner(System.in);
		String str = scn.nextLine();
		
		String[] strary = str.split(" ");
		
		int[] intary = new int[strary.length];

		for (int i = 0; i < strary.length; i++) {
			intary[i] = Integer.parseInt(strary[i]);
		}
		
		
		
		int n = intary.length;
		int h = 1;
		System.out.print("h=1;");
		while(h < n){
			h = 3*h + 1;
			System.out.print(h+";");
		}
		
		System.out.println("");
		
		while (h>=1){
			System.out.println("h="+h);
			
			for (int i = h; i < n; i++) 
			{
				for (int j = i; j >= h; j -=h) {
					
					if(isLess(intary[j], intary[j-h] ))
					{
						
						swap(intary, j, j-h);
					}
					
				}
				
				System.out.println(Arrays.toString(intary));
				
			}
			
			h = h/3;
		}
		
		
			
			
			
	}
}



